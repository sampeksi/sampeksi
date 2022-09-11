#include "player.hh"
#include <iostream>
#include <string>

using namespace std;

Player::Player(string name):
    name_(name) {
}

void Player::add_points(int points)
{
    if (points_ + points > 50) {
        points_ = 25;
        cout << name_ << " gets penalty points!" <<endl;
    } else {
        points_ += points;
    }
}

bool Player::has_won()
{
    if (points_ == 50) {
        return 1;
    } else {
        return 0;
    }
}

string Player::get_name()
{
    return name_;
}

int Player::get_points()
{
    return points_;
}

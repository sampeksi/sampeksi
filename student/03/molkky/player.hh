#ifndef PLAYER_HH
#define PLAYER_HH

#include <iostream>
#include <string>

using namespace std;

class Player
{
public:
    Player(string name);
    void add_points(int points);
    bool has_won();
    string get_name();
    int get_points();

private:
    string name_;
    int points_ = 0;
};

#endif // PLAYER_HH

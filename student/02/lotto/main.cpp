#include <iostream>

using namespace std;

unsigned long int factorials(int total, int drawn, int difference) {

    unsigned long int factorial_total = 1;
    while (total > 0) {
        factorial_total = factorial_total * total;
        --total;
    }
    unsigned long int factorial_drawn = 1;
        while (drawn > 0) {
            factorial_drawn = factorial_drawn * drawn;
            --drawn;
    }
    unsigned long int factorial_difference = 1;
    while (difference > 0) {
        factorial_difference = factorial_difference * difference;
        --difference;
    }
    unsigned long int denominator = factorial_total / (factorial_drawn * factorial_difference);
    return denominator;

}

int main()
{

    int ball_total = 0;
    cout << "Enter the total number of lottery balls: ";
    cin >> ball_total;

    int drawn_balls = 0;
    cout << "Enter the number of drawn balls: ";
    cin >> drawn_balls;

    if (ball_total <= 0 or drawn_balls <= 0) {
        cout << "The number of balls must be a positive number." << endl;
    } else if (ball_total == drawn_balls) {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
    }
    else {
        int difference = ball_total - drawn_balls;
        unsigned long int denominator = factorials(ball_total, drawn_balls, difference);
        cout << "The probability of guessing all " << drawn_balls << " balls correctly is ";
        cout << "1/" << denominator << endl;
    }
    return 0;
}

#include <iostream>

using namespace std;

int main()
{
    int numbers = 0;
    cout << "How many numbers would you like to have? ";
    cin >> numbers;

    int number = 1;

    while (number <= numbers) {

        if (number % 3 == 0 and number % 7 == 0) {
            cout << "zip boing" <<endl;
        } else if (number % 3 == 0) {
            cout << "zip" <<endl;
        }  else if (number % 7 == 0) {
            cout << "boing" <<endl;
        } else {
            cout << number <<endl;
        }
        number += 1;

    }

    return 0;
}

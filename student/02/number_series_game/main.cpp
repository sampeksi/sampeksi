#include <iostream>

using namespace std;

int main()
{
    int numbers = 0;
    cout << "How many numbers would you like to have? ";
    cin >> numbers;

    int number = 1;

    while (number <= numbers) {

        cout << number <<endl;
        number += 1;

    }

    return 0;
}

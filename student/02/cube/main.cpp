#include <iostream>

using namespace std;

int main()
{
    int number = 0;
    cout << "Enter a number: ";
    cin >> number;

    if ((number * number * number) > number or number == 1 or number == 0) {
        cout << "The cube of " << number << " is " << number * number * number <<"." <<endl;
    } else {
        cout << "Error! The cube of " << number << " is not " << number * number * number << "." <<endl;
    }


    return 0;
}

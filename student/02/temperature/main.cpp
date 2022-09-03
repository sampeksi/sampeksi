#include <iostream>

using namespace std;

int main()
{
    int lampo = 0;
    cout << "Enter a temperature: ";
    cin >> lampo;

    cout << lampo << " degrees Celsius is " << lampo * 1.8 + 32 << " degrees Fahrenheit" << endl;

    cout << lampo << " degrees Celsius is " << (lampo - 32) / 1.8 << " degrees Celsius" << endl;

    return 0;
}

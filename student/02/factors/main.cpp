#include <iostream>
#include <string>

using namespace std;

int main()
{

    int number = 1;
    cout << "Enter a positive number: ";
    cin >> number;

    if (number <= 0) {
        cout <<"Only positive numbers accepted" << endl;
    } else {

    int count = 1;
    int last_factor = 1;
    int first_factor;
    int second_factor;


        while (count <= number) {
           if (number % count == 0) {

                if (number / count == last_factor and number % count == 0) {

                   break;
               } else if (count * count == number) {
                   last_factor = count;
                   break;
               } else {

                   last_factor = count;}
               }
           count += 1;
          }
        first_factor = last_factor;
        second_factor = number / last_factor;
        cout << number <<" = "<< first_factor << " * " << second_factor <<endl;

        }

    return 0;
}

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    string input_file = "";
    cout << "Input file: ";
    getline(cin, input_file);

    string output_file = "";
    cout << "Output file: ";
    cin >> output_file;

    ifstream file_name(input_file);
    if (file_name) {
        int line = 1;
        string rivi;
        ofstream file(output_file);
        while (getline(file_name, rivi)) {
            file << line << " " << rivi <<endl;
            line += 1;
        }
        file_name.close();
    } else {
        cout << "Error! The file " << input_file <<
                " cannot be opened." <<endl;
        return EXIT_FAILURE;
    }
}

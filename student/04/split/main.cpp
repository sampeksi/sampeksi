#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(string line, char sep, bool spaces = false)
{
    int length = line.length();
    if (spaces == true) {
        vector<string> prints;
        string chars = "";

        for (int i = 0; i+1 < length; ++i) {
            if (line.at(i) == sep) {
                if (chars != "") {
                    prints.push_back(chars);
                    chars = "";
                }
            } else {
                chars += line.at(i);
            }
            if (i+2 == length) {
                if (line.at(i+1) != sep) {
                    chars += line.at(i+1);}
                if (chars != "") {
                    prints.push_back(chars);}

            }
        } return prints;
    } else {
        vector<string> prints;
        string chars = "";
        if (line.at(0) == sep) {
            prints.push_back("");
        }
        for (int i = 0; i+1 < length; ++i) {
            if (line.at(i) == sep) {
                if (chars != "") {
                prints.push_back(chars);
                chars = "";}

                if (line.at(i+1) == sep) {
                    prints.push_back("");
                }
            } else {
                chars += line.at(i);
        } if (i+2 == length) {
                if (line.at(i+1) == sep) {
                    if (chars != "") {
                    prints.push_back(chars);
                    prints.push_back("");}
                } else {
                    chars += line.at(i+1);
                    prints.push_back(chars);
                }
            }
        }
    return prints;}
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}

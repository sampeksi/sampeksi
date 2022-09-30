#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

void printer(string key, vector<int> details)
{
    cout << key << " " << details.at(0) << ": ";
    string::size_type i = 1;
    while (i < details.size()) {
        if (i+1 == details.size()) {
            cout << details.at(i) <<endl;
        } else {
            cout << details.at(i) << ", ";
        } i += 1;
    }
}

bool sorter(string key1, string key2)
{
    return key1 < key2;
}

string::size_type location(string line, int last_location)
{
    string::size_type location = 0;
    location = line.find(' ', last_location);
    return location;
}

int main()
{
    string input_file;
    cout << "Input file: ";
    getline(cin, input_file);

    ifstream words(input_file);
    if (not words) {
        cout << "Error! The file " << input_file <<
                " cannot be opened." <<endl;
        return EXIT_FAILURE;
    }
    map<string, vector<int>> details;
    vector<string> keys;
    string line;
    int current_line = 1;
    while (getline(words, line)) {

        int last_location = 0;

        while (location(line, last_location) != string::npos) {
            int length = location(line, last_location)- last_location;

            string key = line.substr(last_location, length);
            last_location += (length+1);

            if (details.find(key) != details.end()) {

                if (details.at(key).back() != current_line) {

                details.at(key).at(0) += 1;
                details.at(key).push_back(current_line);}
            } else {
                details.insert({key, {1, current_line}});
                keys.push_back(key);
            }
        }
            int word_length = line.length();
            string key = line.substr(last_location,
                                 word_length);

            if (details.find(key) != details.end()) {

                if (details.at(key).back() != current_line) {
                details.at(key).at(0) += 1;
                details.at(key).push_back(current_line);}

            } else {
                details.insert({key, {1, current_line}});
                keys.push_back(key);
            }
        current_line += 1;
    } words.close();

    sort(keys.begin(), keys.end(), sorter);
    for (string k : keys) {
        printer(k,details.at(k));
    }

     return EXIT_SUCCESS;
}

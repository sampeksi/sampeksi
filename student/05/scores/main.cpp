#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>


using namespace std;

int main()
{
    string file_name;
    cout << "Input file: ";
    getline(cin, file_name);

    ifstream score_list(file_name);
    if (not score_list) {
        cout << "Error! The file " << file_name <<
                " cannot be opened." <<endl;
        return EXIT_FAILURE;}
        string line;
        map <string, int> prints;
        while (getline(score_list, line)) {

         int i = line.find(':');
         string name = line.substr(0, i);
         string points = line.substr(i+1);

         if (prints.find(name) != prints.end()) {
             prints.at(name) += stoi(points);
         } else {
             prints.insert({name, 0});
             prints.at(name) += stoi(points);

         }

        }
        cout << "Final scores:" <<endl;

        for (auto pair : prints) {
            cout << pair.first << ": " <<
                    pair.second <<endl;
        }


    return 0;
}

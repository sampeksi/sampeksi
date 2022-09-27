#ifndef STRINGS_HH
#define STRINGS_HH
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Strings
//This class is used to create an object for each guess.
{
public:
    Strings(string guess);
    bool print_line(string hidden_word, vector<string>& to_print);

private:
    string guess_;

};

#endif // STRINGS_HH





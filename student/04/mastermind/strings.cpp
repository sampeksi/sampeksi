#include "strings.hh"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Strings::Strings(string guess):
    guess_(guess) {
}

//Param: hidden_word is the word that player is trying to guess.
//Param: to_print is a vector where every string, based on latest guess,
//are added.
//This method has two purposes.
//First, compare made guess to the hidden word and check, which characters
//are complitely right and which are the same colour as found in hidden word.
//Second, create the string that includes the guess and details and then
bool Strings::print_line(string hidden_word, vector<string>& to_print) {

    int fully_correct = 0;

    //Creating parameter compared to avoid guess_ from changing.
    string compared = guess_;
    string found = "f", used = "u";

    for (int i = 0; i < 4; ++i) {
            if (compared.at(i) == hidden_word.at(i)) {
                fully_correct += 1;
                compared.replace(i, 1, found);
                hidden_word.replace(i, 1, used);
        }
    }
    int right_colour = 0;
    string::size_type place = 0;
    for (int i = 0; i < 4; ++i) {

        place = hidden_word.find(compared.at(i));
        if (place != string::npos) {
            right_colour += 1;
            compared.replace(i, 1, found);
            hidden_word.replace(place, 1, used);
        }
    }
    string numbers = "01234"; //Numbers to convert int to string.

    //Constructing the final string, which is added into the
    //vector to_print
    string returned_string = "";
    returned_string += "| ";
    returned_string += toupper(guess_.at(0));
    returned_string += " ";
    returned_string += toupper(guess_.at(1));
    returned_string += " ";
    returned_string += toupper(guess_.at(2));
    returned_string += " ";
    returned_string += toupper(guess_.at(3));
    returned_string += " | ";
    returned_string += numbers.at(fully_correct);
    returned_string += " | ";
    returned_string += numbers.at(right_colour);
    returned_string += " |";

    to_print.push_back(returned_string);

    //Determines whether player has won or not.
    if ( fully_correct == 4 ){
        return true;
    }
    else{
        return false;
    }
}

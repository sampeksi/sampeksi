#include "strings.hh"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cctype>

using namespace std;

/* Mastermind
 *
 * Descirption:
 * The program implements the Mastermind game. The game is given or drawn
 * first a secret series of four colors. The same color can appear in a series
 * multiple times, but none of the four positions can be empty.
 * The user tries to guess which colors appear in the sequence and where
 * in order. For this, the user provides his own set of four colors,
 * and the program reports how many color guesses were completely correct
 * (correct color in correct position) and how many guesses were made
 * only correct in terms of color (correct color in wrong position).
 * After this, the user can make a new guess, etc.
 * Initially, the user is asked if the game grid will be filled randomly
 * with random colors or colors listed by the user.
 * (The latter method is not very sensible, but it is useful
 * from the point of view of testing.) In the first option, the user is asked
 * the seed number of the random number generator and the tail in the latter
 * you are asked to enter four colors (the initial letters of the colors, i.e. four
 * character long string).
 * In each round, the user is asked for a new guess. The game ends
 * to the player's win, if the guess goes completely for each color
 * correct. The game ends with the player losing if he has not guessed correctly
 * with a maximum number of (10) guessing times.
 * The program checks that the given colors belong to the allowed colors
 * into the crowd. At the end of the game, it is told whether the player won or lost.
 *
 * Writers
 * Names: Pekka Nokelainen, Sampo Suokuisma
 * Student number: 150290744, 150422473
 * Username: gmpeno
 * E-Mail: pekka.nokelainen@tuni.fi, sampo.suokuisma@tuni.fi
 *
 * */

// Maximum number of guesses
// (Not used in the template code)
const unsigned int GUESS_MAX = 10; // Not in use, yet

// Number of colors in a series
const unsigned int SIZE = 4;

// Length of the suffix part when printing a row.
// The suffix consists of three vertical lines ('|') and two digits, where one
// tells the amount of totally correct colors and the other tells the amount
// of correct colors in incorrect positions.
const unsigned int SUFFIX_LENGTH_IN_PRINT = 5;

// Text printed at the beginning of the program
const string INFO_TEXT = "Colors in use: \
B = Blue, R = Red, Y = Yellow, G = Green, O = Orange, V = Violet";

// Colors to compare the input to.
const string COLORS_TO_CHOOSE = "brygov";

// Creates a color sequence at random and saves it to "colors_to_guess".
// Parameters: Seed is the seedvalue for the generator, colors_to_guess
// is the hidden color sequence.
void random_colors(int seed, string& colors_to_guess){
    default_random_engine gen(seed);
    uniform_int_distribution<int> distr(0, 5);
    for ( unsigned int i = 0; i < SIZE; ++i ){
        char color = COLORS_TO_CHOOSE.at(distr(gen)); // Chooses a color.
        colors_to_guess += color;
    }

}

// Checks if the colors guessed are the right lenght and
// Only contains colors from the info.
// Parameters: colors_to_guess is the hidden color sequence,
// colors is the input line.
// Returns: bool, right if line fills requirements.
bool choose_colors(string colors, string& colors_to_guess){
    if ( colors.size() != 4 ){
        cout << "Wrong size" << endl;
        return false;
    }

    for ( char i : colors ){

        if ( isupper(i) ){
            i = tolower(i);
        }

        if ( COLORS_TO_CHOOSE.find(i) != std::string::npos){
            if ( colors_to_guess != "Already guessed" ) {

                colors_to_guess += i;
            }
        }
        else{
            cout << "Unknown color" << endl;
            colors_to_guess = "";
            return false;
        }
    }

    return true;
}

// Reads the input way, either random or listing way,
// and fills the color series in the user-desired way.
// Repeats the question until the user enters either R or L.
// Parameters: colors_to_guess is the hidden color sequence.
void get_input(string& colors_to_guess)
{
    cout << "Enter an input way (R = random, L = list): ";
    string input_str = "";
    cin >> input_str;
    if(input_str == "R" or input_str == "r")
    {
        while ( true ){
        cout << "Enter a seed value: ";
        int seed = 0;
        cin >> seed;
        if ( !cin.good() ){// Checks if seed is actually a number.
            cin.clear();
            cin.ignore(10000,'\n');
        }
        else{
            random_colors(seed, colors_to_guess);
            break;
        }
        }

    }
    else if(input_str == "L" or input_str == "l")
    {
        bool accepted = false;
        while(not accepted)
        {
            cout << "Enter four colors (four letters without spaces): ";
            string colors = "";
            cin >> colors;

            accepted = choose_colors(colors, colors_to_guess);
        }
    }
    else
    {
        cout << "Bad input" << endl;
        // Below the function itself is called recursively, which makes the
        // above code executed until an acceptable input_str is given,
        // but instead you can enclose the above code inside a loop structure.
        get_input(colors_to_guess);
    }
}

// Prints a line consisting of the given character c.
// The length of the line is given in the parameter line_length.
// Parameters: c is character to print, line_lenght is how many to print.
void print_line_with_char(char c, unsigned int line_length)
{
    for(unsigned int i = 0; i < line_length; ++i)
    {
        cout << c;
    }
    cout << endl;
}

// Prints all color series.
void print_all(vector<string> to_print)
{
    print_line_with_char('=', 2 * (SIZE + SUFFIX_LENGTH_IN_PRINT) + 1);

    //prints every line currently added into the vector.
    for( auto &line : to_print ){
        cout << line << endl;
    }
    print_line_with_char('=', 2 * (SIZE + SUFFIX_LENGTH_IN_PRINT) + 1);
}

// The loop that asks the player to guess a color sequence untill it is
// the right lenght and contains only colors in the info or q.
// Returns: the line the player wants to guess.
string guess_input(){
    bool accepted = false;
    string colors = "";
    string already_guessed = "Already guessed";

    while(not accepted)
    {
        cout << "ROW> ";
        cin >> colors;

        if ( colors == "q" || colors == "Q" ){
            return colors;
        }

        accepted = choose_colors(colors, already_guessed);
    }

    string lower_case_colors = "";
    for ( auto i : colors ){// Changes all characters to lower case.
        if ( isupper(i) ){
            i = tolower(i);
        }
        lower_case_colors += i;
    }
    return lower_case_colors;
}

// Implements the actual game loop, where user-given guesses are read
// and compared to the secret row.
// On each round, all rows given so far are printed.
int main()
{
    string colors_to_guess = ""; //The hidden color sequence.
    string guess = ""; //The guess which the player currently guesses.
    bool has_won = false;

    cout << INFO_TEXT << endl;
    print_line_with_char('*', INFO_TEXT.size());

    get_input(colors_to_guess);

    vector<string> to_print;

    unsigned int guesses = 0;// How many guesses out of 10 used.
    while ( guesses < GUESS_MAX && has_won == false ){

        guess = guess_input();

        if ( guess == "q" || guess == "Q" ){
            has_won = true;
            break;
        }

        Strings mastermind(guess);
        has_won = mastermind.print_line(colors_to_guess, to_print );
        print_all(to_print);
        guesses += 1;

        if ( has_won ){
            cout << "You won: Congratulations!" << endl;
        }
    }

    if ( not has_won ){
        cout << "You lost: Maximum number of guesses done" << endl;
    }

    return 0;
}

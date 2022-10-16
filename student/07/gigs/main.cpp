/* COMP.CS.110 Project 2: GIGS
 * ===========================
 * EXAMPLE SOLUTION
 * ===========================
 *
 *  Acts as a simple gig calendar with n commands:
 * ARTISTS - Prints all known artist names
 * ARTIST <artist name> - Prints single artist's gigs
 * STAGES - Prints all known stage names and their locations
 * STAGE <stage name> - Prints all artists having a gig at the given stage
 * ADD_ARTIST <artist name> - Adds a new artist
 * ADD_GIG <artist name> <date> <town name> <stage name> - Adds a new gig for
 * an artist with the given date, town, and stage (the artist can't already
 * have a gig on the same date and there can't be other gigs at the same stage
 * at the same time)
 * CANCEL <artist name> <date> - Cancels artist's gigs after the given date
 *
 *  The data file's lines should be in format
 * artist_name;date;town_name;stage_name.
 * Otherwise the program execution terminates instantly (but still gracefully).
 *
 * */

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <cctype>
#include <algorithm>


using namespace std;

// Farthest year for which gigs can be allocated
const std::string FARTHEST_POSSIBLE_YEAR = "2030";

// Casual split func, if delim char is between "'s, ignores it.
std::vector<std::string> split(const std::string& str, char delim = ';')
{
    std::vector<std::string> result = {""};
    bool inside_quotation = false;
    for ( char current_char : str )
    {
        if ( current_char == '"' )
        {
            inside_quotation = not inside_quotation;
        }
        else if ( current_char == delim and not inside_quotation )
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if ( result.back() == "" )
    {
        result.pop_back();
    }
    return result;
}

// Checks if the given date_str is a valid date, i.e. if it has the format
// dd-mm-yyyy and if it is also otherwise possible date.
bool is_valid_date(const std::string& date_str)
{
    std::vector<std::string> date_vec = split(date_str, '-');
    if ( date_vec.size() != 3 )
    {
        return false;
    }

    std::string year = date_vec.at(0);
    std::string month = date_vec.at(1);
    std::string day = date_vec.at(2);
    std::vector<std::string> month_sizes
            = { "31", "28", "31", "30", "31", "30",
                "31", "31", "30", "31", "30", "31" };

    if ( month < "01" or month > "12" )
    {
        return false;
    }
    if ( year < "0001" or year > FARTHEST_POSSIBLE_YEAR )
    {
        return false;
    }
    unsigned int year_int = stoi(year);
    bool is_leap_year = (year_int % 400 == 0) or
                        (year_int % 100 != 0 and year_int % 4 == 0);
    if ( day >= "01" and
        (day <= month_sizes.at(stoi(month) - 1) or
        (month == "02" and is_leap_year and day <= "29")) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Asks the user for a file and then if the file meets the standards
// adds the gigs to the gig calendar (gig_calendar).
bool read_file(multimap<string, vector<string>>& gig_calendar){

    string file_name = "";
    cout << "Give a name for input file: ";
    getline(cin, file_name);

    ifstream file(file_name);
    if ( not file ) {
        cout << "Error: File could not be read." << endl;
        return false;
    }

    string file_row;
    while ( getline(file, file_row) ) {
        vector<string> info_vector = split(file_row);
        if ( info_vector.size() != 4 ){
            cout << "Error: Invalid format in file." << endl;
            return false;
        }
        // Ei tarkista onko pelkkiä välilyöntejä, pitääkö laittaa?
        if ( is_valid_date(info_vector.at(1)) ){
            gig_calendar.insert( {info_vector.front(), { info_vector[1],
                                  info_vector[2], info_vector[3] } } );
        }

    }
    file.close();

    return true;
}

// Checks for double booking.
// Returns true if booking can take place.
bool check_if_free(multimap<string, vector<string>> gig_calendar,
                   vector<string> input_vector){

    for ( auto artist : gig_calendar ){
        if ( artist.first == input_vector[1] &&
             (artist.second)[1] == input_vector[2] ){
            return false;
        }
        if ( (artist.second)[1] == input_vector[2] &&
             (artist.second)[2] == input_vector[3] &&
             (artist.second)[3] == input_vector[4] ){
            return false;
        }
    }
    return true;
}

// Compares which date is further in the future.
// Returns true if date2 is further in the future or
// date1 and date2 are the same.
bool compare_dates(string date1, string date2){

    vector<string> first = split(date1, '-');
    vector<string> second = split(date2, '-');
    int i = 0;

    while ( i <= 2 ){
        if ( stoi(first[i]) > stoi(second[i]) ){
            return false;
        }
        if ( stoi(first[i]) < stoi(second[i]) ){
            return true;
        } ++i;
    }
    return true;
}
vector<string> gigs_in_order(vector<string> gigs)
{
    vector<string> sorted_gigs;
    for (const string &gig : gigs) {
        if (gig == gigs[0]) {
            sorted_gigs.push_back(gig);
        } else {
            int index = 0;
            for (const string &sg : sorted_gigs) {
                if (compare_dates(gig, sg)) {
                    sorted_gigs.insert(sorted_gigs.begin() + index, gig);
                    break;
                } else {
                    if (sg == sorted_gigs.back()) {
                        sorted_gigs.push_back(gig);
                        break;
                    } else {
                        index += 1;}
                }
            }
        }
    }
    return sorted_gigs;
}

// Checks if there are any gigs after the given date and if so cancels them.
// Returns true or false depending on whether or not the action went through.
bool gigs_cancelled(multimap<string, vector<string>>& gig_calendar,
                    vector<string> input_vector){

    vector<string> dates = {};
    if ( gig_calendar.find(input_vector[1]) != gig_calendar.end() ) {
        for (pair<string, vector<string>> artist : gig_calendar) {
            if (artist.first == input_vector[1]) {
                dates.push_back((artist.second)[0]);
            }
        }
    }

   vector<string> earlier_dates;
   for (const string &date : gigs_in_order(dates)) {
       if (!compare_dates(input_vector[2], date)) {
           earlier_dates.push_back(date);
       }
       else {
           break;
       }
   }

   bool cancelled = false;
   multimap<string, vector<string>> update;
   for (pair<string, vector<string>> artist : gig_calendar) {
       vector<string>::iterator iter;
       iter = find(earlier_dates.begin(), earlier_dates.end(),
                   (artist.second)[0]);

       if (artist.first == input_vector[1] && iter == earlier_dates.end()) {
           update.insert({"cancelled", artist.second});
           cancelled = true;
       } else {
           update.insert(artist);
       }
   }
   gig_calendar = update;
   gig_calendar.erase("cancelled");

   return cancelled;
}


void print_artists(multimap<string, vector<string>> gig_calendar)
{
    string last_artist;
    for (pair<string, vector<string>> artist : gig_calendar) {
        if (artist.first != last_artist) {
            cout << artist.first <<endl;
            last_artist = artist.first;
        }
    }
}

void print_stages(multimap<string, string> stages)
{
    map<string, string> printed_stages;
    cout << "All gig places in alphabetical order:" <<endl;
    for (pair<string, string> stage : stages) {
        if (printed_stages.find(stage.second) == printed_stages.end()) {
            printed_stages.insert({stage.second, ""});
            cout << stage.first << ", " << stage.second <<endl;
            }
    }
}

void print_performers(vector<string> performers)
{
    for (const string &performer : performers) {
        cout << " - " << performer <<endl;
    }
}

void string_to_upper(vector<string>& input_vector)
{
    string upper_string;
    string::size_type i = 0;
    while (i < (input_vector[0].length())) {
        upper_string += toupper(input_vector[0].at(i));
        i += 1;
    }
    int length = input_vector[0].length();
    input_vector[0].replace(0, length, upper_string);
}

int main()
{
    multimap<string, vector<string>> gig_calendar = {};

    bool file_read_succesfully = read_file(gig_calendar);
    if ( !file_read_succesfully ){
        return EXIT_FAILURE;
    }

    while ( true ){
        string input_string;
        cout << "gigs> ";
        getline(cin, input_string);
        vector<string> input_vector = split(input_string, ' ');

        if ( input_vector.size() <= 0 ){
            cout << "Error: Invalid input." << endl;
        }
        string_to_upper(input_vector);

        if ( input_vector[0] == "QUIT" ){
            return EXIT_SUCCESS;
        }
        else if ( input_vector[0] == "ARTISTS" ){
            print_artists(gig_calendar);
        }
        else if ( input_vector[0] == "ARTIST" && input_vector.size() >= 2 ){
            if ( gig_calendar.find(input_vector[1]) != gig_calendar.end() ) {
                vector<string> dates = {};
                for (pair<string, vector<string>> artist : gig_calendar) {
                    if (artist.first == input_vector[1]) {
                        dates.push_back((artist.second)[0]);
                    }
                }
                cout << "Artist " << input_vector[1] << " has the following "
                     "gigs in the order they are listed:" <<endl;
                for (const string &gig : gigs_in_order(dates)) {
                    for (pair<string, vector<string>> artist : gig_calendar) {
                        if (artist.first == input_vector[1] &&
                                (artist.second)[0] == gig) {

                            cout << " - " << gig <<" : " << (artist.second)[1]
                                 << ", " << (artist.second)[2] <<endl;
                        }
                    }
                }

            }
            else {
                cout << "Error: Not found." << endl;
            }
        }
        else if ( input_vector[0] == "STAGES" ){
            multimap<string, string> stages;
            for (pair<string, vector<string>> artist : gig_calendar) {
                string city = (artist.second)[1];
                string place = (artist.second)[2];
                stages.insert({city, place});
                }
            print_stages(stages);
            }

        else if ( input_vector[0] == "STAGE" && input_vector.size() >= 2 ){
            bool in_stages = false;
            for ( auto artist : gig_calendar ){
                if ( (artist.second)[2] == input_vector[1] ){
                    in_stages = true;
                }
            }
            if ( !in_stages ){
                cout << "Error: Not found." << endl;
            }
            else {
                vector<string> performers;
                for (pair<string, vector<string>> artist : gig_calendar) {
                    if ((artist.second)[2] == input_vector[1]) {
                        performers.push_back(artist.first);
                    }
                }
                cout << "Stage " << input_vector[1] <<
                          " has gigs of the following artists:" <<endl;
                print_performers(performers);
            }
        }
        else if ( input_vector[0] == "ADD_ARTIST" && input_vector.size() >= 2){
            if ( gig_calendar.find(input_vector[1]) != gig_calendar.end() ){
                cout << "Error: Already exists." << endl;
            }
            else {
                gig_calendar.insert( {input_vector[1], { } } );
                cout << "Artist added." << endl;
            }
        }
        else if ( input_vector[0] == "ADD_GIG" && input_vector.size() >= 5 ){
            if ( gig_calendar.find(input_vector[1]) != gig_calendar.end() ){

                if ( is_valid_date(input_vector[2]) ){

                    if ( check_if_free(gig_calendar, input_vector)){

                        gig_calendar.insert({input_vector[1], {input_vector[2],
                                           input_vector[3], input_vector[4]}});

                        cout << "Gig added." << endl;
                    }
                    else {
                        cout << "Error: Already exists." << endl;
                    }
                }
                else {
                    cout << "Error: Invalid date." << endl;
                }
            }
            else {
                cout << "Error: Not found." << endl;
            }
        }
        else if ( input_vector[0] == "CANCEL" && input_vector.size() >= 3 ){
            if ( gig_calendar.find(input_vector[1]) == gig_calendar.end() ){
                cout << "Error: Not found." << endl;
            }
            else if ( !is_valid_date(input_vector[2] ) ){
                cout << "Error: Invalid date." << endl;
            }
            else if ( gigs_cancelled(gig_calendar, input_vector) ){
                cout << "Artists' gigs after the given date cancelled." <<endl;
            }
            else {
                cout << "Error: No gigs after the given date." << endl;
            }
        }
        else {
            cout << "Error: Invalid input." << endl;
        }

    }

    return EXIT_SUCCESS;
}

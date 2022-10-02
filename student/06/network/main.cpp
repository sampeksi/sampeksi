#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <utility>


using namespace std;

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

bool is_in_people(map<string, vector<string>> people, string person)
{
    if (people.find(person) != people.end()) {
        return true;
    } else {
        for (pair<string, vector<string>> p : people) {
            for (string k : p.second) {
                if (k == person) {
                    return true;
                }
            }
        }
    } return false;
}

void print(map<string, vector<string>> people, string person, string points = "")
{
    if (people.find(person) == people.end()) {
        cout << points << person <<endl;
    } else {
        cout << points;
        cout << person <<endl;
        points += "..";
        for (string p : people.at(person)) {
            print(people, p, points);
        }
    }
}

void help_counter(map<string, vector<string>> people, string person, int& count)
{
    if (people.find(person) != people.end()) {
        for (string p : people.at(person)) {
                help_counter(people, p, ++count);
        }
    }
}

void counter(map<string, vector<string>> people, string person)
{
    int count = 0;
    if (people.find(person) != people.end()) {
        for (string p : people.at(person)) {
            help_counter(people, p, ++count);
    }
    } cout << count << endl;
}

int depth(map<string, vector<string>> people, string person)
{
    int count = 1;
    if (people.find(person) != people.end()) {
        for (string p : people.at(person)) {
            return count + depth(people, p);
        }
    } return count;
}

int main()
{
    map<string, vector<string>> people;


    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            if (people.find(id1) != people.end()) {
                people.at(id1).push_back(id2);
            } else {
                people.insert({id1, {id2}});
            }

        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            if (is_in_people(people, id)) {
                print(people, id);
            } else {
                cout << id << endl;
            }



        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            if (is_in_people(people, id)) {
                counter(people, id);
            } else {
                cout << id << endl;
            }


        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);
            if (is_in_people(people, id)) {
                cout << depth(people, id) <<endl;
            } else {
                cout << id << endl;
            }

        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}

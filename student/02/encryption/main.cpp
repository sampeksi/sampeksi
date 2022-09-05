#include <iostream>
#include <string>
#include <cctype>

using namespace std;

void encrypter(string key, string text) {

    string encryption = "";
    int max = text.length();

    for (int index = 0; index < max; ++index) {

        char character = text.at(index);

        int asc = static_cast< int >(character) - 97;

        char enc = key.at(asc);
        encryption = encryption + enc;
    }
    cout << "Encrypted text: " << encryption <<endl;

}

int tester(string key) {

    int characters = key.length();

    if (characters != 26) {
        cout << "Error! The encryption key must contain 26 characters." <<endl;
        return EXIT_FAILURE;
    }

    for (int index = 0; index < characters; ++index) {

        char character = key.at(index);

        if (islower(character) == 0) {
            cout << "Error! The encryption key must contain only lower case characters." <<endl;
            return EXIT_FAILURE;}
        }

    for (int index = 0; index < 26; ++index) {
        if (key.find(key.at(index), index+1) <= 26) {
            cout << "Error! The encryption key must contain all alphabets a-z." <<endl;
            return EXIT_FAILURE;
        }
    }
    string text = "";
    cout << "Enter the text to be encrypted: ";
    getline(cin, text);
    int chars = text.length();

    for (int index = 0; index < chars; ++index) {

        char characterr = text.at(index);

        if (islower(characterr) == 0) {
            cout << "Error! The text to be encrypted must contain only lower case characters." <<endl;
            return EXIT_FAILURE;}
    }
    encrypter(key, text);
    return EXIT_SUCCESS;
}


int main()
{
    string key = "";
    cout << "Enter the encryption key: ";
    getline(cin, key);

    if (tester(key) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    } else {
        return 0;}
}

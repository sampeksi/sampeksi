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

void tester(string key) {

    string::size_type characters = 0;
    characters = key.length();

    if (characters != 26) {
        cout << "Error! The encryption key must contain 26 characters." <<endl;
        return;
    }

    for (int index = 0; index < 26; ++index) {

        char character = key.at(index);

        if (islower(character) == 0) {
            cout << "Error! The encryption key must contain only lower case characters." <<endl;
            return;}
        }

    for (int index = 0; index < 26; ++index) {
        if (key.find(key.at(index), index+1) <= 26) {
            cout << "Error! The encryption key must contain all alphabets a-z." <<endl;
            return;
        }
    }
    string text = "";
    cout << "Enter the text to be encrypted: ";
    getline(cin, text);
    encrypter(key, text);
}


int main()
{
    string key = "";
    cout << "Enter the encryption key: ";
    getline(cin, key);

    tester(key);

    return 0;
}

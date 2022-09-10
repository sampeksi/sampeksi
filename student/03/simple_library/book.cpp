#include "book.hh"
#include <iostream>
#include <string>
#include "date.hh"

using namespace std;

Book::Book(string author, string book):
    author_(author), book_(book) {

}


void Book::loan(Date day)
{
    if (status_ == "available") {
        status_ = "loaned";
        loaned_ = day;
        day.advance(28);
        returned_ = day;
    } else {
        cout << "Already loaned: cannot be loaned" <<endl;
    }
}
void Book::renew()
{
    if (status_ == "loaned") {
        returned_.advance(28);
    } else {
        cout << "Not loaned: cannot be renewed" <<endl;
    }
}
void Book::give_back()
{
    if (status_ == "loaned") {
        status_ = "available";
    }
}
void Book::print()
{
    if (status_ == "available") {
        cout << author_ << " : " << book_ <<endl;
        cout << "- available" <<endl;
    } else {
        cout << author_ << " : " << book_ <<endl;
        cout << " - loaned: "; loaned_.print();
        cout << "- to be returned: "; returned_.print();

    }
}

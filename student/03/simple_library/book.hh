#ifndef BOOK_HH
#define BOOK_HH

#include "date.hh"
#include <iostream>
#include <string>

using namespace std;

class Book
{
public:
    Book(string author, string book);
    void print();
    void loan(Date day);
    void renew();
    void give_back();


private:
    string author_;
    string book_;
    string status_ = "available";
    Date loaned_;
    Date returned_;

};

#endif // BOOK_HH

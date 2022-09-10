#include "account.hh"
#include <iostream>

using namespace std;

Account::Account(const std::string& owner, bool has_credit):
   name_(owner), credits_(has_credit) {

    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::set_credit_limit(int amount)
{
    if (credits_ != 0) {
        limit_ = amount;
    } else {
        cout << "Cannot set credit limit: the account has no credit card" <<endl;
    }
}

void Account::save_money(int number)
{
    saved_money_ = saved_money_ + number;
}

void Account::take_money(int taken)
{
    if (saved_money_ < taken and credits_ != 0) {
        if (credits_ >= saved_money_ - taken) {
            saved_money_ = saved_money_ - taken;
            cout << taken << "euros taken: new balance of "
        << iban_ << " is " << saved_money_ << " euros" <<endl;
        } else {
            cout << "Cannot take money: credit limit overflow" <<endl;
        }
    }
    else if (saved_money_ < taken) {
        cout << "Cannot take money: balance underflow" <<endl;
    } else {
        saved_money_ -= taken;
        cout << taken << "euros taken: new balance of "
    << iban_ << " is " << saved_money_ << " euros" <<endl;
    }
}

void Account::transfer_to(Account where, int transfer)
{

}

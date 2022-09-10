#include "account.hh"
#include <iostream>

using namespace std;

Account::Account(const std::string& owner, bool has_credit):
name_(owner), credit_card_(has_credit) {
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

void Account::set_credit_limit(int limit)
{
    if (credit_card_ != 0) {
        credit_ = limit;

    } else {
        cout << "Cannot set credit limit: the account has no credit card" <<endl;
    }
}

void Account::save_money(int amount)
{
    balance_ += amount;
}

bool Account::take_money(int taken)
{
    if (balance_ < taken and credit_card_ != 0) {
        if (-credit_ <= balance_ - taken) {
            balance_ -= taken;
            cout << taken << " euros taken: new balance of "
            << iban_ << " is " << balance_ << " euros" << endl;
            return balance_;
        } else {
            cout << "Cannot take money: credit limit overflow" <<endl;
            return 0;
        }
    } else if (balance_ < taken) {
        cout << "Cannot take money: balance overflow" <<endl;
        return 0;
    } else {
        balance_ -= taken;
        cout << taken << " euros taken: new balance of "
        << iban_ << " is " << balance_ << " euros" << endl;
        return balance_;
    }
}

void Account::transfer_to(Account& where, int transfer)
{
    if (take_money(transfer) != 0) {
        where.balance_ += transfer;
    } else {
        cout << "Transfer from " << iban_ << " failed" <<endl;
    }
}

void Account::print() const
{
    cout << name_ <<" : "<< iban_ <<" : "<< balance_ <<endl;
}

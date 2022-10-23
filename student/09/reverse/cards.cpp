#include <iostream>
#include <memory>
#include "cards.hh"

using namespace std;

Cards::Cards(): top_( nullptr ) {
}


void Cards::add(int id) {
    std::shared_ptr<Card_data> new_card 
            = std::make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

void Cards::print(std::ostream& s) {
   std::shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;

   while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << std::endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}

bool Cards::remove(int &id)
{
    if (top_ == nullptr) {
        return false;
    } else {
        id = top_->data;
        shared_ptr<Card_data> removed = top_;
        if (top_->next == nullptr) {
            top_ = nullptr;

        } else {
            top_ = top_->next;
        }
    }
    return true;
}

void Cards::reverse()
{
    shared_ptr<Card_data> current = top_;
    shared_ptr<Card_data> prev = nullptr;
    shared_ptr<Card_data> next = nullptr;

    while (current != nullptr) {

        next = current->next;
        current->next = prev;

        prev = current;
        current = next;
    }
    top_ = prev;
}


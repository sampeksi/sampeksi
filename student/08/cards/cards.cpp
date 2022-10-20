#include "cards.hh"

using namespace std;

Cards::Cards(): top_(nullptr), bottom_(nullptr) {

}

Cards::~Cards() {

}

bool Cards::remove(int &id) {
    if (top_ == nullptr) {
        return false;
    } else {
        id = top_->data;
        Card_data* removed = top_;
        if (top_->next == nullptr) {
            top_ = nullptr;
            bottom_ = nullptr;
        } else {
            top_ = top_->next;
        }
        delete  removed;
    }
    return true;
}

void Cards::add(int id) {

    Card_data* new_item = new Card_data{id, nullptr};

    if (top_ == nullptr) {
        top_ = new_item;
        bottom_ = new_item;
    } else {
        new_item->next = top_;
        top_ = new_item;
    }

}

bool Cards::bottom_to_top() {
    if (top_ == nullptr) {
        return false;
    } else {
        Card_data* item = new Card_data{bottom_->data, nullptr};
        item->next = top_;
        top_ = item;
        while (true) {
            if (item->next->next != nullptr) {
                item = item->next;
            }
            else {
                delete item->next;
                item->next = nullptr;
                bottom_ = item;
                break;
            }
        }
        return true;
    }
}

bool Cards::top_to_bottom(){

    if (top_ == nullptr) {
        return false;
    } else {
        if (top_->next == nullptr) {

        } else {
            Card_data* item = new Card_data{top_->data, nullptr};
            top_ = top_->next;
            Card_data* loop = top_;
            while (true) {
                if (loop->next != nullptr) {
                    loop = loop->next;
                } else {
                    loop->next = item;
                    break;
                }
            }
        }

    } return true;
}

void Cards::print_from_top_to_bottom(std::ostream &s) {
    Card_data* print_card = top_;
    while (print_card != nullptr) {
        s << print_card->data <<endl;
        print_card = print_card->next;
    }
}

void Cards::print_from_bottom_to_top(std::ostream &s) {
    Card_data* print_card = top_;
    if (print_card != nullptr) {
     recursive_print(print_card, s);
    }
}

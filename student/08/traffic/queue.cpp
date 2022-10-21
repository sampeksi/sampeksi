#include "queue.hh"
#include <iostream>

using namespace std;

Queue::Queue(unsigned int cycle): cycle_(cycle) {
}

Queue::~Queue() {

}

void Queue::enqueue(const string &reg) {

    if (!is_green_) {
        Vehicle* new_car = new Vehicle{reg, nullptr};

        if (first_ == nullptr) {
        first_ = new_car;
        last_ = new_car;
        } else {
        last_->next = new_car;
        last_ = new_car;
        }
    } else {
        cout << "GREEN: The vehicle " << reg << " need not stop to wait" <<
                endl;
    }
}

void Queue::print() const {

    if (is_green_ and first_ == nullptr) {
        cout << "GREEN: No vehicles waiting in traffic lights" <<endl;
    } else {
        cout << "RED: ";

        if (first_ == nullptr) {
            cout << "No vehicles waiting in traffic lights" <<endl;
        } else {
            cout << "Vehicle(s) ";
            Vehicle* print = first_;
            while (print != nullptr) {
                cout << print->reg_num << " ";
                print = print->next;
            } cout << "waiting in traffic lights" <<endl;
        }
    }

}

void Queue::switch_light() {

    if (first_ == nullptr) {
        if (is_green_) {
            is_green_ = false;
            cout << "RED: ";
        } else {
            is_green_ = true;
            cout << "GREEN: ";
        }
        cout << "No vehicles waiting in traffic lights" <<endl;
    } else {
        if (!is_green_) {
            cout << "GREEN: ";

            if (first_ == nullptr) {
                cout << "No vehicles waiting in traffic lights" <<endl;
            } else {
                cout << "Vehicle(s) ";
                unsigned int count = 1;
                Vehicle* print = first_;

                while (count <= cycle_) {
                    cout << print->reg_num << " ";
                    if (print->next == nullptr) {
                        break;
                    } else {
                        print = print->next;
                        count += 1;
                    }
                } cout <<"can go on " <<endl;
            }

            unsigned int c = 1;


            while (c <= cycle_) {

                if (first_ != nullptr) {
                    dequeue();
                    c += 1;
                }
                else {
                    break;
                }
            }

        }
    }
}

void Queue::reset_cycle(unsigned int cycle) {

    cycle_ = cycle;
}


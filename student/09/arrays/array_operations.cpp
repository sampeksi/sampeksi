#include "array_operations.hh"
#include <algorithm>
#include <iostream>

using namespace std;

int greatest_v1(int *itemptr, int size)
{
    sort(itemptr, itemptr + size);
    return *(itemptr + size -1);
}



int greatest_v2(int *itemptr, int *endptr)
{
    sort(itemptr, itemptr);
    return *(endptr-1);
}

void copy(int *itemptr, int *endptr, int *targetptr)
{
    int *start = itemptr;
    int i = 0;

    while (start + i < endptr) {
        *(targetptr + i) = *(start + i);
        i += 1;
    }
}

void reverse(int *leftptr, int *rightptr)
{
    int i = 0;
    int j = rightptr - leftptr -1;
    int temp = 0;


    while (i < j) {

        temp = *(leftptr + i);
        *(leftptr +i) = *(leftptr + j);
        *(leftptr + j) = temp;

        i += 1;
        j -= 1;

    }

}

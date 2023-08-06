#pragma once
#include <iostream>
#include "String.h"

#define SIZE_MULTIPLICATION 2

using namespace std;


//one element of a list
struct Point {
    int x;
    int y;
    int distance;
};

class Queue
{
    //array of point structures
    Point* array;
    size_t size, capacity;

public:

    Queue();
    size_t getSize() const;
    void put(int x, int y, int distance);
    Point* pop();
    bool isEmpty() const;
    ~Queue();
};
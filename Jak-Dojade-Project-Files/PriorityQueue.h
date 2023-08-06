#pragma once
#include "String.h"

struct nearCity {
    String name;
    int nameIndex;
    int distance;
};

//class which organizes the elements as max-heap, vertex with shortest distance is on the top of a heap
class PriorityQueue {

    nearCity* elements;
    int size;
    int capacity;

public:

    PriorityQueue();
    void heapInsert(nearCity newElement);
    nearCity heapGetMax();
    void heapify(nearCity* A, int i);
    int getSize() const;
    int parent(int i);
    int left(int i);
    int right(int i);
    ~PriorityQueue();

};
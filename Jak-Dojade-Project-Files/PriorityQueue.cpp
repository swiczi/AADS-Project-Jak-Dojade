#include "PriorityQueue.h"
#include "queue.h"

#define FIRST_ELEMENT 0

//basic class constructor
PriorityQueue::PriorityQueue() {
    capacity = DEFAULT_SIZE;
    elements = new nearCity[capacity];
    size = 0;
}

//inserting new element to heap
void PriorityQueue::heapInsert(nearCity newElement) {
    if (size >= capacity) {
        int newCapacity = capacity * SIZE_MULTIPLICATION;
        nearCity* newElements = new nearCity[newCapacity];
        for (int i = 0; i < size; i++) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
        capacity = newCapacity;
    }
    elements[size] = newElement;
    size++;
    if (size != 0) {
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify(elements, i);
        }
    }

}

//getting element from the top of a heap
nearCity PriorityQueue::heapGetMax() {
    nearCity max = elements[FIRST_ELEMENT];
    elements[FIRST_ELEMENT] = elements[size - 1];
    size--;
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(elements, i);
    }
    return max;
}

//function building max heap
void PriorityQueue::heapify(nearCity* A, int i)
{
    int leftChild = left(i);
    int rightChild = right(i);
    //position of minimal element
    int minps;

    if (leftChild < size && (A[leftChild].distance < A[i].distance && A[leftChild].distance != NO_VALUE)) {
        minps = leftChild;
    }
    else {
        minps = i;
    }

    if (rightChild < size && A[rightChild].distance < A[minps].distance && A[rightChild].distance != NO_VALUE) {
        minps = rightChild;
    }

    if (minps != i) {
        swap(A[i], A[minps]);
        heapify(A, minps);
    }
}

//returns current size of a heap
int PriorityQueue::getSize() const {
    return size;
}

//calculating positions of parent, left, right sibling, respectively for given element
int PriorityQueue::parent(int i) {
    return (i - 1) / 2;
}

//position on left sibling
int PriorityQueue::left(int i) {
    return (i * 2) + 1;
}

//position of right sibling
int PriorityQueue::right(int i) {
    return (i * 2) + 2;
}

//destructor of the class
PriorityQueue::~PriorityQueue() {
    //deleting array
    delete[] elements;
}
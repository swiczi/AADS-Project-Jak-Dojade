#include "Queue.h"

//creating array of points in deafult constructor
Queue::Queue() {
    array = new Point[DEFAULT_SIZE];
    size = 0;
    capacity = DEFAULT_SIZE;
}

//getting current size of a queue
size_t Queue::getSize() const {
    return size;
}

//putting new element into a queue
void Queue::put(int x, int y, int distance) {

    //looking if we still have some free space
    if (size >= capacity) {

        //we need to increase length of an array
        size_t newCapacity = size * SIZE_MULTIPLICATION;
        Point* newQueue = new Point[newCapacity];

        //push the content of old queue to new 1
        for (size_t i = 0; i < newCapacity; i++) {
            newQueue[i] = array[i];
        }
        delete[] array;
        array = newQueue;
        capacity = newCapacity;


    }
    array[size].x = x;
    array[size].y = y;
    array[size].distance = distance;
    size++;
}

//removing first element
Point* Queue::pop() {

    Point* first = new Point{ 0, 0 };

    if (!isEmpty()) {

        first->x = array[0].x;
        first->y = array[0].y;
        first->distance = array[0].distance;

        //move array 1 cell to the left
        for (size_t i = 1; i < size; i++) {
            array[i - 1] = array[i];
        }
        size--;
    }

    return first;

}

//returns true if queue is empty
bool Queue::isEmpty() const {
    return size == 0;
}

//destructor of the class
Queue::~Queue() {
    delete[] array;
}
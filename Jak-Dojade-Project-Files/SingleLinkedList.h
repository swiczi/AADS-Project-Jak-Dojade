#pragma once
#include <iostream>
#include "String.h"

using namespace std;

//one element od a list
struct Node {
    String name;
    int value1 = 0;
    int namePosition = 0;
    Node* next = nullptr;
};

class SingleLinkedList
{
    //head pointer
    Node* head;
    //pointer to last element
    Node* last;
    //current size of the list
    size_t size;

public:

    SingleLinkedList();
    void addLast(String name, int value1, int namePosition);
    int getPosition(const String name) const;
    int lookForValue(const String name) const;
    void changeValue(const String name, int value);
    Node* getNode();
    Node* getLast();
    size_t getSize() const;

};
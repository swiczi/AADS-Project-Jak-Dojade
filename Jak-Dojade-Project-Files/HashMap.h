#pragma once
#include <iostream>
#include "String.h"
#include "SingleLinkedList.h"
#include "queue.h"

//structure of with information about 1 city
struct City {
    String cityName;
    Point cityPoint;
};

class HashMap
{
    int numberOfContainers;
    int numberOfElements;
    SingleLinkedList* map;

public:

    HashMap();
    void addWord(String word, Point mapPosition);
    static int getIndex(String word);
    String searchForWord(int position);
    City searchForStructure(int position);
    int getPosition(String name);
    int getSize() const;
    ~HashMap();
    
};
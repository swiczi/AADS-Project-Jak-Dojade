#include "HashMap.h"

#define ALPHABET_LETTERS 26
#define NUMBER_OF_LETTERS 2
#define NUMBERS 10

//default constructor of a class
HashMap::HashMap() {
    //we will be packing words depending on three first letters
    numberOfContainers = ALPHABET_LETTERS * (ALPHABET_LETTERS + NUMBERS) * (ALPHABET_LETTERS + NUMBERS);
    numberOfElements = 0;
    //making an array of lists
    map = new SingleLinkedList[numberOfContainers];

}

//adding given word to proper container
void HashMap::addWord(String word, Point mapPosition) {

    int id = getIndex(word);
    map[id].addLast(word, mapPosition.x, mapPosition.y);
    numberOfElements++;

}

//calculate index number for given word
int HashMap::getIndex(String word) {

    int index = 0, firstIndex = word[0] - 'A', secondIndex, thirdIndex;
    index = (firstIndex) * (ALPHABET_LETTERS + NUMBERS) * (ALPHABET_LETTERS + NUMBERS);
    //word is at least 2 characters
    if (word.getLength() >= NUMBER_OF_LETTERS) {
        secondIndex = word[1] - 'A';

        //second letter belongs to ALPHABET_LETTERS -> is not a number
        if (word[1] >= 'A' && word[1] <= 'Z') {
            index += secondIndex * (ALPHABET_LETTERS + NUMBERS);
        }
        else {
            secondIndex = word[1] - '0';
            index += (ALPHABET_LETTERS + secondIndex) * (ALPHABET_LETTERS + NUMBERS);
        }

        //word has at least 3 letters
        if (word.getLength() >= NUMBER_OF_LETTERS + 1) {
            thirdIndex = word[2] - 'A';

            //third index in a letter
            if (word[2] >= 'A' && word[2] <= 'Z') {
                index += thirdIndex;
            }
            //third index is a number
            else {
                thirdIndex = word[2] - '0';
                index += thirdIndex + ALPHABET_LETTERS;
            }
        }

    }

    return index;
}

//searching containers for word at given posititon
String HashMap::searchForWord(int position) {
    int currentPosition = 0, size, i;
    String* word = new String("");

    for (i = 0; i < numberOfContainers; i++) {

        size = map[i].getSize();
        if (currentPosition + size >= position + 1) {

            //search current list for given posiiton
            Node* tmp = map[i].getNode();
            while (currentPosition < position) {
                tmp = tmp->next;
                currentPosition++;
            }
            word = new String(tmp->name);
            break;
        }
        currentPosition += size;
    }

    return *word;

}

//searching containers for word at given posititon
City HashMap::searchForStructure(int position) {
    int currentPosition = 0, size, i;
    Point* point = new Point;
    String* word = new String("");
    City structure;

    for (i = 0; i < numberOfContainers; i++) {

        size = map[i].getSize();
        if (currentPosition + size >= position + 1) {

            //search current list for given posiiton
            Node* tmp = map[i].getNode();
            while (currentPosition < position) {
                tmp = tmp->next;
                currentPosition++;
            }
            word = new String(tmp->name);
            point = new Point{ tmp->value1, tmp->namePosition };
            structure.cityName = *word;
            structure.cityPoint = *point;
            break;
        }
        currentPosition += size;
    }

    delete[] point;

    return structure;

}

//searching what is the current position in array of given word
int HashMap::getPosition(String name) {

    int size = 0, i;
    int index = getIndex(name);
    int listIndex = map[index].getPosition(name);

    //adding occupations of lists that occur before
    for (i = 0; i < index; i++) {
        size += map[i].getSize();
    }

    return size + listIndex;

}

//return current size of hashmap
int HashMap::getSize() const {
    return numberOfElements;
}

//destructor
HashMap::~HashMap() {
    //freeing memory
    delete[] map;
}
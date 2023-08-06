#include "SingleLinkedList.h"

//initializing head pointer with deafult constructor
SingleLinkedList::SingleLinkedList() :head(nullptr), last(nullptr), size(NULL) { }

//adding new element to list, on the lastest position
void SingleLinkedList::addLast(String name, int value1, int namePosition) {

    //allocating memory
    Node* newNode = new Node;

    //preparing newNode
    newNode->name.setWord(name);
    newNode->value1 = value1;
    newNode->namePosition = namePosition;
    newNode->next = NULL;

    if (head == nullptr) {
        head = newNode;
        last = newNode;
    }
    else {

        Node* tmp = getLast();
        tmp->next = newNode;
        last = newNode;
    }
    size++;

}

//getting position index of given name
int SingleLinkedList::getPosition(const String name) const {
    Node* tmp = head;
    int i = NULL;

    while (tmp != nullptr) {
        //searching for a name
        if (tmp->name == name)  return i;
        i++;
        tmp = tmp->next;
    }

    return NO_VALUE;

}

//getting value of given name
int SingleLinkedList::lookForValue(const String name) const {
    Node* tmp = head;
    int i = NULL;

    while (tmp != nullptr) {
        //searching for name and its value
        if (tmp->name == name) {
            i = tmp->value1;
            return i;
        }

        tmp = tmp->next;
    }

    return NO_VALUE;
}

//searching for given name and changing its value
void SingleLinkedList::changeValue(const String name, int value) {
    Node* tmp = head;
    int i = 0, position = getPosition(name);

    while (tmp != nullptr) {
        if (i == position) {
            tmp->value1 = value;
            break;
        }
        i++;
        tmp = tmp->next;
    }

}

//getting head element
Node* SingleLinkedList::getNode() {
    return head;
}

//getting pointer to last element
Node* SingleLinkedList::getLast() {
    return last;
}

//returning current size of a list
size_t SingleLinkedList::getSize() const {
    return size;
}

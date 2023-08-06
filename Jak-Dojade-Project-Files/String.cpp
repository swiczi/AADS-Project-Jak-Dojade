#include "String.h"

//function to clean & delete string
void String::cleanBuffer() {
    if (word != nullptr)
        delete[] word;
    word = nullptr;
}

//deafult constructor
String::String() {
    word = new char[1];
    word[NULL] = '\0';
    size = 1;
    length = NULL;
}

//constructor with char*
String::String(const char* buffer)
{
    size_t str = strlen(buffer);

    length = str;
    size = str + 1;
    word = new char[size];

    strcpy_s(word, size, buffer);
    word[length] = '\0';

}

//constructor with const String
String::String(const String& buffer)
{
    size_t str = buffer.getLength();
    length = str;
    size = str + 1;
    word = new char[size];

    strcpy_s(word, size, buffer.word);
    word[length] = '\0';
}

//copy assignment operator with const char* buffer
String& String::operator=(const char* buffer)
{
    String tmp(buffer);
    swap(word, tmp.word);
    swap(size, tmp.size);
    swap(length, tmp.length);

    return *this;
}

//copy assignment operator with const String buffer
String& String::operator=(const String& buffer)
{
    String tmp(buffer);
    swap(word, tmp.word);
    swap(size, tmp.size);
    swap(length, tmp.length);

    return *this;
}

//comparing word with const char* buffer
bool String::operator==(const char* buffer) const
{
    if (length != strlen(buffer)) {
        return false;
    }

    for (size_t i = NULL; i < length; i++) {
        if (word[i] != buffer[i]) {
            return false;
        }
    }

    return true;
}

//comparing word with const char* buffer
bool String::operator!=(const char* buffer) const
{
    return !(word == buffer);
}

//comparing object with const String buffer
bool String::operator==(const String& buffer) const
{
    if (length != buffer.getLength()) {
        return false;
    }

    for (size_t i = NULL; i < length; i++) {
        if (word[i] != buffer[i]) {
            return false;
        }
    }

    return true;
}

//comparing object with const String buffer
bool String::operator!=(const String& buffer) const
{
    return !(*this == buffer);
}

//getting char at given index of a word array
char& String::operator[](std::size_t index) {
    return word[index];
}

//getting const char at given index of a word array
const char& String::operator[](std::size_t index) const {
    return word[index];
}

//getting current string length
size_t String::getLength() const {
    return length;
}

//getting current word
const char* String::getWord() const
{
    return word;
}

//getting current size of a buffer
size_t String::getSize() const
{
    return size;
}

//setting name of a non existing object
void String::setWord(const String& str) {
    length = str.getLength();
    size = length + 1;
    word = new char[size];
    strcpy_s(word, size, str.word);
    word[length] = '\0';
}

//destructor of the class
String::~String() {

    //deleting assigned memory
    cleanBuffer();
}

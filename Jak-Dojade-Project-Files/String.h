#pragma once
#include <iostream>
#include <cstring>

#define DEFAULT_SIZE 100
#define NO_VALUE -1

using namespace std;

//preparing self-implemented string class
class String {

    //initializing array of chars
    char* word = nullptr;
    //size of a buffer
    size_t size = NULL;
    //current length of a string
    size_t length = NULL;

    void cleanBuffer();
    friend std::ostream& operator<<(std::ostream& os, const String& s);
    friend std::istream& operator>>(std::istream& is, String& s);

public:

    //constructors
    String();
    String(const char* buffer);
    String(const String& buffer);

    //functions to handle copy assignment operators
    String& operator=(const char* buffer);
    String& operator=(const String& buffer);

    //functions to handle comparing operators
    bool operator==(const char* buffer) const;
    bool operator!=(const char* buffer) const;
    bool operator==(const String& buffer) const;
    bool operator!=(const String& buffer) const;

    char& operator[](std::size_t index);
    const char& operator[](std::size_t index) const;
    size_t getLength() const;
    const char* getWord() const;
    size_t getSize() const;
    void setWord(const String& str);
    ~String();

};

//handling cout<< operator
inline std::ostream& operator<<(std::ostream& out, const String& str)
{
    out << str.word;
    return out;
}

//handling cin>> operator
inline std::istream& operator>>(std::istream& in, String& str)
{
    char* buffer = new char[DEFAULT_SIZE];
    in >> buffer;

    //handling given string, using proper constructor
    if (in) str = String(buffer);
    else    str = String();

    delete[] buffer;
    return in;
}
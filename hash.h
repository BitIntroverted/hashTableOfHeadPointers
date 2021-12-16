/*
 * 	Name: Lukas Friedrich
 * 	Exam 2
 * 	Hashtable header
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#define HASHTABLESIZE 15

#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

struct Data {
    int id;
    string information;
};

struct Node {
    Data data;
    Node* next;
};


class Hashtable {

public:

    Hashtable();
    ~Hashtable();

    bool insertEntry(int, string*);
    string getData(int);
    bool removeEntry(int);
    int getCount();
    void printTable();

private:


    int count;
    int hash(int);
    Node* head[HASHTABLESIZE];

};

#endif /*HASHTABLE_H*/
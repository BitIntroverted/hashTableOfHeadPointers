/*
 * 	Name: Lukas Friedrich
 * 	Exam 2
 * 	Hashtable class
 */

#include "hash.h"

Hashtable::Hashtable() {
    count = 0;
    for (int i = 0; i < HASHTABLESIZE; i++) {
        head[i] = nullptr;
    }
}

Hashtable::~Hashtable() {
    Node* temp;
    bool cleared = false;
    for (int i = 0; i < HASHTABLESIZE; i++) {
        Node* current = head[i];
        while (current)
        {
            temp = current->next;
            delete current;
            current = temp;
        }
    }
}

/************************************
 * Private
 ************************************/
int Hashtable::hash(int id) {
    return id % HASHTABLESIZE;
}

/************************************
 * Public
 ************************************/

bool Hashtable::insertEntry(int id, string* info) {
    bool inserted = false;
    bool exists = false;
    if (id > 0) {
        int hashedID = hash(id);
        Node* current = head[hashedID];
        while (current && current->data.id != id)
        {
            current = current->next;
        }
        if (current && current->data.id == id) {
            exists = true;
        }
        if (!exists && *info != "") {
            Node* temp = new Node;
            temp->next = head[hashedID];
            temp->data.id = id;
            temp->data.information = *info;
            head[hashedID] = temp;
            inserted = true;
            count++;
        }
    }
    return inserted;
}

string Hashtable::getData(int id) {
    string ret = "";
    int hashedID = hash(id);
    Node* current = head[hashedID];
    if (id > 0) {
        while (current && current->data.id != id)
        {
            current = current->next;
        }
        if (current && current->data.id == id) {
            ret = current->data.information;
        }
    }
    return ret;
}

bool Hashtable::removeEntry(int id) {
    bool removed = false;
    bool exists = false;
    if (id > 0) {
        int hashedID = hash(id);
        Node* previous = nullptr, * current = head[hashedID];
        while (current && current->data.id != id)
        {
            previous = current;
            current = current->next;
        }
        if (current && current->data.id == id) {
            exists = true;
        }
        if (exists && id == current->data.id) {
            if (!previous && current->next) { //replace head
                head[hashedID] = current->next;
                delete current;
                removed = true;
            }
            else if (!current->next && previous) { //replace tail
                previous->next = nullptr;
                delete current;
                removed = true;
            }
            else if (current->next && previous) { //replace middle
                previous->next = current->next;
                delete current;
                removed = true;
            }
            else if (!previous && !current->next) { //solo node case
                delete current;
                head[hashedID] = nullptr;
                removed = true;
            }
        }
    }
    if (removed == true) { count--; }
    return removed;
}


int Hashtable::getCount() {
    return count;
}

void Hashtable::printTable() {
    for (int i = 0; i < HASHTABLESIZE; i++) {
        Node* current = head[hash(i)];
            while (current) {
                std::cout << current->data.id << ": " << current->data.information << std::endl;
                current = current->next;
            }
    }
}
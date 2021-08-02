/* 
 * File: hashtable.h
 * Author: Nitish Malluru
 * 
 * header file for hashtable.cpp
 * 
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#define SIZE 15

//#include "linkedlist.h"

#include <iostream>
#include "data.h"

using std::cout;
using std::endl;

class HashTable {

public:

    /* 
     * write all your public method prototypes here
     * this includes you constructor and destructor
     */
    HashTable();
    bool insertEntry(int, string*);
    string getData(int); 
    bool removeEntry(int);
    int getCount();
    void printTable();
    ~HashTable();

    bool addNode(int, int, string*);
    bool deleteNode(int, int);
    bool getNode(int, int, Data*);
    void printList(int, bool = false);
    int getInCount(int);
    bool clearList(int);
    bool exists(int, int);

    
private:

    /* 
     * write all your private method prototypes here
     */
    Node *hashTable[SIZE]; 
    int hash(int); 
    int count;

    bool findID(int, int, Node **);
    void createNode(Node*, Node*, int, string);
    void deleteHead(int, Node*);
    int getLast(int, Node**);
    void createHead(int, int, string);
    void addAfterHead(int, string, Node*);
};

#endif //HASH_TABLE_H
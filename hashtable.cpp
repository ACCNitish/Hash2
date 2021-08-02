/* 
 * File: hashtable.cpp
 * Author: Nitish Malluru
 * 
 * This file will be used to demonstrate 
 * my knowledge of hastables
 * 
 */

#include "hashtable.h"

HashTable::HashTable(){
    for(int i = 0; i < SIZE; i++){
        hashTable[i] = new Node();
        hashTable[i] = nullptr;
    }
    count = 0;
}

bool HashTable::insertEntry(int id, string* data){
    bool sucess = false;
    if(id >= 0){
        int hashId = hash(id);
        sucess = addNode(hashId, id, data);
        if(sucess){
            count++;
        }
    }
    return sucess;
}

string HashTable::getData(int id){
    string sucess = "";
    if(id >= 0){
        int hashId = hash(id);
        Data *getInfo = new Data();
        getNode(hashId, id, getInfo);
        sucess = getInfo->data;
    }
    return sucess;
}

bool HashTable::removeEntry(int id){
    bool sucess = false;
    if(id >= 0){
        int hashId = hash(id);
        sucess = deleteNode(hashId, id);
        if(sucess){
            count--;
        }
    }
    return sucess;
}

int HashTable::getCount(){
    return count;
}

void HashTable::printTable(){
    for(int i = 0; i < SIZE; i++){
        cout << "Entry " << i+1 << ":";
        int listSize = getInCount(i);
        if(listSize == 0){
            cout << "EMPTY" << endl;
        }else{
            printList(i);
        }
    }
}

int HashTable::hash(int id){
    return id % SIZE;
}


bool HashTable::addNode(int hashId, int x, string* info){
    bool addSucces = false;
    if(x > 0 && !info->empty()){
        Node *add = hashTable[hashId];
        if(findID(hashId, x, &add)){
            if(add == nullptr && hashTable[hashId] == nullptr){
                createHead(hashId, x, *info);
            }else{
                addAfterHead(x, *info, add);
            }  
            addSucces = true;
        }else{
            delete add;
            add = nullptr;
        }
    }
    return addSucces;
}

bool HashTable::findID(int hashId, int x, Node **add){
    bool unique = true;
    bool found = false;
    Node *curr = hashTable[hashId];
    *add = nullptr;
    while(curr != nullptr && !found && unique){ 
        if(x != curr->data.id){
            if (!curr->next){
                *add = curr;
                found = true;
            }
            curr = curr->next;
        }
        else{
            unique = false;   
        }
    }
    return unique;
}

bool HashTable::deleteNode(int hashId, int deleteId){
    Node *curr = hashTable[hashId];
    Node *prevPoin = hashTable[hashId];
    bool deleteSuccess = false;
    while (curr != nullptr && !deleteSuccess){
        if(deleteId == curr->data.id){
            if(curr->data.id == hashTable[hashId]->data.id){
                deleteHead(hashId, curr);
            }
            else{
                prevPoin->next = curr->next;
                delete curr;
                curr = nullptr;
            }
            deleteSuccess = true;
        }
        else {
            prevPoin = curr;
            curr = curr->next;
        }
    }
    return deleteSuccess;
}

bool HashTable::getNode(int hashId, int x, Data* emptyData){
    emptyData->id = -1;
    emptyData->data = "";
    bool exist = false;
    Node *curr = hashTable[hashId];
    while (curr != nullptr && !exist){
        if(x == curr->data.id){
            emptyData->id = curr->data.id;
            emptyData->data = curr->data.data;
            exist = true;
        }
        curr = curr->next;
    }
    return exist;
}

void HashTable::printList(int hashId, bool backward){
    if(!backward){
        Node *curr = hashTable[hashId];
        bool tail = false;
        while(curr && !tail){ 
            if(curr->next){
                cout << curr->data.id << "-->";
                curr = curr->next;
            }else{
                tail = true;
            }
        }  
        cout << curr->data.id << endl;
    }
}

int HashTable::getInCount(int hashId){ 
    Node *curr = hashTable[hashId];
    int countIn = 0;
    bool tail = false;
    while(curr && !tail){ 
        curr = curr->next;
        countIn++;
    }
    return countIn;
}

bool HashTable::clearList(int hashId){
    bool clearListSucess = false;
    Node *curr = hashTable[hashId];
    int count = getLast(hashId, &curr);
    bool tail = false; 
    if(count > 0){
        for(int i = 0; i < count; i++){
            Node *next = curr->next;
            deleteNode(hashId, curr->data.id);
            
            curr = next;
        }
        clearListSucess = true;
    }   
    return clearListSucess;
}

bool HashTable::exists(int hashId, int x){
    Node *curr = hashTable[hashId];
    bool tail = false;
    bool exists = false;

    while(curr && !tail){
        if(curr->data.id){
            exists = true;
        }
        if (curr->next){
            curr = curr->next;
        } else {
            tail = true;
        }
    }
    return exists;
}

void HashTable::createNode(Node* toCreate, Node* next, int x, string info){
    toCreate->next = next;
    Data *addData = new Data;
    addData->id = x;
    addData->data = info;
    toCreate->data = *addData;
}

void HashTable::deleteHead(int hashId, Node* curr){
    if(curr->next == nullptr){
        hashTable[hashId] = nullptr;
    }else
    {
        hashTable[hashId] = curr->next;
    }
    delete curr;
    curr = nullptr;
}


int HashTable::getLast(int hashId, Node** curr){
    Node *iter = hashTable[hashId];
    int count = 0;
    bool tail = false; 
    while(iter && !tail){
        count++;
        if (iter->next){
            iter = iter->next;
        }
        else{
            tail = true; 
        }
    }
    *curr = iter;
    return count;
}

void HashTable::createHead(int hashId, int x, string info){
    Node *firstNode = new Node; 
    createNode(firstNode, nullptr, x, info);
    hashTable[hashId] = firstNode;
}


void HashTable::addAfterHead(int x, string info, Node* add){
    Node *addNode = new Node();
    createNode(addNode, add->next, x, info);

    add->next = addNode; 
}

HashTable::~HashTable(){
    for(int i = 0; i < SIZE; i++){
        clearList(i);
        delete hashTable[i];
        hashTable[i] = nullptr;
    }
}




/* 
 * File: main.cpp
 * Author: Nitish Malluru
 * 
 * This file will be used to test my 
 * seperate chaining hastable
 * 
 */

#include "main.h"

int main() {
    srand(time(NULL));

    const int testdatasize = BASE + (rand() % OFFSET + 1);
    int ids[testdatasize];
    string strs[testdatasize];
    
    char buffer[BUFFERSIZE];
    for (int i = 0; i < testdatasize; i++) {
        ids[i] = rand() % MAXID + 1;
        for (int j = 0; j < BUFFERSIZE - 1; j++) {
            buffer[j] = 'a' + i;
        }
        buffer[BUFFERSIZE - 1] = '\0';
        strs[i] = buffer;
    }
    ids[testdatasize-2] = ids[testdatasize-3];
    strs[testdatasize-2] = "known duplicate";
    ids[testdatasize-1] = - 1;
    strs[testdatasize-1] = "known bad";
    
    cout << "Showing Test Data (" << testdatasize << " entries)..." << endl;
    for (int i = 0; i < testdatasize; i++) {
        cout << ids[i] << " : " << strs[i] << endl;
    }
    cout << endl;

    HashTable table;

    cout << "The length of the HashTable is " << table.getCount() << endl << endl;
    table.printTable();
    cout << endl;

    for(int i = 0; i < testdatasize; i++){
        table.insertEntry(ids[i], &strs[i]);
    }
    table.printTable();
    cout<< endl;
    cout << "Emptying the hashtable"<<endl;
    cout<< endl;
    for(int i = 0; i < testdatasize-1; i++){
        table.removeEntry(ids[i]);
    }
    table.printTable();
    cout << endl;
    
    for(int i = 0; i < SIZE*10; i++){
        int random = rand()%10;
        int randId = rand()%testdatasize;
        int randInfo = rand()%testdatasize;
        if (random <=10 && random > 3){
            if(table.insertEntry(ids[randId], &strs[randInfo])){
                cout << "INSERT: The addition of " << strs[randInfo] << " at id "<< ids[randId] << " was sucessful" <<endl;
            }else{
                cout << "INSERT: The addition of id " << ids[randId] << " to the HashTable was unsuccesful" << endl;
            }
        }else if(random == 3){
            if(table.removeEntry(ids[randId])){
                cout << "REMOVE: The removal of id "<< ids[randId] << " was sucessful" <<endl;
            }else{
                cout << "REMOVE: The removal of id " << ids[randId] << " to the HashTable was unsuccesful" << endl;
            }
        }else if(random == 2){
            cout << "PRINT:" << endl;
            table.printTable();
        }else if(random == 1){
            cout << "COUNT:  The length of the HashTable is " << table.getCount() << endl;
        }else{
            string data = table.getData(ids[randId]);
            if(data.length() == 0){
                cout << "GET:    The id " << ids[randId] << " does not exist in the HashTable" << endl; 
            }else{
                cout << "GET:    The data of " << data << " is found at id "<< ids[randId] << endl; 
            }
        }
    }

    
    return 0;
}

#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>
#include <string>
#include<cstdio>
#include<sstream>
#include<algorithm>
#include <utility>
#include <vector>
#include <IndexInterface.h>
#include <random>
#include <list>
using namespace std ;

template<class T>
class HashMap
{
    int BUCKET = 2000000000;    // No. of buckets

    // Pointer to an array containing buckets
    list<pair<T,vector<T>>> *table;
public:
    HashMap(){
        table = new list<int>[BUCKET];
        srand(5);
    }  // Constructor

    HashMap(int V){
        this->BUCKET = V;
        table = new list<int>[BUCKET];
        srand(5);
    }  // Constructor

    // inserts a key into hash table
    void addWord(string word){
        vector<T> tempVec;
        pair<T,vector<T>> temp = make_pair(word, tempVec);
        int index = hashFunction(word);
        table[index].push_back(word);
    }

    void addDoc(string doc, string word){
        table[(hashFunction(word))].second.push_back(doc);
    }

    // deletes a key from hash table
    void deleteItem(int key){
        // get the hash index of key
        int index = hashFunction(key);

        // find the key in (inex)th list
        list <int> :: iterator i;
        for (i = table[index].begin();
                 i != table[index].end(); i++) {
          if (*i == key)
            break;
        }

        // if key is found in hash table, remove it
        if (i != table[index].end())
          table[index].erase(i);
    }

    // hash function to map values to key
    int hashFunction(int x) {
        return (x % (rand()%BUCKET));
    }

    void displayHash(){
        for (int i = 0; i < BUCKET; i++) {
          cout << i;
          for (auto x : table[i])
            cout << " --> " << x;
          cout << endl;
        }
    }
};

#endif // HASHMAP_H

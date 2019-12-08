#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
#include <algorithm>
#include <utility>
#include <vector>
#include <IndexInterface.h>
#include <random>
#include <list>
using namespace std ;

template<class T>
class HashMap : public IndexInterface{
private:
    int BUCKET = 200000;    // No. of buckets
    bool empty = true;
    vector<vector<pair<T,vector<pair<T,int>>>>> * table; // use holy hell this is a dumb-ass line

public:
    HashMap(){
        table = new vector<vector<pair<T,vector<pair<T,int>>>>>[BUCKET];
    }  // Constructor

    void add(T data, T data2){
        int index = hashFunction(data);
        int temp = -1;

    }

    ~HashMap(){
        destroy();
    }

    void destroy() override{
        empty = true;
        delete table;
    }

    void addFirst(T data){
    //    table[(hashFunction(word))].second.push_back(doc);
        int index = hashFunction(data);
        vector<pair<T,int>> nullVec;
        table[index].push_back(make_pair(data, nullVec)); // ????
        empty = false;
    }

    void addSec(T data, T data2){ // fuck this method
        int index = hashFunction(data);
        for(int i = 0; i < table[index].size(); i++){ // goes through the list of collisions
            if(table[index][i].first == data){ // finds the pair in the collision vector that has the same name
                for(int j = 0; i < table[index][j].second.size(); j++){ // goes through the vecotr matched to the word
                    if(table[index][i].second[j].first == data2){ // if the value in that vector is equal to the doc title or whatever is in there
                        table[index][i].second[j].second++; //adds a number to the seen per doc value in the right box
                    }
                }
                table[index][i].second.push_back(make_pair(data2, 1));
            }
        }
        if(table[index].size() == 0){
            table[index] = (make_pair(data2, 1));
        }
    }

    void deleteItem(T key){ // dont think i really need this rn
        int index = hashFunction(key);

    }

    // hash function to map values to key
    int hashFunction(string data) {
        //int fei = static_cast<int>(data);
        return (((long int)data.c_str()*17+4*3-85*10) %BUCKET);
    }

    int hashFunction(int data){
        //doesnt really matter for this usage
    }

    void displayHash(){ // for testing mostly
        for (int i = 0; i < BUCKET; i++) {
          cout << i;
          for (auto x : table[i])
            cout << " --> " << x.first << " -> " << x.second.size();
          cout << endl;
        }
    }

    void rf() override{

    }
    void pof() override{

    }

//    void add(string, string) override{

//    }
    void access(T data, vector<pair<string, int>> &docs){
        int index = hashFunction(data);
        for(int i = 0; i < table[index].size(); i++){ // goes through the list of collisions
            if(table[index][i].first == data){ // finds the pair in the collision vector that has the same name
                docs = table[index][i].second; //sets the passby to the correct vector value
                return;
            }
        }

    }

    vector<pair<T, int>> access(T data){
        //return access(data, root);
    }
    bool isEmpty() override{
        return empty;
    }

};

#endif // HASHMAP_H

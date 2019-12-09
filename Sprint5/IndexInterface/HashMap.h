#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>
#include <string>
#include <cstdio>
#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <utility>
#include <vector>
#include <IndexInterface.h>
#include <random>
#include <list>
#include <fstream>
#include <string>
#include <sstream>
#include <ostream>
using namespace std ;

template<class T>
class HashMap : public IndexInterface{
private:
    int BUCKET = 200000;    // No. of buckets
    bool empty = true;
   // vector<vector<pair<T,vector<pair<T,int>>>>> * table; // use holy hell this is a dumb-ass line
    vector<pair<T,vector<pair<T,int>>>> * table[200000];
    ofstream outFile;

public:
    HashMap(){
      //  table = new vector<vector<pair<T,vector<pair<T,int>>>>>[BUCKET];
        outFile.open("/home/student/Desktop/index.txt");
    }  // Constructor

    void add(T data, T data2){ // finsih me
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
        table[index]->push_back(make_pair(data, nullVec)); // ????
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

    void rf() override{ //read file
        ifstream out;
        if(!out.is_open()){
            out.open("/home/student/Desktop/index.txt");
        }
        string first;
        string sec;
        string num;
        string line;
        int pNum;
        int index;
        while(outFile){
                getline(out, first, '|'); // gets word / first item
               // index = hashFunction(first);
                addFirst(first);
                getline(out, line);
                while(line != ""){ // this might go forever
                    num = strtok((char*)line.c_str(), "-");
                    sec = strtok((char*)num.c_str(), ":");
                    pNum = stoi(num);
                    addSecF(first, sec, pNum);
                }
        }
    }
    void pof() override{ // print out file
        for(int i = 0; i < table->size(); i++){
            for(int j = 0; j < table->at(i).size(); j++){
                outFile << table->at(i).at(j).first << "|"; // word
                for(int k = 0; k < table->at(i).at(j).second.size(); k++){
                    outFile << table->at(i).at(j).second.at(k).first << ":" << table->at(i).at(j).second.at(k).second << "-";
                }
                outFile << endl;
            }
        }
    }

//    void add(string, string) override{

//    }
    void access(T data, vector<pair<string, int>> &docs){
        int index = hashFunction(data);
        for(int i = 0; i < table[index].size(); i++){ // goes through the list of collisions
            if(table->at(index).at(i).first == data){ // finds the pair in the collision vector that has the same name
                docs = table->at(index).at(i).second; //sets the passby to the correct vector value
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

    void addSecF(T data, T data2, int num){
        int index = hashFunction(data);
        for(int i = 0; i < table[index].size(); i++){ // goes through the list of collisions
            if(table->at(index).at(i).first == data){ // finds the pair in the collision vector that has the same name
                table->at(index).at(i).second.push_back(make_pair(data2, num)); // if the doc is not in the vector add it
            }
        }
    }

};

#endif // HASHMAP_H

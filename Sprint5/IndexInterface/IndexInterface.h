#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H

#include <iostream>
#include <vector>

using namespace std;

//template<class T>
class IndexInterface{
public:
    //virtual void addFirst(string) = 0;
    //virtual void addSec(string, string) = 0;
    virtual vector<pair<string, int>> access(string data) = 0;
    //virtual vector<string> access(string data) = 0;
//    virtual void write() = 0;
    //virtual void readFromFile() = 0;
    //virtual
    virtual void destroy() = 0;
    virtual void add(string, string) = 0;
    virtual void rf() = 0;
    virtual void pof() = 0;
    virtual bool isEmpty() = 0;
};


#endif // INDEXINTERFACE_H

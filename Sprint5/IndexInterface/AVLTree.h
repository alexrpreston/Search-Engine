#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <string>
#include <utility>

using namespace std;
template<class T>

struct Node{
    T data;
    int height;
    Node * left;
    Node * right;
};

#endif // AVLTREE_H

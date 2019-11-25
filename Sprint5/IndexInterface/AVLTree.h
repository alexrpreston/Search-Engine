#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
#include <IndexInterface.h>
#include <string.h>
#include <stdio.h>

using namespace std;

template<class T>
struct Node{
    pair<T,vector<T>> data; // each word has a vector of the docs that contain the word
    Node * left;
    Node * right;
    int height;
};

template<class T>
class AVLTree : public IndexInterface {
private:
    Node<string> * root = nullptr;
    int numNodes = 0;

public:
    int getNumNodes(){
        return numNodes;
    }

    int height(Node<T> * N)
    {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    int max(int a, int b)
    {
        return (a > b)? a : b;
    }

    Node<T> * newNode(T key)
    {
        Node<T> * node = new Node<T>();
        node->data.first = key;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1; // new node is initially
                          // added at leaf
        return(node);
    }

    Node<T> * llRotate(Node<T> * parent){
        Node<T> * k1 = parent->left;
        parent->left = k1->right;
        k1->right = parent;
        parent->height = max(height(parent->left), height(parent->right)) + 1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        if(parent == root){
            root = k1;
        }
        return k1;
    }

    Node<T> * rrRotate(Node<T> * parent){
        Node<T> * k1 = parent->right;
        parent->right = k1->left;
        k1->left = parent;
        parent->height = max(height(parent->left), height(parent->right)) + 1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        if(parent == root){
            root = k1;
        }
        return k1;
    }

    Node<T> * rlRotate(Node<T> * parent){
        Node<T> * k = parent->right;
        parent->right = llRotate(k);
        return rrRotate(parent);
    }

    Node<T> * lrRotate(Node<T> * parent){
        Node<T> * k = parent->left;
        parent->left = rrRotate(k); //sets to ll case, works
        return llRotate(parent);

    }

    int getBalance(Node<T> * Node)
    {
        if (Node == nullptr)
            return 0;
        return height(Node->left) - height(Node->right);
    }

    void addFirst(T data){
        addFirst(root, data);
    }

    Node<T> * addFirst(Node<T> * node, T data){
        if(root == nullptr){
            Node<T> * nNode = newNode(data);
            root = nNode;
        }
        if (node == nullptr){
            Node<T> * nNode = newNode(data);
            nNode->left = nullptr;
            nNode->right = nullptr;
            numNodes++;
            return(nNode);
        }

        if (data < node->data.first){
            node->left = addFirst(node->left, data);
        }
        else if (data > node->data.first){
            node->right = addFirst(node->right, data);
        }
        else{
            return node;
        }

        node->height = 1 + max(height(node->left),
                            height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && data < node->left->data.first) // ll
            return llRotate(node);

        if (balance < -1 && data > node->right->data.first) // rr
            return rrRotate(node);

        if (balance > 1 && data > node->left->data.first) // lr
        {
            return lrRotate(node); //returns new pviot
        }

        if (balance < -1 && data < node->right->data.first)  // rl
        {
            return rlRotate(node);
        }

        return node;
    }

    void preOrder(){
        preOrder(root);
    }

    void preOrder(Node<T> * root){
        if(root != nullptr)
        {
            cout << root->data.first << endl;
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    vector<T> access(T data){
        return access(data, root);
    }

    vector<T> access(T data, Node<T> * curr){ // return value can be changed for query
        if(strcmp(curr->data.first.c_str(), data.c_str()) < 0){ //neg if search is larger
            curr == curr->right;
            access(data, curr);
        }
        else if(strcmp(curr->data.first.c_str(), data.c_str()) > 0){ // if search is larger
            curr == curr->left;
            access(data, curr);
        }
        else if(strcmp(curr->data.first.c_str(), data.c_str()) == 0){
            return curr->data.second;
        }
        else{
            cout << "nothing" << endl;
        }

    }

    void addSec(T data, T doc){
        addSec(data, doc, root);
    }

    void addSec(T data, T newDoc, Node<T> * curr){
        if(strcmp(curr->data.first.c_str(), data.c_str()) < 0){ //neg if search is larger
            curr = curr->right;
            addSec(data, newDoc, curr);
        }
        else if(strcmp(curr->data.first.c_str(), data.c_str()) > 0){ // if search is larger
            curr = curr->left;
            addSec(data, newDoc, curr);
        }
        else if(strcmp(curr->data.first.c_str(), data.c_str()) == 0){
            curr->data.second.push_back(newDoc);
            return;
        }
        else
            return;
    }


};



#endif // AVLTREE_H

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

    Node<T> * rightRotate(Node<T> * parent)
    {
        Node<T> * x = parent->left;
        Node<T> * T2 = x->right;

        x->right = parent;
        parent->left = T2;

        parent->height = max(height(parent->left),
                        height(parent->right)) + 1;
        x->height = max(height(x->left),
                        height(x->right)) + 1;

        return x;
    }

    Node<T> * leftRotate(Node<T> * parent)
    {
        Node<T> * rChild = parent->right;
        Node<T> * rlChild = rChild->left;

        rChild->left = parent;
        parent->right = rlChild;

        parent->height = max(height(parent->left),
                        height(parent->right)) + 1;
        rChild->height = max(height(rChild->left),
                        height(rChild->right)) + 1;
        return rChild;
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
            return rightRotate(node);

        if (balance < -1 && data > node->right->data.first) // rr
            return leftRotate(node);

        if (balance > 1 && data > node->left->data.first) // lr
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && data < node->right->data.first)  // rl
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
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

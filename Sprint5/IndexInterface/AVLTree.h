#ifndef AVLTREE_H
#define AVLTREE_H

// obtained via Geeks for Geeks.
// https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
// set II for deletion also used **

#include <iostream>
#include <string>
#include<cstdio>
#include<sstream>
#include<algorithm>
#include <utility>
#include <vector>
#include <IndexInterface.h>
#define pow2(n) (1 << (n))

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
   public:
    // A utility function to get maximum
    // of two integers

    // A utility function to get the
    // height of the tree
    int height(Node<T> * N)
    {
        if (N == NULL)
            return 0;
        return N->height;
    }

    // A utility function to get maximum
    // of two integers
    int max(int a, int b)
    {
        return (a > b)? a : b;
    }

    /* Helper function that allocates a
       new node with the given key and
       NULL left and right pointers. */
    Node<T> * newNode(int key)
    {
        Node<T> * node = new Node<T>();
        node->key = key;
        node->left = NULL;
        node->right = NULL;
        node->height = 1; // new node is initially
                          // added at leaf
        return(node);
    }

    // A utility function to right
    // rotate subtree rooted with y
    // See the diagram given above.
    Node<T> * rightRotate(Node<T> * y)
    {
        Node<T> * x = y->left;
        Node<T> * T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = max(height(y->left),
                        height(y->right)) + 1;
        x->height = max(height(x->left),
                        height(x->right)) + 1;

        // Return new root
        return x;
    }

    // A utility function to left
    // rotate subtree rooted with x
    // See the diagram given above.
    Node<T> * leftRotate(Node<T> * x)
    {
        Node<T> * y = x->right;
        Node<T> * T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = max(height(x->left),
                        height(x->right)) + 1;
        y->height = max(height(y->left),
                        height(y->right)) + 1;

        // Return new root
        return y;
    }

    // Get Balance factor of node N
    int getBalance(Node<T> * N)
    {
        if (N == NULL)
            return 0;
        return height(N->left) - height(N->right);
    }

    // Recursive function to insert a key
    // in the subtree rooted with node and
    // returns the new root of the subtree.
    Node<T> * addWord(Node<T> * node, T data)
    {
        /* 1. Perform the normal BST insertion */
        if (node == NULL)
            return(newNode(data));

        if (data < node->key)
            node->left = insert(node->left, data);
        else if (data > node->key)
            node->right = insert(node->right, data);
        else // Equal keys are not allowed in BST
            return node;

        /* 2. Update height of this ancestor node */
        node->height = 1 + max(height(node->left),
                            height(node->right));

        /* 3. Get the balance factor of this ancestor
            node to check whether this node became
            unbalanced */
        int balance = getBalance(node);

        // If this node becomes unbalanced, then
        // there are 4 cases

        // Left Left Case
        if (balance > 1 && data < node->left->data)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && data > node->right->data)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && data > node->left->data)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && data < node->right->data)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        /* return the (unchanged) node pointer */
        return node;
    }

    // A utility function to print preorder
    // traversal of the tree.
    // The function also prints height
    // of every node
    void preOrder(Node<T> * root)
    {
        if(root != NULL)
        {
            cout << root->key << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    vector<T> access(string data, Node<T> * root){ // return value can be changed for query
        Node<T> * curr = root;

        if(strcmp(curr->data.first, data) < 0){ //neg if search is larger
            curr == curr->right;
            access(data, curr);
        }
        else if(strcmp(curr->data.first, data) > 0){ // if search is larger
            curr == curr->left;
            access(data, curr);
        }
        else if(strcmp(curr->data.first, data) == 0){
            return curr->data.second;
        }
        else{
            cout << "nothing" << endl;
        }

    }

    void addDoc(string data, string newDoc, Node<T> * root){

    }


};



#endif // AVLTREE_H

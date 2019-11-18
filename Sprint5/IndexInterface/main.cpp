#include <iostream>
#include <AVLTree.h>
#include <HashMap.h>
#include "documentparser.h"

using namespace std;

int main(){

    cout << "Hello World!" << endl;
    AVLTree<int> avl;
    HashMap<string> hash;
    hash.addWord("hi");
   // avl.addWord("hi");
    string tester = "std";
    documentParser test(tester);

    return 0;
}

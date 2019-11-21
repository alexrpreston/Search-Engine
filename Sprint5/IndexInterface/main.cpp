#include <iostream>
#include <AVLTree.h>
#include <HashMap.h>
#include "documentparser.h"

using namespace std;

int main(){
    AVLTree<string> avl;
    HashMap<string> hash = HashMap<string>();
    //hash.addWord("hi");
    //hash.addDoc("hiDoc", "hi");
    avl.addFirst("hi");
    avl.addSec("hi", "doc1");
    avl.addFirst("word2");
    avl.addFirst("a");
    avl.addFirst("peanuts");
    avl.addSec("a", "adoc");

    avl.preOrder();
    string tester = "std";
    //documentParser test(tester);

    return 0;
}

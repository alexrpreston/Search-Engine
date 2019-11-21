#include <iostream>
#include <AVLTree.h>
#include <HashMap.h>
#include "documentparser.h"
#include "../IndexInterface/OleanderStemmingLibrary/include/olestem/stemming/english_stem.h"
using namespace std;

int main(){
    AVLTree<string> avl;
    HashMap<string> hash = HashMap<string>();
    //hash.addWord("hi");
    //hash.addDoc("hiDoc", "hi");
    avl.addWord("hi");
    avl.addDoc("hi", "doc1");
    avl.addWord("word2");
    avl.addWord("a");
    avl.addWord("peanuts");
    avl.addDoc("a", "adoc");

    avl.preOrder();
    //string tester1 = "HeLLo";
    documentParser();
    //cout << tester1 << endl;;


    return 0;
}

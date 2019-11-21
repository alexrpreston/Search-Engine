#include <iostream>
#include <AVLTree.h>
#include <HashMap.h>
#include "documentparser.h"
#include "../../../OleanderStemmingLibrary/include/olestem/stemming/english_stem.h"
using namespace std;

int main(){
    AVLTree<string> avl;
    HashMap<string> hash = HashMap<string>();
    //hash.addWord("hi");
    //hash.addDoc("hiDoc", "hi");
<<<<<<< HEAD
    avl.addFirst("hi");
    avl.addSec("hi", "doc1");
    avl.addFirst("word2");
    avl.addFirst("a");
    avl.addFirst("peanuts");
    avl.addSec("a", "adoc");
=======
//    avl.addWord("hi");
//    avl.addDoc("hi", "doc1");
//    avl.addWord("word2");
//    avl.addWord("a");
//    avl.addWord("peanuts");
//    avl.addDoc("a", "adoc");

//    avl.preOrder();
    //string tester1 = "HeLLo";
    documentParser();
    //cout << tester1 << endl;


>>>>>>> db3b705214425b7d081ed4ad07ba0aeb9db3fe4d


    return 0;
}

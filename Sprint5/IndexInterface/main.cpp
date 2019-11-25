#include <iostream>
#include <AVLTree.h>
#include <HashMap.h>
#include "documentparser.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "../IndexInterface/Libraries/OleanderStemmingLibrary/include/olestem/stemming/english_stem.h"

using namespace std;



int main(int argc, char * const argv[]){
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

    cout << avl.getNumNodes() << endl;
//    avl.addWord("hi");
//    avl.addDoc("hi", "doc1");
//    avl.addWord("word2");
//    avl.addWord("a");
//    avl.addWord("peanuts");
//    avl.addDoc("a", "adoc");

    documentParser(argv[1], argv[2]);

    return 0;

}





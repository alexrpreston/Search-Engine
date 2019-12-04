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
#include "userinterface.h"
#include "../IndexInterface/Libraries/OleanderStemmingLibrary/include/olestem/stemming/english_stem.h"

using namespace std;



int main(int argc, char * const argv[]){

    string filePath = argv[1];
    if(filePath[filePath.length()-1] != '/'){
            filePath = filePath + '/';
    }
    char * formatedFilePath = &filePath[0];
    //documentParser(formatedFilePath, argv[2]);
    userInterface();

    return 0;

}





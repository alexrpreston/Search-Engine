#include "documentparser.h"
#include "iomanip"
#include <string.h>
#include <iostream>
#include <stdio.h>
documentParser::documentParser(string test)
{
    cout << "line 8" << endl;
    makeStopWords();
    cout << "line 10" << endl;
    if(isStopWord(test)) cout << "true";
    else cout << "false";
}

bool documentParser::isStopWord(string &word){
    int left = 0;
    int right = stopWords.size()-1;

    while(left <= right){
            int middle = left + (right - left) / 2;

            if(stopWords.at(middle) == word){
                return true;
            }

            if(stopWords.at(middle) < word){
                left = middle + 1;
            }

            else {
               right = middle - 1;
            }
        }
        return false;
}

void documentParser::readDocuments(){

}

void documentParser::makeStopWords(){
    string stopWordList = "a about after all also an and any as at back be because but by can come could day do even first for from get give go have he her him his how i if in into it its just know like look make me most my new no not now of on one only or other our out over people say see she so some take than that the their them then there these they think this time to two up us use want way we well what when which who will with would year you your";
    string deliminator = " ";
    size_t position = 0;
    string token = "";
    while((position = stopWordList.find(deliminator)) != string::npos){
          token = stopWordList.substr(0, position);
          stopWords.push_back(token);
          stopWordList.erase(0, position + deliminator.length());
    }
}

#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H
using namespace std;
#include <string>
#include <vector>
#include "AVLTree.h"
class documentParser
{
public:
    documentParser();
    documentParser(char * filePath, string wordToFind);
    bool isStopWord(string &word);
    void makeLowerCase(string &word);
    void getFileNames(char * filePath);
    void stemWord(string &word);
    void readDocumentsHTMLData(string filePath);
    void makeStopWords();
    void removeTags(string &html);
private:
    string word = "";
    vector<string>stopWords;
    string wordToFind = "";
    int wordToFindTotalOccurances = 0;
    int wordToFindDocumentOccurances = 0;
    bool appearsInDoc = false;
    AVLTree<string> tree;
    string filePath = "";

};

#endif // DOCUMENTPARSER_H

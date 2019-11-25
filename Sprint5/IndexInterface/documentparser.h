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
    char *pathcat(const char *str1, char *str2);
    bool isStopWord(string &word);
    void makeLowerCase(string &word);
    void getFileNames(char * filePath);
    void stemWord(string &word);
    void readDocumentsHTMLData(char * filePath);
    void parseHTMLData();
    void makeStopWords();
    void removeTags(string &html);
private:
    string word = "";
    vector<string>stopWords;
    vector<string>FileNames;
    vector<pair<string, string>>HTMLData;
    string wordToFind = "";
    int wordToFindTotalOccurances = 0;
    int wordToFindDocumentOccurances = 0;
    bool appearsInDoc = false;
    AVLTree<string> tree;

};

#endif // DOCUMENTPARSER_H

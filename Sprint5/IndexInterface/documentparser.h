#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H
using namespace std;
#include <string>
#include <vector>
class documentParser
{
public:
    documentParser(char * filePath, string wordToFind);
    bool isStopWord(string &word);
    void makeLowerCase(string &word);
    void stemWord(string &word);
    void readDocuments();
    void makeStopWords();
private:
    string word = "";
    vector<string>stopWords;
};

#endif // DOCUMENTPARSER_H

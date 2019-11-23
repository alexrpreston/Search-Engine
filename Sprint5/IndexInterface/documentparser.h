#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H
using namespace std;
#include <string>
#include <vector>
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
    void readDocuments();
    void makeStopWords();
private:
    string word = "";
    vector<string>stopWords;
    vector<string>FileNames;
};

#endif // DOCUMENTPARSER_H

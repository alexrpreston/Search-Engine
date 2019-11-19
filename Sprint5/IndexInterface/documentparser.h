#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H
using namespace std;
#include <string>
#include <vector>
class documentParser
{
public:
    documentParser(string test);
    bool isStopWord(string &word);
    string makeLowerCase(string word);
    string stemWord(string word);
    void readDocuments();
    void makeStopWords();
private:
    string word = "";
    vector<string>stopWords;
};

#endif // DOCUMENTPARSER_H

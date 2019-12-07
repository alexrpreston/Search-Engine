#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H
#include "string"
#include "documentparser.h"
#include "vector"
#include "HashMap.h"
#include "AVLTree.h"

using namespace std;

class queryProcessor
{
public:
    queryProcessor();
    queryProcessor(string query);
    void singleQuery(string query);
    void orQuery();
    void andQuery();
    void notQuery();
    void spliceQueryWords();
    void removeRepeats();

    vector<vector<string>> allDocuments;
    vector<string> finalDocuments;
    documentParser (formatedFilePath);
    vector<string> splicedWords;
private:
    string query = "";
    //IndexInterface * II = &tree;

};

#endif // QUERYPROCESSOR_H

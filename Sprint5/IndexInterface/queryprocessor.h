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
    queryProcessor(IndexInterface * &II);

    void querySearch(string query);
    void singleQuery(string query);
    void orQuery(string query);
    void andQuery(string query);
    void notQuery(string query);
    void spliceQueryWords(string query);
    void removeRepeats();

    vector<vector<pair<string, int>>> allDocuments;
    vector<string> finalDocuments;
    documentParser (formatedFilePath);
    vector<string> splicedWords;
    AVLTree<string> tree;
    HashMap<string> map;
    IndexInterface * II = &tree;

private:
    string query = "";
    //IndexInterface * II = &tree;

};

#endif // QUERYPROCESSOR_H

#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H
#include "string"
#include "documentparser.h"
#include "vector"
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

    vector<vector<string>> allDocuments;
    vector<string> finalDocuments;
    documentParser (formatedFilePath);

};

#endif // QUERYPROCESSOR_H

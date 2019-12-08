#include "queryprocessor.h"
#include "documentparser.h"
#include <iostream>
queryProcessor::queryProcessor(IndexInterface &II){
    this->II = &II;
}

void queryProcessor::querySearch(string query){
    this->query = query;
    size_t andQuery = query.find("AND");
    size_t orQuery = query.find("OR");
    if(andQuery != std::string::npos){
        query = query.substr(4,query.size()); //removes "AND" from beginning or query
    }
    else if(orQuery != std::string::npos){
        query = query.substr(3,query.size()); //removes "OR" from beginning or query
    }
    else{
        singleQuery(query);
    }
}


void queryProcessor::singleQuery(string query){
    cout << "Just one word" << endl;
    //access(query)
    vector<pair<string, int>> testDat = II->access(query);
    for(int i = 0; i < testDat.size(); i++){
        cout << testDat[i].first << endl;
    }
}

void queryProcessor::orQuery(){
    size_t notQuery = query.find("NOT");
    if(notQuery == std::string::npos){
        spliceQueryWords();

    }

}

void queryProcessor::andQuery()
{

}

void queryProcessor::notQuery()
{

}

void queryProcessor::spliceQueryWords(){
    string deliminator = " ";
    size_t position = 0;
    string token = "";
    while((position = query.find(deliminator)) != string::npos){
          token = query.substr(0, position);
          splicedWords.push_back(token);
          query.erase(0, position + deliminator.length());
    }
}

void queryProcessor::removeRepeats(){
    for(int i = 0; i < finalDocuments.size()-1; i++){
        for(int j = 1; j < finalDocuments.size(); j++){
            if(finalDocuments[i] == finalDocuments[j]){
                finalDocuments.erase(finalDocuments.begin()+i);
            }
        }
    }
}

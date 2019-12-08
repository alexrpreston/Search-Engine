#include "queryprocessor.h"
#include "documentparser.h"
#include <iostream>
queryProcessor::queryProcessor(IndexInterface * &II){
    this->II = II;
}

void queryProcessor::querySearch(string query){
    //this->query = query;
    size_t andQueryLocation = query.find("AND");
    size_t orQueryLocation = query.find("OR");
    if(andQueryLocation != std::string::npos){
        query = query.substr(4,query.size()); //removes "AND" from beginning or query
        andQuery(query);
    }
    else if(orQueryLocation != std::string::npos){
        query = query.substr(3,query.size()); //removes "OR" from beginning or query
        cout << query << endl;
        orQuery(query);
    }
    else{
        singleQuery(query);
    }
}


void queryProcessor::singleQuery(string query){
    cout << "Just one word" << endl;
    //access(query)
    //cout << II->access(query)[0].first << endl;
    vector<pair<string, int>> testData;
    II->access(query, testData);
    for(int i = 0; i < testData.size(); i++){
        cout << testData[i].first << endl;
    }
}

void queryProcessor::orQuery(string query){
    cout << "Query Type: OR " << query << endl;
    size_t notQuery = query.find("NOT");
    if(notQuery == std::string::npos){
        spliceQueryWords(query);
        for(int i = 0; i < splicedWords.size(); i++){
            cout << "How many time does this print" << endl;
            cout << splicedWords[i] << endl;
            //vector<pair<string, int>> singleWordDocumentList;
            //II->access(splicedWords[i]., singleWordDocumentList);
            //allDocuments.push_back(singleWordDocumentList);
        }
//        for(int i = 0; i < allDocuments.size(); i++){
//            for(int j = 0; j < allDocuments[i].size(); j++){
//                cout << allDocuments[i][j].first << endl;
//            }
//        }
    }

}

void queryProcessor::andQuery(string query)
{

}

void queryProcessor::notQuery(string query)
{

}

void queryProcessor::spliceQueryWords(string query){
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

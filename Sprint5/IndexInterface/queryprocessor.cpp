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
        orQuery(query);
    }
    else{
        singleQuery(query);
    }

//    mergeAllDocuments();
//    removeRepeats();
//    for(int i = 0; i < finalDocuments.size(); i++){
//        cout << finalDocuments[i].first << " - " << finalDocuments[i].second << endl;
//    }
}


void queryProcessor::singleQuery(string query){
    size_t notQuery = query.find("NOT");
    if(notQuery == std::string::npos){
        II->access(query, finalDocuments);
    }
    else{
        string notWord = query.substr(notQuery+4, query.size()-notQuery);
        query = query.substr(0,notQuery-1);
        II->access(query, finalDocuments);
        spliceNotWords(notWord);
        getNotQueryDocs();
        removeNotQueryDocs();
    }
    removeRepeats();
    sortFinalDocsByFrequency();
    cout << "Relevancy Ranking:" << endl;
    for(int i = 0; i < finalDocuments.size(); i++){
        cout << finalDocuments[i].first << " - " << finalDocuments[i].second << endl;
    }
}

void queryProcessor::orQuery(string query){
    cout << "Query Type: OR " << query << endl;
    size_t notQuery = query.find("NOT");
    if(notQuery == std::string::npos){
        spliceQueryWords(query);
        for(int i = 0; i < splicedQueryWords.size(); i++){
            cout << "How many time does this print" << endl;
            cout << splicedQueryWords[i] << endl;
            vector<pair<string, int>> singleWordDocumentList;
            II->access(splicedQueryWords[i], singleWordDocumentList);
            allDocuments.push_back(singleWordDocumentList);
        }
        for(int i = 0; i < allDocuments.size(); i++){
            for(int j = 0; j < allDocuments[i].size(); j++){
                cout << "ALL DOCS: " << allDocuments[i][j].first << " - " << allDocuments[i][j].second << endl;
            }
        }
    }

}

void queryProcessor::andQuery(string query){

}



void queryProcessor::spliceQueryWords(string query){
    char sentence[655565];
    string word = "";
    strcpy(sentence, query.c_str());
    char * token = strtok(sentence, " ");

   while(token != NULL){
       string buffer = "";
       for(int i = 0; i < strlen(token); i++){
               if(isalpha(tolower(token[i]))) buffer += char(tolower(token[i]));
       }
       token = strtok(NULL, " ");

       word = buffer.c_str();
       parser.makeLowerCase(word);
       word = parser.stemQueryWord(word);
       splicedQueryWords.push_back(word);
   }
}

void queryProcessor::spliceNotWords(string notQueryWords){
    char sentence[655565];
    string word = "";
    strcpy(sentence, notQueryWords.c_str());
    char * token = strtok(sentence, " ");

    while(token != NULL){
       string buffer = "";
       for(int i = 0; i < strlen(token); i++){
               if(isalpha(tolower(token[i]))) buffer += char(tolower(token[i]));
       }
       token = strtok(NULL, " ");

       word = buffer.c_str();
       parser.makeLowerCase(word);
       word = parser.stemQueryWord(word);
       splicedNotWords.push_back(word);
    }
}

void queryProcessor::removeRepeats(){
    finalDocuments.erase(unique(finalDocuments.begin(), finalDocuments.end()), finalDocuments.end());
}

void queryProcessor::mergeAllDocuments(){
    for(int i = 0; i < allDocuments.size(); i++){
        for(int j = 0; j < allDocuments[i].size(); j++){
            int totalOccurances = 0;
            for(int a = 0; a < allDocuments.size(); a++){
                for(int b = 1; b < allDocuments.size(); b++){
                    if(allDocuments[i][j].first == allDocuments[a][b].first){
                        allDocuments[i][j].second += allDocuments[a][b].second;
                        allDocuments[a][b].second = allDocuments[i][j].second;
                    }
                }
            }
            pair<string, int> documentAndFrequency = make_pair(allDocuments[i][j].first, allDocuments[i][j].second);
            finalDocuments.push_back(documentAndFrequency);
        }
    }

}

void queryProcessor::getNotQueryDocs(){
    for(int i = 0; i < splicedNotWords.size(); i++){
        vector<pair<string, int>> singleWordDocumentList;
        II->access(splicedNotWords[i], singleWordDocumentList);
        for(int j = 0; j < singleWordDocumentList.size(); j++){
            notQueryDocs.push_back(singleWordDocumentList[j]);
        }
    }
}

void queryProcessor::removeNotQueryDocs(){
    for(int i = 0; i < finalDocuments.size(); i++){
        for(int j = 0; j < notQueryDocs.size(); j++){
            if(finalDocuments[i].first == notQueryDocs[j].first){
                finalDocuments.erase(finalDocuments.begin() + i);
            }
        }
    }
}

void queryProcessor::sortFinalDocsByFrequency(){
    for(int i = 0; i < finalDocuments.size()-1; i++){
        int minIndex = i;
        for(int j = i+1; j < finalDocuments.size(); j++){
            if(finalDocuments[j].second > finalDocuments[minIndex].second){
                minIndex = j;

            }
        }
        pair<string,int> temp =  finalDocuments[minIndex];
        finalDocuments[minIndex] = finalDocuments[i];
        finalDocuments[i] = temp;
    }
}

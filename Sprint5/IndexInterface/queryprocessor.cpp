#include "queryprocessor.h"
#include "documentparser.h"
#include <iostream>
#include "chrono"
queryProcessor::queryProcessor(IndexInterface * &II){
    this->II = II;
}

void queryProcessor::querySearch(string query){
    cout << "\n";

    //Resets all Vectors
    allDocuments.clear();
    finalDocuments.clear();
    notQueryDocs.clear();
    splicedNotWords.clear();
    splicedQueryWords.clear();

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


}


void queryProcessor::singleQuery(string query){
//    auto start = chrono::system_clock::now();
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
//    auto end = chrono::system_clock::now();
//    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - start);
//    cout << finalDocuments.size() << " results " << "(" << elapsed.count() << " microseconds" << ")" << "\n\n";
    printDocuemnts();


}

void queryProcessor::orQuery(string query){
//    auto start = chrono::system_clock::now();
    string notWord = "";
    size_t notQuery = query.find("NOT");
    if(notQuery == std::string::npos){
        spliceQueryWords(query);
        for(int i = 0; i < splicedQueryWords.size(); i++){
            vector<pair<string, int>> singleWordDocumentList;
            II->access(splicedQueryWords[i], singleWordDocumentList);
            allDocuments.push_back(singleWordDocumentList);
        }
        mergeAllDocuments();
        sortFinalDocsByFrequency();
        for(int i = 0; i < finalDocuments.size(); i++){
            cout << i+1 << " " <<  finalDocuments[i].first << endl;
        }
        //printDocuemnts();
    }
    else{
        notWord = query.substr(notQuery+4, query.size()-notQuery);
        query = query.substr(0,notQuery-1);
        spliceQueryWords(query);
        for(int i = 0; i < splicedQueryWords.size(); i++){
            vector<pair<string, int>> singleWordDocumentList;
            II->access(splicedQueryWords[i], singleWordDocumentList);
            allDocuments.push_back(singleWordDocumentList);
        }
    }

    spliceNotWords(notWord);
    getNotQueryDocs();
    mergeAllDocuments();
    removeNotQueryDocs();
    sortFinalDocsByFrequency();
//    auto end = chrono::system_clock::now();
//    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - start);
//    cout << finalDocuments.size() << " results " << "(" << elapsed.count() << " microseconds" << ")" << "\n\n" << flush;
    printDocuemnts();

}

void queryProcessor::andQuery(string query){
//    auto start = chrono::system_clock::now();
    string notWord = "";
    size_t notQuery = query.find("NOT");
    if(notQuery == std::string::npos){
        spliceQueryWords(query);
        for(int i = 0; i < splicedQueryWords.size(); i++){
            vector<pair<string, int>> singleWordDocumentList;
            II->access(splicedQueryWords[i], singleWordDocumentList);
            allDocuments.push_back(singleWordDocumentList);
        }
    }
    else{
        notWord = query.substr(notQuery+4, query.size()-notQuery);
        query = query.substr(0,notQuery-1);
        spliceQueryWords(query);
        for(int i = 0; i < splicedQueryWords.size(); i++){
            vector<pair<string, int>> singleWordDocumentList;
            II->access(splicedQueryWords[i], singleWordDocumentList);
            allDocuments.push_back(singleWordDocumentList);
        }
    }
    int totalOccurances = 0;
    for(int i = 0; i < allDocuments.size(); i++){
        for(int j = 0; j < allDocuments[i].size(); j++){
            for(int l = i+1; l < allDocuments.size()-1; l++){
                for(int m = j+1; m < allDocuments[i].size()-1; m++){
                    if(allDocuments[i][j].first == allDocuments[l][m].first){
                        totalOccurances++;
                        if(totalOccurances == splicedQueryWords.size()){
                            finalDocuments.push_back(allDocuments[l][m]);
                            totalOccurances = 0;
                        }
                    }
                }
            }

        }
    }
    getNotQueryDocs();
    mergeAllDocuments();
    removeNotQueryDocs();
    sortFinalDocsByFrequency();
//    auto end = chrono::system_clock::now();
//    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - start);
//    cout << finalDocuments.size() << " results " << "(" << elapsed.count() << " microseconds" << ")" << "\n\n";
    printDocuemnts();
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
    bool alreadyInFinal = false;
    for(int i = 0; i < allDocuments.size(); i++){
        for(int j = 0; j < allDocuments[i].size(); j++){
            for(int k = 0; k < finalDocuments.size(); k++){
                if(allDocuments[i][j].first == finalDocuments[k].first){
                    finalDocuments[k].second += allDocuments[i][j].second;
                    alreadyInFinal = true;
                }
            }
            if(!alreadyInFinal){
                finalDocuments.push_back(allDocuments[i][j]);
            }
            alreadyInFinal = false;

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

void queryProcessor::printDocuemnts(){

    for(int i = 0; i < 15 && i < finalDocuments.size(); i++){
        //cout << finalDocuments[i].first << " - " << finalDocuments[i].second << endl;
        if(i+1 == 1) cout << "1st";
        if(i+1 == 2) cout << "2nd";
        if(i+1 == 3) cout << "3rd";
        else if(i+1 > 3)cout << i+1 << "th";
        cout << " most relevant opinion found."<< "      \n========================================\n";
        parser.getRelevantInfo(finalDocuments[i].first);
        cout << "\n========================================\n\n";
    }
}

string queryProcessor::expand(int num){
    string docID = finalDocuments[num].first;
    return parser.getFirst300Words(docID);

}

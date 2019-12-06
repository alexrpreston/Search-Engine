#include "queryprocessor.h"
#include "documentparser.h"
#include <iostream>
queryProcessor::queryProcessor()
{

}

queryProcessor::queryProcessor(string query){
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
}

void queryProcessor::orQuery(){

}

void queryProcessor::andQuery()
{

}

void queryProcessor::notQuery()
{

}

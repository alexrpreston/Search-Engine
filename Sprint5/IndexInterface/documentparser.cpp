#include "documentparser.h"
#include "iomanip"
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <dirent.h>
#include <algorithm>
#include <cctype>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <cstdio>
#include "../IndexInterface/Libraries/OleanderStemmingLibrary/include/olestem/stemming/english_stem.h" // un comment me later
#include "../IndexInterface/Libraries/rapidjson/include/rapidjson/document.h"
#include "../IndexInterface/Libraries/rapidjson/include/rapidjson/writer.h"
#include "../IndexInterface/Libraries/rapidjson/include/rapidjson/stringbuffer.h"
#include "../IndexInterface/Libraries/rapidjson/include/rapidjson/filereadstream.h"
#include "../IndexInterface/Libraries/myhtml/include/myhtml/api.h"

using namespace rapidjson;

documentParser::documentParser(){

}

documentParser::documentParser(char * filePath, string wordToFind){
    cout << filePath << endl;
    cout << wordToFind << endl;
    getFileNames(filePath);
    makeStopWords();
    if(!isStopWord(word)){
        stemWord(word);
    }


    for(int i = 0; i < FileNames.size(); i++){
        //Gives all HTML data for Opinion
        string name = filePath+FileNames[i];
        FILE * fp = fopen(name.c_str(), "rb");
        char readBuffer[6553666];
        FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        Document d;
        d.ParseStream(is);
        Value& s = d["html"];
        cout << "Read JSON data of: " << name << endl;
        fclose(fp);

        string html = s.GetString();
    }





}




bool documentParser::isStopWord(string &word){
    int left = 0;
    int right = stopWords.size()-1;
    makeLowerCase(word);
    while(left <= right){
            int middle = left + (right - left) / 2;

            if(stopWords.at(middle) == word){
                return true;
            }

            if(stopWords.at(middle) < word){
                left = middle + 1;
            }

            else {
               right = middle - 1;
            }
    }

    return false;
}

void documentParser::makeLowerCase(string &word){
    transform(word.begin(), word.end(), word.begin(), ::tolower);
}

void documentParser::getFileNames(char *filePath){
    char * dir = filePath;

    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if((dp = opendir(dir)) == NULL) {
        return;
    }
    chdir(dir);
    while((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode)) {
            if(strcmp(".",entry->d_name) == 0 ||
                strcmp("..",entry->d_name) == 0)
                continue;
            FileNames.push_back(entry->d_name);
        }
        FileNames.push_back(entry->d_name);
    }
    //chdir(".."); //Might have to readd later it just move the current directory up one level, N/A if I use aboslute path
    closedir(dp);
}

void documentParser::stemWord(string &unstemmedWord){
    stemming::english_stem<> StemEnglish;
    std::wstring stemmedword(L" ");
    std::string ANSIWord(unstemmedWord);
    wchar_t* UnicodeTextBuffer = new wchar_t[ANSIWord.length()+1];
    std::wmemset(UnicodeTextBuffer, 0, ANSIWord.length()+1);
    std::mbstowcs(UnicodeTextBuffer, ANSIWord.c_str(), ANSIWord.length());
    stemmedword = UnicodeTextBuffer;
    StemEnglish(stemmedword);

}

void documentParser::readDocuments(){

}

void documentParser::makeStopWords(){
    string stopWordList = "a about after all also an and any as at back be because but by can come could day do even first for from get give go have he her him his how i if in into it its just know like look make me most my new no not now of on one only or other our out over people say see she so some take than that the their them then there these they think this time to two up us use want way we well what when which who will with would year you your";
    string deliminator = " ";
    size_t position = 0;
    string token = "";
    while((position = stopWordList.find(deliminator)) != string::npos){
          token = stopWordList.substr(0, position);
          stopWords.push_back(token);
          stopWordList.erase(0, position + deliminator.length());
    }
}

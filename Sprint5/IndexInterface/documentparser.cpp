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
#include <locale>
#include <codecvt>
#include "../IndexInterface/Libraries/OleanderStemmingLibrary/include/olestem/stemming/english_stem.h" // un comment me later
#include "../IndexInterface/Libraries/rapidjson/include/rapidjson/document.h"
#include "../IndexInterface/Libraries/rapidjson/include/rapidjson/writer.h"
#include "../IndexInterface/Libraries/rapidjson/include/rapidjson/stringbuffer.h"
#include "../IndexInterface/Libraries/rapidjson/include/rapidjson/filereadstream.h"
#include "../IndexInterface/Libraries/myhtml/include/myhtml/api.h"

using namespace rapidjson;

documentParser::documentParser(){
    cout << "" << endl;
}

documentParser::documentParser(char * filePath, string wordToFind){
    this->wordToFind = wordToFind;
    makeStopWords();
    cout << filePath << endl;
    cout << wordToFind << endl;
    getFileNames(filePath);
    readDocumentsHTMLData(filePath);
    parseHTMLData();










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
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type,wchar_t>converter;

    unstemmedWord = converter.to_bytes(stemmedword);

}

void documentParser::readDocumentsHTMLData(char * filePath){
    for(int i = 0; i < FileNames.size(); i++){
        //Gives all HTML data for Opinion
        string name = filePath+FileNames[i];
        FILE * fp = fopen(name.c_str(), "rb");
        char readBuffer[6553666];
        FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        Document d;
        d.ParseStream(is);
        Value& s = d["html"];


        fclose(fp);
        string shortFileName =  FileNames[i];
        //cout << "Grabbed HTML data of: " << shortFileName << endl;
        string html = s.GetString();
        pair<string,string> fileHtml;
        fileHtml = make_pair(html, shortFileName);
        HTMLData.push_back(fileHtml);

    }
}

void documentParser::parseHTMLData(){
    for(int i = 0; i < HTMLData.size(); i++){
        string html = HTMLData[i].first;
        removeTags(html);
        char sentence[656565];
        strcpy(sentence, html.c_str());
        //cout << html << endl;
        char * token = strtok(sentence, " ");

           while(token != NULL){
               string buffer = "";
               for(int i = 0; i < strlen(token); i++){
                       if(isalpha(tolower(token[i]))) buffer += char(tolower(token[i]));
               }
               token = strtok(NULL, " ");


               word = buffer.c_str();
               if(word != ""){

                   if(!isStopWord(word)){
                       //cout << "Before: " << word << endl;
                       stemWord(word);
                       //cout << "After: " << word << endl;
                   }
               }


        }
    cout << "Parsed: " << HTMLData[i].second << endl;
    }


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

void documentParser::removeTags(string &html){
    while(html.find("<") != html.npos){
        int openBracket = html.find("<");
        int closeBracket = html.find(">") + 1;

        if(closeBracket != html.npos){
            html.erase(openBracket, closeBracket - openBracket);
        }
    }
}

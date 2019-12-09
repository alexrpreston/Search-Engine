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
#include <chrono>
#include "../IndexInterface/Libraries/OleanderStemmingLibrary/include/olestem/stemming/english_stem.h"
#include "../IndexInterface/Libraries/rapidjson/include/rapidjson/document.h"
#include "../IndexInterface/Libraries/rapidjson/include/rapidjson/writer.h"
#include "../IndexInterface/Libraries/rapidjson/include/rapidjson/stringbuffer.h"
#include "../IndexInterface/Libraries/rapidjson/include/rapidjson/filereadstream.h"

using namespace rapidjson;

documentParser::documentParser(){
}

documentParser::documentParser(char * folderPath){ //Only used once to parse the files then gets stored the index.txt
    makeStopWords();
    getFileNames(folderPath);
}

documentParser::documentParser(char * persistentIndexPath, IndexInterface * &II){
    this->II = II; //This sets the AVL tree we created in the UI to the one we read all our files into.

    makeStopWords();
    getFileNames(persistentIndexPath);

    //tree.pof();
}

documentParser::documentParser(IndexInterface *&II){
    this->II = II; //This sets the AVL tree we created in the UI to the one we read all our files into.
    makeStopWords();
}




void documentParser::dataTypes(){
    //II->pof();
    II->destroy();
    if(avlT){
        avlT == false;
    }
    else{
        avlT == true;
    }

    if(!avlT){
        II = &tree;
    }
    else{
        II = &map; //map doesnt extend II rn
    }
    II->rf(); //^^
}

string documentParser::getRelevantInfo(string filePath){
    string path = "/home/student/Desktop/scotus-small/";
    string jsonEXT = ".json";
    string name = path + filePath + jsonEXT;
    FILE * fp = fopen(name.c_str(), "rb");
    char readBuffer[6553666];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    Document d;
    d.ParseStream(is);
    Value& s = d["html_with_citations"];
    string html = s.GetString();
    //cout << html;
    size_t endOfInfoIndex = html.find("Decided");
    html = html.substr(5, endOfInfoIndex+26);
    removeTags(html);
    cout <<  html;
}

string documentParser::getFirst300Words(string filePath){
    int totalwords = 0;
    string expandedDoc = "";
    string path = "/home/student/Desktop/scotus-small/";
    string jsonEXT = ".json";
    string name = path + filePath + jsonEXT;
    FILE * fp = fopen(name.c_str(), "rb");
    char readBuffer[6553666];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    Document d;
    d.ParseStream(is);
    Value& s = d["html_with_citations"];
    string html = s.GetString();
    //cout << html;
    size_t endOfInfoIndex = html.find("Decided");
    html = html.substr(endOfInfoIndex+26, 1500);
    removeTags(html);

    char sentence[655565];
    strcpy(sentence, html.c_str());
    char * token = strtok(sentence, " ");
    while(token != NULL){
        string buffer = "";
        for(int i = 0; i < strlen(token); i++){
                if(isalpha(tolower(token[i]))) buffer += char(tolower(token[i]));
        }

        token = strtok(NULL, " ");

        word = buffer.c_str();
        if(totalwords < 300) expandedDoc = expandedDoc + " " + word;
        totalwords++;
     }
    expandedDoc += "..........";
    return expandedDoc;
}

int documentParser::getTotalDocumentsParsed() const
{
    return totalDocumentsParsed;
}

void documentParser::addTotalDocumentsParsed(int value)
{
    totalDocumentsParsed += value;
}

double documentParser::getAvergeWordsPerDocument() const
{
    return avergeWordsPerDocument / getTotalDocumentsParsed();
}

void documentParser::addAvergeWordsPerDocument(int value)
{
    avergeWordsPerDocument += value;
}

bool documentParser::isStopWord(string &word){
    int left = 0;
    int right = stopWords.size()-1;
    makeLowerCase(word);
    if(word == wordToFind){
        appearsInDoc = true;
        wordToFindTotalOccurances++;
    }
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
    this->filePath = filePath;
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
            readDocumentsHTMLData(entry->d_name);
            addTotalDocumentsParsed(1);
        }
//        string entryName = entry->d_name;
//        entryName = entryName.substr(0, 11);
        readDocumentsHTMLData(entry->d_name);
        addTotalDocumentsParsed(1);
    }
    closedir(dp);
    chdir("../CSE2341-F19-Alex-Isaac/Sprint5/build-IndexInterface-Desktop_Qt_5_10_0_GCC_64bit-Debug/");
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
    delete [] UnicodeTextBuffer;

}

string documentParser::stemQueryWord(string word){
    stemming::english_stem<> StemEnglish;
    std::wstring stemmedword(L" ");
    std::string ANSIWord(word);
    wchar_t* UnicodeTextBuffer = new wchar_t[ANSIWord.length()+1];
    std::wmemset(UnicodeTextBuffer, 0, ANSIWord.length()+1);
    std::mbstowcs(UnicodeTextBuffer, ANSIWord.c_str(), ANSIWord.length());
    stemmedword = UnicodeTextBuffer;
    StemEnglish(stemmedword);
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type,wchar_t>converter;

    word = converter.to_bytes(stemmedword);
    delete [] UnicodeTextBuffer;
    return word;
}

void documentParser::readDocumentsHTMLData(string filePath){
        string name = this->filePath + filePath;
        FILE * fp = fopen(name.c_str(), "rb");
        char readBuffer[6553666];
        FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        Document d;
        d.ParseStream(is);
        Value& s = d["html_with_citations"];


        fclose(fp);
        string shortFileName =  filePath.substr(0,filePath.size()-5);
        string html = s.GetString();

        removeTags(html);
        char sentence[655565];
        strcpy(sentence, html.c_str());
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
                   stemWord(word);
                   addAvergeWordsPerDocument(1);
                   II->add(word, shortFileName);
               }
           }
        }
       if(appearsInDoc == true){
           wordToFindDocumentOccurances++;
           appearsInDoc = false;

        }
           if(appearsInDoc == true){
               wordToFindDocumentOccurances++;
               appearsInDoc = false;
           }
    //cout << "Parsed: " << HTMLData[i].second << endl;
    //tree.preOrder();

//cout << tree.access("coffee").front().first << " : " << tree.access("coffee").front().second << endl;

}

void documentParser::makeStopWords(){
    stopWords.clear();
    string stopWordList = "'ll 've a able about above abst accordance according accordingly across act actually added adj affected affecting affects after afterwards again against ah all almost alone along already also although always am among amongst an and announce another any anybody anyhow anymore anyone anything anyway anyways anywhere apparently approximately are aren aren’t arise around as aside ask asking at auth available away awfully b back be became because become becomes becoming been before beforehand begin beginning beginnings begins behind being believe below beside besides between beyond biol both brief briefly but by c ca came can can't cannot cause causes certain certainly co com come comes contain containing contains could couldn’t d date did didn't different do does doesn't doing don't done down downwards due during e each ed edu effect eg eight eighty either else elsewhere end ending enough especially et et-al etc even ever every everybody everyone everything everywhere ex except f far few ff fifth first five fix followed following follows for former formerly forth found four from further furthermore g gave get gets getting give given gives giving go goes gone got gotten h had happens hardly has hasn't have haven't having he hed hence her here hereafter hereby herein heres hereupon hers herself hes hi hid him himself his hither home how howbeit however hundred i i'll i've id ie if im immediate immediately importance important in inc indeed index information instead into invention inward is isn't it it'll itd its itself j just k keep keeps kept kg km know known knows l largely last lately later latter latterly least less lest let lets like liked likely line little look looking looks ltd m made mainly make makes many may maybe me mean means meantime meanwhile merely mg might million miss ml more moreover most mostly mr mrs much mug must my myself n na name namely nay nd near nearly necessarily necessary need needs neither never nevertheless new next nine ninety no nobody non none nonetheless noone nor normally nos not noted nothing now nowhere o obtain obtained obviously of off often oh ok okay old omitted on once one ones only onto or ord other others otherwise ought our ours ourselves out outside over overall owing own p page pages part particular particularly past per perhaps placed please plus poorly possible possibly potentially pp predominantly present previously primarily probably promptly proud provides put q que quickly quite qv r ran rather rd re readily really recent recently ref refs regarding regardless regards related relatively research respectively resulted resulting results right run s said same saw say saying says sec section see seeing seem seemed seeming seems seen self selves sent seven several shall she she'll shed shes should shouldn't show showed shown shown’s shows significant significantly similar similarly since six slightly so some somebody somehow someone somethan something sometime sometimes somewhat somewhere soon sorry specifically specified specify specifying still stop strongly sub substantially successfully such sufficiently suggest sup sure t take taken taking tell tends th than thank thanks thanx that that'll that've thats the their theirs them themselves then thence there there'll there've thereafter thereby thered therefore therein thereof therere theres thereto thereupon these they they'll they've they’d they’re think this those thou though thoughh thousand throug through throughout thru thus til tip to together too took toward towards tried tries truly try trying ts twice two u un under unfortunately unless unlike unlikely until unto up upon ups us use used useful usefully usefulness uses using usually v value various very via viz vol vols vs w want wants was wasn’t way we we'll we've wed welcome went were weren’t what what'll whatever what’s when whence whenever where whereafter whereas whereby wherein wheres whereupon wherever whether which while whim whither who who'll whoever whole whom whomever whos whose who’d why widely willing wish with within without wont words world would wouldn’t www x y yes yet you you'll you've your yours yourself yourselves you’d you’re z";
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
    int openBracket = 0;
    int closeBracket = 0;
    for(int i = html.length()-1; i > 0; i--){
        if(html[i] == '>'){
            closeBracket = i;
        }
        if(html[i] == '<'){
            openBracket = i;
            if(closeBracket != html.npos){
                html.erase(openBracket, closeBracket - openBracket+1);
            }
        }
    }
}

void documentParser::addOpinions(char *folderPath){
    makeStopWords();
    getFileNames(folderPath);
}

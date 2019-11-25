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
    cout << "Total occurances of '" << wordToFind << "': " << wordToFindTotalOccurances << "." << endl;
    cout << "Total documents '" << wordToFind << "' orccurs in is " << wordToFindDocumentOccurances << "." << endl;
    cout << "Total number of nodes is " << tree.getNumNodes() << endl;








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
    delete [] UnicodeTextBuffer;

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
        Value& s = d["html_with_citations"];


        fclose(fp);
        string shortFileName =  FileNames[i].substr(0, FileNames[i].size()-5);
        //cout << "Grabbed HTML data of: " << shortFileName << endl;
        string html = s.GetString();
        pair<string,string> fileHtml;
        fileHtml = make_pair(html, shortFileName);
        HTMLData.push_back(fileHtml);

    }
}

void documentParser::parseHTMLData(){
    int progressBarTotal = HTMLData.size() / 10;
    cout << "Parsing Progress [          ] 0%" << endl;
    int percent = 0;
    string bar = "";
    string barSpaces = "          ";
    int j = 9;
    for(int i = 0; i < HTMLData.size(); i++){
        if(i%progressBarTotal == 0){
            percent += 10;
            bar += "=";
            barSpaces = barSpaces.substr(0,j);
            j--;
            cout << "Parsing Progress [" << bar << barSpaces << "] " << percent << "%" << endl;
        }
        string html = HTMLData[i].first;
        removeTags(html);
        char sentence[656565];
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
                   if(word == wordToFind){
                       appearsInDoc = true;
                       wordToFindTotalOccurances++;
                   }
                   if(!isStopWord(word)){
                       stemWord(word);
                       tree.addFirst(word);
                       //cout << "Word: " << word << endl;
                       //cout << HTMLData[i].second << endl;
                       string ID = HTMLData[i].second;
                       tree.addSec(word, ID);
                   }
               }


        }
           if(appearsInDoc == true){
               wordToFindDocumentOccurances++;
               appearsInDoc = false;
           }
    //cout << "Parsed: " << HTMLData[i].second << endl;
    //tree.preOrder();
    }


}



void documentParser::makeStopWords(){
    //string stopWordList = "a about after all also an and any as at back be because but by can come could day do even first for from get give go have he her him his how i if in into it its just know like look make me most my new no not now of on one only or other our out over people say see she so some take than that the their them then there these they think this time to two up us use want way we well what when which who will with would year you your";
    string stopWordList = "a able about above abst accordance according accordingly across act actually added adj affected affecting affects after afterwards again against ah all almost alone along already also although always am among amongst an and announce another any anybody anyhow anymore anyone anything anyway anyways anywhere apparently approximately are aren aren’t arise around as aside ask asking at auth available away awfully b back be became because become becomes becoming been before beforehand begin beginning beginnings begins behind being believe below beside besides between beyond biol both brief briefly but by c ca came can cannot can't cause causes certain certainly co com come comes contain containing contains could couldn’t d date did didn't different do does doesn't doing done don't down downwards due during e each ed edu effect eg eight eighty either else elsewhere end ending enough especially et et-al etc even ever every everybody everyone everything everywhere ex except f far few ff fifth first five fix followed following follows for former formerly forth found four from further furthermore g gave get gets getting give given gives giving go goes gone got gotten h had happens hardly has hasn't have haven't having he hed hence her here hereafter hereby herein heres hereupon hers herself hes hi hid him himself his hither home how howbeit however hundred i id ie if i'll im immediate immediately importance important in inc indeed index information instead into invention inward is isn't it itd it'll its itself i've j just k keep keeps kept kg km know known knows l largely last lately later latter latterly least less lest let lets like liked likely line little 'll look looking looks ltd m made mainly make makes many may maybe me mean means meantime meanwhile merely mg might million miss ml more moreover most mostly mr mrs much mug must my myself n na name namely nay nd near nearly necessarily necessary need needs neither never nevertheless new next nine ninety no nobody non none nonetheless noone nor normally nos not noted nothing now nowhere o obtain obtained obviously of off often oh ok okay old omitted on once one ones only onto or ord other others otherwise ought our ours ourselves out outside over overall owing own p page pages part particular particularly past per perhaps placed please plus poorly possible possibly potentially pp predominantly present previously primarily probably promptly proud provides put q que quickly quite qv r ran rather rd re readily really recent recently ref refs regarding regardless regards related relatively research respectively resulted resulting results right run s said same saw say saying says sec section see seeing seem seemed seeming seems seen self selves sent seven several shall she shed she'll shes should shouldn't show showed shown shown’s shows significant significantly similar similarly since six slightly so some somebody somehow someone somethan something sometime sometimes somewhat somewhere soon sorry specifically specified specify specifying still stop strongly sub substantially successfully such sufficiently suggest sup sure     t take taken taking tell tends th than thank thanks thanx that that'll thats that've the their theirs them themselves then thence there thereafter thereby thered therefore therein there'll thereof therere theres thereto thereupon there've these they they’d they'll they’re they've think this those thou though thoughh thousand throug through throughout thru thus til tip to together too took toward towards tried tries truly try trying ts twice two u un under unfortunately unless unlike unlikely until unto up upon ups us use used useful usefully usefulness uses using usually v value various 've very via viz vol vols vs w want wants was wasn’t way we wed welcome we'll went were weren’t we've what whatever what'll what’s when whence whenever where whereafter whereas whereby wherein wheres whereupon wherever whether which while whim whither who who’d whoever whole who'll whom whomever whos whose why widely willing wish with within without wont words world would wouldn’t www x y yes yet you you’d you'll your you’re yours yourself yourselves you've z zero";
    //sort(stopWordList.begin(), stopWordList.end());
    //cout << stopWordList << endl;

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
        //find starts at beginning so is linear everytime
        //If I start at the end of the string it is alot faster.
        int openBracket = html.find("<");
        int closeBracket = html.find(">") + 1;

        if(closeBracket != html.npos){
            html.erase(openBracket, closeBracket - openBracket);
        }
    }
}

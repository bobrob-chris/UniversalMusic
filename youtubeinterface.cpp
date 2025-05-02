#include "youtubeinterface.h"
#include <string>
#include <iostream>
#include <windows.h>
#include <shellapi.h>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#include "utils.h"

//This can't go wrong right?
const string stringRoot = "https://www.youtube.com";


using std::string;

//helper method to replace all instances of find in text with replace
string replaceAll(string text, string find, string replace);

//harder to implemnt of the two
string UniMusic::YoutubeInterface::findSongUrl(string name, string artist, string apiKey) {
    //search bar query: https://www.youtube.com/results?search_query=cheri+cher+lady+modern+talking+vevo
    //returns 

    //so basic outline

    //take name and artist

    //turn it into curl request

    //TODO - methodize this process so that you can repeatedly look for videos (and not just first one)
    //
    
    string query = "q="+replaceAll(name,string(" "),("+"))+"+"+replaceAll(name,string(" "),("+"))+"+official";
    string key = "key="+apiKey;

    //execute curl request
        //curl https://www.youtube.com/results?search_query=cheri+cher+lady+modern+talking+vevo

    //actually since I'm using youtube api instead
    //(and screw actually reading documentation, I'm just going to use stack overflow)
    //https://www.googleapis.com/youtube/v3/search?part=snippet&maxResults=20&q=cheri+cher+lady+modern+talking+vevo&type=video&key=KEYID
    

    string base = "https://www.googleapis.com/youtube/v3/search?part=snippet&maxResults=20";

    string finalUrl = base+"&"+query+"&type=video&"+key;
    

    string command = "curl \""+finalUrl+"\" -s";



    //TODO - implement error handeling for exec c
    string output = exec(command.c_str());
        //std::cout << output << std::endl;

    //sift through output until you find the first video, (hardest part)
    //Actuall, really dumb idea
    //"videoId": "eNvUS-6PTbs"

    //find position of first video
    size_t videoPos = output.find("videoId");
    if (videoPos == string::npos) {
        std::cout << "didn't find videoId" << std::endl;
        //idk what this does, coming from java
    }

    

    size_t colonPos = output.find(":", videoPos);
    if (colonPos == string::npos) {
        std::cout << "didn't find colonPos" << std::endl;
    }

    

    size_t firstQuotePos = output.find("\"", colonPos);
    if (firstQuotePos == string::npos) {
        std::cout << "didn't find firstQuotePos" << std::endl;
    }
    firstQuotePos++;



    size_t secondQuotePos = output.find("\"", firstQuotePos);
    if (firstQuotePos == string::npos) {
        std::cout << "didn't find firstQuotePos" << std::endl;
    }



    string videoId =  output.substr(firstQuotePos, secondQuotePos-firstQuotePos);



    //packaging
    //https://www.youtube.com/watch?v=W3q8Od5qJio

    return stringRoot+"/watch?v="+videoId;



}

void UniMusic::YoutubeInterface::openUrl(string url) {
    if (url.find(stringRoot) == string::npos) {
        exec(string("start "+stringRoot+url).c_str());
    } else {
        exec(string("start "+url).c_str());
    }
}



string replaceAll(string text, string find, string replace){
    //almost exactly copied from geeks for geeks

    string copy = text;

    size_t pos = copy.find(find);

    while (pos != string::npos) {

        copy.replace(pos, find.size(), replace);
        pos = copy.find(find,pos + replace.size());
    }

    return copy;

}
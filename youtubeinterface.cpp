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





//harder to implemnt of the two
int UniMusic::YoutubeInterface::findSongUrl(string &name, string &artist, string *output) {
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



    string exec_output = exec(command);
    //if exec_output is wrong: return 1;

    //sift through output until you find the first video, (hardest part)
    //Actuall, really dumb idea
    //"videoId": "eNvUS-6PTbs"

    //find position of first video
    size_t videoPos = exec_output.find("videoId");
    if (videoPos == string::npos) {
        return 1;
    }

    size_t colonPos = exec_output.find(":", videoPos);
    if (colonPos == string::npos) {
        return 1;
    }

    

    size_t firstQuotePos = exec_output.find("\"", colonPos);
    if (firstQuotePos == string::npos) {
        return 1;
    }
    firstQuotePos++;

    size_t secondQuotePos = exec_output.find("\"", firstQuotePos);
    if (firstQuotePos == string::npos) {
        return 1;
    }



    string videoId =  exec_output.substr(firstQuotePos, secondQuotePos-firstQuotePos);



    //packaging
    //https://www.youtube.com/watch?v=W3q8Od5qJio

    //*output = stringRoot+"/watch?v="+videoId;
    *output = videoId;
    return 0;



}

void UniMusic::YoutubeInterface::openUrl(string &url) {
    if (url.find(stringRoot) == string::npos) {
        exec("start "+stringRoot+"/watch?v="+url);
    } else {
        exec("start "+url);
    }
}

int UniMusic::YoutubeInterface::getRuntime(string &id, int *output) {
    //https://www.googleapis.com/youtube/v3/videos?part=contentDetails&id=url

    string key = "key="+apiKey;
    string finalUrl  = "https://www.googleapis.com/youtube/v3/videos?part=contentDetails&id="+id+"&"+key;


    string command = "curl \""+finalUrl+"\" -s";

    string coutput = exec(command);

    string duration;
    int result = findToken(coutput, "duration", &duration);
    if (result != 0) {
        std::cerr << "FindToken failed" << std::endl;
        return 1;
    }


    //PT3M18S for cheri cheri lady
    int min = std::stoi(duration.substr(duration.find("PT")+2,2));//can only handle songs in single digits for min and two digits for seconds
    int sec = std::stoi(duration.substr(duration.find("M")+1,2));

    *output = (60*min + sec);
    return 0;
    
}    




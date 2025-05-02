#include <iostream>
#include <fstream>

#include <vector>
#include <ctime>

#include <algorithm>

#include "song.h"
#include "network.h"
#include "htmlparser.h"
#include "spotifyinterface.h"
#include "youtubeinterface.h"

#include "config.h"

#include "testing.h"

#include "unimusic.h"


//##############################
/*
4/28/25

I'm going to actually need to bring this alltogether at some point.
I've got Tina working on the front end, (gonna have to give her a more detailed design for that tmw)

But I got to figure out what "Essential Functions" I need

4/29/25

All of this looks like an utter mess, so 
TODO - organize all utility commands into a separate file

TODO - make a list of all the final commands, which will live here,
and will be called from Tina's interface. 

*/



using std::cout;
using std::endl;





//TODO - make spotify interface global so there's only one of them
int main(){
    //testSuite();
    runSimulator();

}




//TODO implement time and date functionality

void savePlaylist(string playlistid, string filename){
    //TODO - maybe put in some error handelling 
    UniMusic::SpotifyInterface s = UniMusic::SpotifyInterface(HIDDEN_SPOTIFY_CLIENT_ID, HIDDEN_SPOTIFY_CLIENT_SECRET);


    std::ofstream output(filename);

    //time_t timestamp;
    //time(&timestamp);

    //output << timestamp << endl;
    output << "PLACEHOLDER" << endl;

    output << s.getPlaylist(playlistid);

    output.close();
}

std::vector<string> readPlaylist(string filename, time_t *date){
    //TODO - error checking
    string line;
    std::ifstream inputFile(filename);

    std::vector<string> v;

    //First line - ignore for now until you get time working

    //getline(inputFile, line);
    //*date = mktime(line); 
    getline(inputFile, line); //discard first line, should be "PLACEHOLDER"

    while (getline (inputFile, line)) {
        v.push_back(line);
    }
    return v;

}


std::vector<string> delimitString(string &input, string &delimiter){
    string copy = input;
    std::vector<string> result;
    size_t pos = copy.find(delimiter);
    if (pos == string::npos) {
        return result;
    }
    size_t oldPos = 0;
    do {
        string seg = copy.substr(oldPos, pos);
        result.push_back(seg);
        copy = copy.substr(pos+1);
        oldPos = pos;
        pos = copy.find(delimiter);
    } while (pos != string::npos);

    result.push_back(copy);
    return result;

}



string removeQuotation(string &input) {
    return input.substr(1,input.length()-2);
}


void testYoutubeURLGet() {
    //should open christina perri thousand years
    UniMusic::YoutubeInterface::openUrl(string("/watch?v=rtOvBOTyX00"));
}

//Approaching magnum opus
//Takes a playlist on your spotify,
//Looks up a video from one of the songs
//And plays it
void testYoutubeURLSearch() {
    string playlist = HIDDEN_MY_PLAYLIST_ID;

    string playlistFileName = "playlist_test.txt";

    savePlaylist(playlist, playlistFileName);

    std::vector<string> list = readPlaylist(playlistFileName, nullptr);
    string song = list[157]; //TODO - make an accesser that checks size of vector
    std::vector<string> songParts = delimitString(song,string("-"));
    cout << song << endl;
    string url = UniMusic::YoutubeInterface::findSongUrl(removeQuotation(songParts[0]),removeQuotation(songParts[1]), HIDDEN_YOUTUBE_API_KEY);
    UniMusic::YoutubeInterface::openUrl(url);

}



//I need a function that's going to let me scroll through a list and choose songs via numbers.
//commands keys are i-up, k-down, l-pick, j,exit
void runSimulator(){
    string playlist = HIDDEN_MY_PLAYLIST_ID;

    string playlistFileName = "playlist_test.txt";
    //savePlaylist(playlist, playlistFileName);

    std::vector<string> list = readPlaylist(playlistFileName, nullptr);
    int listInt = 0;
    string response = string();
    do {
        string song = list[listInt];
        cout << song << ": ";
        
        getline(std::cin,response);
        //std::cin >> response;
        //commands
        if (response == "i" && listInt > 0) listInt--;
        if (response == "k" && listInt < list.size() -2) listInt++;
        if (response == "l") {
            std::vector<string> songParts = delimitString(song,string("-"));
            string url = UniMusic::YoutubeInterface::findSongUrl(removeQuotation(songParts[0]),removeQuotation(songParts[1]), HIDDEN_YOUTUBE_API_KEY);
            UniMusic::YoutubeInterface::openUrl(url);
        }


        cout << string(response.length()+song.length()+2,'\b');


    } while (response != "j"); //janky, change later
}




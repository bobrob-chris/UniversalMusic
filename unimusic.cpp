#include <iostream>
#include <fstream>

#include <vector>
#include <ctime>

#include <algorithm>

#include "utils.h"
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

TODO - removeQuotation has a bug i think

*/



using std::cout;
using std::endl;



int main(){
    //testSuite();
    UniMusic::MusicPlayer m = UniMusic::MusicPlayer(HIDDEN_SPOTIFY_CLIENT_ID,HIDDEN_SPOTIFY_CLIENT_SECRET,HIDDEN_YOUTUBE_API_KEY);


    m.runInterface();

}


void UniMusic::MusicPlayer::runInterface() {
    string playlist = HIDDEN_MY_PLAYLIST_ID_2;

    string playlistFileName = "playlist_test.txt";
    savePlaylist(playlist, playlistFileName);


    std::vector<string> list = readPlaylist(playlistFileName);
    //check list
    if (list.size() == 0) {cout << "No songs" << endl; return;}
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
            string url;
            int result = yi->findSongUrl(songParts[0],songParts[1], &url);
            if (result == 1) {
                std::cerr << "FindSongUrl failed" << std::endl;
                return;
            }
            yi->openUrl(url);
        }


        if (response == "a") {//autoplay
            int runtime;
            time_t lastTime;
            bool isUpdated = true;
            while (true) {
                if (isUpdated){
                    lastTime = std::time(nullptr);
                    cout << lastTime << endl;                   
                    
                    song = list[listInt];

                    std::vector<string> songParts = delimitString(song,string("-"));

                    string url;
                    int result = yi->findSongUrl(songParts[0],songParts[1], &url);
                    if (result == 1) {
                        std::cerr << "FindSongUrl failed" << std::endl;
                        return;
                    }
                    result = yi->getRuntime(url, &runtime);
                    if (result == 1) {
                        std::cerr << "Runtime failed" << std::endl;
                        return;
                    }
                    isUpdated = false;
                    yi->openUrl(url);

                }

                time_t currentTime = std::time(nullptr);
                if (currentTime - lastTime > runtime+70){
                    isUpdated = true;
                    listInt++;

                }


            }
        }



    } while (response != "j"); //janky, change later
}







void UniMusic::MusicPlayer::savePlaylist(string playlistid, string filename){
    std::ofstream output(filename);
    string playlistOutput;
    int result = si->getPlaylist(playlistid, 200, &playlistOutput);
    if (result != 0) {
        std::cerr << "getPlaylist failed" << std::endl;
        return;
    }
    output << playlistOutput;

    output.close();
}

std::vector<string> UniMusic::MusicPlayer::readPlaylist(string filename){
    //TODO - error checking
    string line;
    std::ifstream inputFile(filename);

    std::vector<string> v;

    while (getline (inputFile, line)) {
        v.push_back(line);
    }
    return v;

}





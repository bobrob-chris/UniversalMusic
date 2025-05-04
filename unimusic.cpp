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

#define STANDARD_DELIMITER ","

//z0NfI2NeDHI


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
    //check if playlist exitsts
    //TODO - put in function
    //START OF FUTURE FUNCTION
    string line;
    std::ifstream inputFile(playlistFileName);
    getline(inputFile, line);
    if (line.length() == 0) {
        savePlaylist(playlist, playlistFileName);
    }
    inputFile.close();

    //END OF FUTURE FUNCTION




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
        else if (response == "k" && listInt < list.size() -2) listInt++;
        else if (response == "l") {
            std::vector<string> songParts = delimitString(song,string(STANDARD_DELIMITER));
            string url;
            //heuristic goes like this
            //song-artist-url
            
            if (songParts.size() >= 3) { //should be 2 or greater than three
                url = songParts[2];
            } else {
                int result = yi->findSongUrl(songParts[0],songParts[1], &url);
                if (result == 1) {
                    std::cerr << "FindSongUrl failed" << std::endl;
                    return;
                }
                list[listInt] = songParts[0]+STANDARD_DELIMITER+songParts[1]+STANDARD_DELIMITER+url;
                savePlaylist(list, playlistFileName);

            }
            yi->openUrl(url);
        }

        else if (response == "y") {//change url, 
            //TODO - check if input is empty
            string url;
            std::cout << "Please insert the new youtube video id here: ";
            std::cin >> url;
            //Probably should do some error checking on this

            std::vector<string> songParts = delimitString(song,string(STANDARD_DELIMITER));
            for (string part: songParts){
                 cout << part << endl;
            }

            list[listInt] = songParts[0]+STANDARD_DELIMITER+songParts[1]+STANDARD_DELIMITER+url;
            savePlaylist(list, playlistFileName);
        }


        else if (response == "a") {//autoplay
           //updateCurrentSontList with what you want to play (like spotifies queue)
           std::vector<string>::const_iterator first = list.begin() + listInt;
           std::vector<string>::const_iterator last = list.end();

           songListLock.lock();
           currentSongList = std::vector<string>(first,last);
           songListLock.unlock();

           playing = true;
           player = std::thread(&UniMusic::MusicPlayer::startPlayer, this);
           cout << "Autoplaying..." << endl;
        }
        else if (response == "p") {
            if(playing) {
                playing = false;
                cout << "Pause" << endl;
            } else if (currentSongList.size() != 0){
                playing = true;
                cout << "Play" << endl;
            }
        }



    } while (response != "j"); //janky, change later

    playing = false;
}

void UniMusic::MusicPlayer::startPlayer(){

    int listInt = 0;



    int runtime;
    time_t lastTime;
    bool isUpdated = true;
    while (playing) {
        if (isUpdated){
            lastTime = std::time(nullptr);

            songListLock.lock();
            if (listInt >= currentSongList.size()){
                //at the end of the songs you have
                playing = false;
                currentSongList = std::vector<string>(); //clears queue
                break;//for good measure;
            }
            string song = currentSongList[listInt];
            songListLock.unlock();

            std::vector<string> songParts = delimitString(song,string(STANDARD_DELIMITER));

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

            if (listInt >= currentSongList.size()){
                //at the end of the songs you have
                playing = false;
                currentSongList = std::vector<string>(); //clears queue
                break;//for good measure;
            }

        }


    }
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

    inputFile.close();

}

int UniMusic::MusicPlayer::savePlaylist(std::vector<string> &vec, string &filename){
    //TODO - impelent try and accept blocks for this code
    std::ofstream output(filename);
    for (string line: vec) {
        output << line << std::endl;
    }
    output.close();
    return 0;
}




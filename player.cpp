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

#include "player.h"


#define MASTER_FILE "mf.txt"

//change to something else at somepoint
#define DEFAULT_CURRENT "playlist_test.txt"  



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

void UniMusic::MusicPlayer::setUp() {
    std::ifstream master(MASTER_FILE);
    string line;
    
    if (getline(master, line)) {
        currentPlaylistFileName = line;

        master.close();
    } else {
    //if one doesn't exits or its corrupted, create new one
        master.close();
        std::ofstream master(MASTER_FILE);
        master << DEFAULT_CURRENT << endl;
        master.close();
        currentPlaylistFileName = DEFAULT_CURRENT;
    }   



    displayList= readPlaylist(currentPlaylistFileName);
    //check 
    if (displayList.size() == 0) cout << "No songs" << endl;
}

void UniMusic::MusicPlayer::close() {
    playing = false;

    //let's see, 
    //on close, put the currently played filename on top
    string saved;
    std::ifstream finalMaster(MASTER_FILE);
    string line;
    getline(finalMaster, line); //forget first line
    while (getline(finalMaster, line)) {
        saved += line+"\n";
    }

    std::ofstream newMaster(MASTER_FILE);
    newMaster << currentPlaylistFileName << endl;
    newMaster << saved;
    newMaster.close();
}

void UniMusic::MusicPlayer::playSong(int index) {
    if (index >= displayList.size() || index < 0) return;

    std::vector<string> songParts = delimitString(displayList[index],string(STANDARD_DELIMITER));
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
        displayList[index] = songParts[0]+STANDARD_DELIMITER+songParts[1]+STANDARD_DELIMITER+url;
        savePlaylist(displayList, currentPlaylistFileName);

    }
    yi->openUrl(url);
}

std::vector<string> UniMusic::MusicPlayer::getAllFileNames(){
    std::ifstream master(MASTER_FILE);
    std::vector<string> filenames;
    string line;
    getline(master,line);
    int i = 1;
    while(getline(master,line)) {
        //std::vector<string> parts = delimitString(line,string(STANDARD_DELIMITER));
        filenames.push_back(line);
    }
    master.close();
    return filenames;
}


void UniMusic::MusicPlayer::runInterface() {
    //string playlist = HIDDEN_MY_PLAYLIST_ID_2;
    //string playlistFileName = "playlist_test.txt";

    //TODO - sets file with firstline being the the last playlist open
    // and all the other files being the potential playlists
    // [1.] lastfileopen.txt
    // [2.] playlist_id.txt displayname"playlist1"
    // [3.] playlist_id.txt displayname
    //ect.

    string playlistFileName;
    std::ifstream master(MASTER_FILE);
    string line;
    
    if (getline(master, line)) {
        playlistFileName = line;

        master.close();
    } else {
    //if one doesn't exits or its corrupted, create new one
        master.close();
        std::ofstream master(MASTER_FILE);
        master << DEFAULT_CURRENT << endl;
        master.close();
        playlistFileName = DEFAULT_CURRENT;
    }   



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
        /*
        else if (response == "p") {
            if(playing) {
                playing = false;
                cout << "Pause" << endl;
            } else if (currentSongList.size() != 0){
                playing = true;
                cout << "Play" << endl;
            }
        }
        */
        else if (response == "s") {
            playing = false;
        }
        else if (response == "g") {//get all playlists from the user
            std::vector<string> output;
            si->getUserPlaylists(HIDDEN_SPOTIFY_USER_ID,&output);

            string playlistFileName;    
            std::ofstream master(MASTER_FILE, std::ios_base::app); //opens in append mode
            
            
            //TODO
            for (string id: output){
                string name;
                si->getPlaylistName(id, &name);
                master << id+".txt"+STANDARD_DELIMITER+name<< endl;
            }
            master.close();
        }

        else if (response == "o") {//open a new file.
            std::ifstream master(MASTER_FILE);
            std::vector<string> filenames;
            string line;
            getline(master,line);
            int i = 1;
            while(getline(master,line)) {
                std::vector<string> parts = delimitString(line,string(STANDARD_DELIMITER));
                cout << i++ <<" "+parts[1]<< endl;
                filenames.push_back(parts[0]);
            }
            master.close();
            int choice;
            cout << "Choose a line by index: ";
            std::cin >> choice;
            choice--;
            //TODO - do error checking here

            playlistFileName = filenames[choice];
            conditionalCreate(playlistFileName);
            list = readPlaylist(playlistFileName);
            playing = false;
            

        }

        else if (response == "n"){
            if (playing){
                nextSong = true;

            }
        }



    } while (response != "j"); //janky, change later


    playing = false;

    //let's see, 
    //on close, put the currently played filename on top
    string saved;
    std::ifstream finalMaster(MASTER_FILE);
    getline(finalMaster, line); //forget first line
    while (getline(finalMaster, line)) {
        saved += line+"\n";
    }
    master.close();

    std::ofstream newMaster(MASTER_FILE);
    newMaster << playlistFileName << endl;
    newMaster << saved;
    newMaster.close();
}



void UniMusic::MusicPlayer::startPlayer(){

    int listInt = -1;



    int runtime;
    time_t lastTime;
    bool isUpdated = true;
    while (playing) {
        if (isUpdated || nextSong){
            if (nextSong) {
                nextSong = false;
            }

            listInt++;

            if (listInt >= currentSongList.size()){
                //at the end of the songs you have
                playing = false;
                currentSongList = std::vector<string>(); //clears queue
                break;//for good measure;
            }

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

            if (songParts.size() > 2) {
                url = songParts[2];
            } else {
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
            }
            isUpdated = false;
            yi->openUrl(url);

        }

        time_t currentTime = std::time(nullptr);
        if (currentTime - lastTime > runtime+70){
            isUpdated = true;
        

        }


    }
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


void UniMusic::MusicPlayer::savePlaylist(string playlistid, string filename){
    std::ofstream output(filename);
    string playlistOutput;
    string name;
    int result = si->getPlaylist(playlistid, 200, &playlistOutput,&name);
    if (result != 0) {
        std::cerr << "getPlaylist failed" << std::endl;
        return;
    }
    output << playlistOutput;

    output.close();
}



int UniMusic::MusicPlayer::savePlaylist(std::vector<string> &vec, string &filename){
    //TODO - implement try and accept blocks for this code
    std::ofstream output(filename);
    for (string line: vec) {
        output << line << std::endl;
    }
    output.close();
    return 0;
}

void UniMusic::MusicPlayer::conditionalCreate(string filename){
    string line;
    std::ifstream inputFile(filename);
    if (!getline(inputFile, line)) {
        string id = filename.substr(0, filename.length() -4); //removing .txt
        inputFile.close();

        savePlaylist(id, filename);
    } else {
        inputFile.close();

    }

    
    //END OF FUTURE FUNCTION
}





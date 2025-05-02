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

*/



using std::cout;
using std::endl;





//TODO - make spotify interface global so there's only one of them
int main(){
    //testSuite();
    runSimulator();

}




//TODO implement time and date functionality
//Maybe have a separate file keep track of dates that playlists have been updated

void savePlaylist(string playlistid, string filename){
    //TODO - maybe put in some error handelling 
    UniMusic::SpotifyInterface s = UniMusic::SpotifyInterface(HIDDEN_SPOTIFY_CLIENT_ID, HIDDEN_SPOTIFY_CLIENT_SECRET);

    std::ofstream output(filename);

    output << s.getPlaylist(playlistid);

    output.close();
}

std::vector<string> readPlaylist(string filename){
    //TODO - error checking
    string line;
    std::ifstream inputFile(filename);

    std::vector<string> v;

    while (getline (inputFile, line)) {
        v.push_back(line);
    }
    return v;

}


//I need a function that's going to let me scroll through a list and choose songs via numbers.
//commands keys are i-up, k-down, l-pick, j,exit
void runSimulator(){
    string playlist = HIDDEN_MY_PLAYLIST_ID_2;

    string playlistFileName = "playlist_test.txt";
    savePlaylist(playlist, playlistFileName);

    std::vector<string> list = readPlaylist(playlistFileName);
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
            string url = UniMusic::YoutubeInterface::findSongUrl(songParts[0],songParts[1], HIDDEN_YOUTUBE_API_KEY);
            UniMusic::YoutubeInterface::openUrl(url);
        }


        cout << string(response.length()+song.length()+2,'\b');


    } while (response != "j"); //janky, change later
}




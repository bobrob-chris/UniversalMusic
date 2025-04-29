#include <iostream>
#include <fstream>

#include <vector>
#include <ctime>

#include "song.h"
#include "network.h"
#include "htmlparser.h"
#include "spotifyinterface.h"

// security so I don't have things on github
#include "config.h"



//song.cc
//song.h

//generates a new id, guranteed to be unique, for each song

//create song
//song.getTitle()
//song.getArtist()
//song.getAlbum() -- just a string
//delete

//overloaded operations probably

//need something to represent albums and playlists
//collection.h
//collection.cc

//displayAll() - for debugging
//create
//delete
//add
//addList - or other data type
//an iterator
//remove(by index)
//remove(by id)
//date added in reference list
//date added in this list


//maybe have a unique file type to save song lists?
//could make a file class
//(or just save it in a txt file to begin with)

//fileInterface.h
//fileInterface.cc

//load (returns collection object from file object, file name)
//save (makes file object from collection object, file name)

//also an interface to create/read/write files


//finally the necessary 
//goes through spotify and makes a list of everything you need

//##############################
/*
4/28/25

I'm going to actually need to bring this alltogether at some point.
I've got Tina working on the front end, (gonna have to give her a more detailed design for that tmw)

But I got to figure out what "Essential Functions" I need

*/



using std::cout;
using std::endl;


//Function declarations for tests
void testNetwork();
void testCommandHP();
void testSpotifyInterface();
void testSaveFile();
void testSavePlaylist();

void testSuite();


//Function declarations for actual usable functions for final product
//________________

//Pretty self explanatory, but important note is it will also
//Include a time as the first line in the file which will be the date the file is written
//Otherwise, everything in the file will be of format "[name]"-"[artist]"
void savePlaylist(string playlistid, string filename);

//Returns a playlist given a filename, with each entry in the returned vector being
//"[name]"-"[artist]". Additionally if date is supplied 
std::vector<string> readPlaylist(string filename, time_t *date);

//Todo - write function and also write documenation for 
void updatePlaylist();

int main(){
    testSuite();

}

void testSuite() {

    //testNetwork();
    //testCommandHP();
    //testSpotifyInterface();
    //testSaveFile();
    testSavePlaylist();
}


void testNetwork() {
    //int result = socketTest();
    //cout << "Exit code: " <<result << endl;


    string request = "GET / HTTP/1.1\r\nConnection: close\r\n\r\n"; 
    //string request = "Post /api/token HTTP/1.1\r\n"
                    "Host: accounts.spotify.com\r\n"
                    "User-Agent: curl/8.2.1\r\n"
                    "Accept: */*\r\n"
                    "ContentType: application/x-www-form-urlencoded\r\n"
                    "Content-Type: application/x-www-form-urlencoded\r\n"
                    "Content-Length: 119\r\n"
                    "          \r\n"
                    "grant_type=client_credentials&client_id="+HIDDEN_SPOTIFY_CLIENT_ID+"&"
                    "client_secret="+HIDDEN_SPOTIFY_CLIENT_SECRET+"\r\n\r\n";



    UniMusic::NetworkInteface page = UniMusic::NetworkInteface("www.google.com");
    page.sendRequest(request);
    cout << page.getResponseBuffer() << endl;

}

void testCommandHP(){
    string output = string();
    map<string,string> m =  map<string, string>();
    m.insert({"Content-Type","application/x-www-form-urlencoded"});
    UniMusic::CommandHP p = UniMusic::CommandHP();
    int result = p.sendRequest("https://accounts.spotify.com/api/token", m, UniMusic::Post, "grant_type=client_credentials&client_id="+HIDDEN_SPOTIFY_CLIENT_ID+"&client_secret="+HIDDEN_SPOTIFY_CLIENT_SECRET, &output);
    cout << output << endl;
    

}

//Test deprecated since introduction of playlist builder
void testSpotifyInterface() {
    UniMusic::SpotifyInterface s = UniMusic::SpotifyInterface(HIDDEN_SPOTIFY_CLIENT_ID, HIDDEN_SPOTIFY_CLIENT_SECRET);
    //cout << "Access Token: " << s.getAccessToken() << endl;

    //cout << "Playlist fetching example: " << s.getPlaylist("3wwGdfUSREap8DgIJMbSCA") << endl;
    //This works 
}

void testSaveFile() {
    UniMusic::SpotifyInterface s = UniMusic::SpotifyInterface(HIDDEN_SPOTIFY_CLIENT_ID, HIDDEN_SPOTIFY_CLIENT_SECRET);

    string playlist = HIDDEN_MY_PLAYLIST_ID;

    std::ofstream output("playlist_test.txt");

    output << s.getPlaylist(playlist);

    output.close();

}


void testSavePlaylist(){
    string playlist = HIDDEN_MY_PLAYLIST_ID;

    string playlistName = "playlist_test.txt";

    savePlaylist(playlist, playlistName);

    std::vector<string> list = readPlaylist(playlistName, nullptr);

    for (string song: list) {
        cout << song << endl;
    }
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



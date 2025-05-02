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


using std::endl, std::cout;

void testSuite() {


    //If its commented out that means I'm satisfied with how the test runs so far.

    //testNetwork();
    //testCommandHP();
    //testSpotifyInterface();
    //testSaveFile();
    //testSavePlaylist();
    //testDelimiterAndQuotationRemover();
    //testYoutubeURLGet();
    testYoutubeURLSearch();
    
}







void testDelimiterAndQuotationRemover() {
    std::vector<string> output = readPlaylist("playlist_test.txt",nullptr);
    std::vector<string> name = delimitString(output[0],string("-"));
    cout << removeQuotation(name[0]) << endl; //I think this should be cheri cheri lady
    cout << removeQuotation(name[1]) << endl; //I think this should be modern talking

    

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

    string playlistFileName = "playlist_test.txt";

    savePlaylist(playlist, playlistFileName);

    std::vector<string> list = readPlaylist(playlistFileName, nullptr);

    for (string song: list) {
        cout << song << endl;
    }
}




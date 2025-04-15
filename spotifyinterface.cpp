#include "spotifyinterface.h"
#include "htmlparser.h"
#include <iostream>


string findToken(const string &input, const string &identifier);

UniMusic::SpotifyInterface::SpotifyInterface(string clientId, string clientSecret){
    curlWrapper = CommandHP();
    this->clientId = clientId;
    this->clientSecret = clientSecret;
    generateAccessToken();
}


void UniMusic::SpotifyInterface::generateAccessToken(){
    //Assumes return from spotify service will be {access_token:"...","token_type":"Bearer","expires_in":3600}
    string output = string();
    map<string,string> m =  map<string, string>();
    m.insert({"Content-Type","application/x-www-form-urlencoded"});
    
    string body = "grant_type=client_credentials&client_id="+clientId+"&client_secret="+clientSecret;
    
    int result = curlWrapper.sendRequest("https://accounts.spotify.com/api/token", 
                m, UniMusic::Post, body, &output);

    //TODO - check if result is not zero;
    
    accessToken = findToken(output, "access_token");

}

string UniMusic::SpotifyInterface::getPlaylist(string playlistId) {
    string output = string();
    map<string,string> m = map<string, string>();
    m.insert({"Authorization","Bearer "+accessToken});
    int result = curlWrapper.sendRequest("https://api.spotify.com/v1/playlists/"+playlistId, m, UniMusic::Get, string(), &output);
    return string(output);
}

string findToken(const string &input, const string &identifer) {
    // TODO - add some sanity error checking and all that jazz

    // assuming {"somehting":"bleh","something_else":"bleeeeeeeeeeeeh"}
    size_t a,b,c;

    a = input.find(identifer);
    b = input.find(":",a)+2;
    c = input.find("\"", b);

    return input.substr(b,c-b);
}
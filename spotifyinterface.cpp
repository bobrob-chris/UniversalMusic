#include "spotifyinterface.h"
#include "htmlparser.h"
#include <iostream>
#include <stack>


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
    string output2 = string();
    string final_output = string();

    map<string,string> m = map<string, string>();
    m.insert({"Authorization","Bearer "+accessToken});
    int result = curlWrapper.sendRequest("https://api.spotify.com/v1/playlists/"+playlistId, m, UniMusic::Get, string(), &output);
    int second_result = curlWrapper.sendRequest("https://api.spotify.com/v1/playlists/"+playlistId+"/tracks?offset=100&limit=100", m, UniMusic::Get, string(), &output2);

    
    output += output2;
   

    //TODO - write a tree generator that keeps track of all the elements in output instead of going by guesswork for 

    //can delimit songs in playlist by added_at
    //then find "artists"
    //then find "name":[artist name]

    //then duration_ms

    //then "name":song_name

    std::stack<string> s = std::stack<string>();


    //This whole thing could probably be made a lot faster
    int count = 0; 
    size_t addedPos = output.find("added_at");

    while (addedPos != string::npos) {//while added_at is still found

        size_t artistsPos = output.find("artists",addedPos); //only finds first artist .. TODO - make it so that it finds multiple artists at some point

        size_t namePos = output.find("name",artistsPos);

        string artistName = findToken(output.substr(namePos),"name");

        size_t durationPos = output.find("duration_ms",namePos);

        string songName = findToken(output.substr(durationPos), "name");

        addedPos = output.find("added_at",durationPos);

        final_output += songName+"-"+artistName + "\n";
        
        

    }  


  
    
    return final_output;
}


string UniMusic::SpotifyInterface::getSong(string songId) {
    string output = string();
    map<string,string> m = map<string, string>();
    m.insert({"Authorization","Bearer "+accessToken});
    return "NOT DONE"; //TODO - ...
}

string findToken(const string &input, const string &identifer) {
    // TODO - add some sanity error checking and all that jazz

    // assuming {"somehting":"bleh","something_else":"bleeeeeeeeeeeeh"}
    size_t a,b,c;

    a = input.find(identifer);
    b = input.find(":",a)+1;
    c = input.find(",", b);

    return input.substr(b,c-b);
}
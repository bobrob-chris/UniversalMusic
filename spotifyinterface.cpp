#include "spotifyinterface.h"
#include "utils.h"
#include <iostream>
#include <stack>

#define STANDARD_DELIMITER ","


UniMusic::SpotifyInterface::SpotifyInterface(const string clientId, const string clientSecret){
    curlWrapper = CommandWI();
    this->clientId = clientId;
    this->clientSecret = clientSecret;
    int result = generateAccessToken();
    //TODO - check result here, idk what to do if its not zero tho
}


int UniMusic::SpotifyInterface::generateAccessToken(){
    //Assumes return from spotify service will be {access_token:"...","token_type":"Bearer","expires_in":3600}
    string output = string();
    map<string,string> m =  map<string, string>();
    m.insert({"Content-Type","application/x-www-form-urlencoded"});
    
    string body = "grant_type=client_credentials&client_id="+clientId+"&client_secret="+clientSecret;
    
    int result = curlWrapper.sendRequest("https://accounts.spotify.com/api/token", 
                m, UniMusic::Post, body, &output);

    if (result != 0){
        return 1;
    }
    
    result = findToken(output, "access_token", &accessToken);
    if (result != 0){
        return 1;
    }
    return 0;
}

int UniMusic::SpotifyInterface::getPlaylist(string playlistId, int maxSongs, string *output, string*name) {
    string curlWrapperResult = string();
    string requestResult = string();
    string final_output = string();


    map<string,string> m = map<string, string>();
    m.insert({"Authorization","Bearer "+accessToken});

    int times = maxSongs/100 + 1;
    //times should at least be 1


    int result = curlWrapper.sendRequest("https://api.spotify.com/v1/playlists/"+playlistId, m, UniMusic::Get, string(), &requestResult);
    if (result != 0) {
        return 1;
    }

    for (int i = 1; i < times; i++) {
        string offset = std::to_string(i*100);
        int result = curlWrapper.sendRequest("https://api.spotify.com/v1/playlists/"+playlistId+"/tracks?offset="+offset+"&limit=100", m, UniMusic::Get, string(), &curlWrapperResult);
        if (result != 0){
            return 1;
        }
        requestResult += curlWrapperResult;

    }

    if (name != nullptr) findToken(requestResult,"\"name\"",name);
    
    //can delimit songs in playlist by added_at
    //then find "artists"
    //then find "name":[artist name]

    //then duration_ms

    //then "name":song_name


    //TODO - new thing, if find token is an error, just leave it blank in that part of the song, or algternatively, don't add it


    size_t addedPos = requestResult.find("added_at");
    if (addedPos == string::npos) {
        return 2;
    }

    while (addedPos != string::npos) {//while added_at is still found

        string artistName, songName;


        size_t artistsPos = requestResult.find("artists",addedPos); //only finds first artist .. TODO - make it so that it finds multiple artists at some point
        if (artistsPos == string::npos) return 1;



        size_t namePos = requestResult.find("name",artistsPos);
        if (namePos == string::npos) return 1;


        result = findToken(requestResult.substr(namePos),"name", &artistName);
        if (result != 0) return 1;


        size_t durationPos = requestResult.find("duration_ms",namePos);
        if (durationPos == string::npos) return 1;

        //string duration = findToken(output.substr(durationPos), "duration_ms");


        result = findToken(requestResult.substr(durationPos), "name", &songName);
        if (result != 0) return 1;


        addedPos = requestResult.find("added_at",durationPos);


        //final_output += removeQuotation(songName)+"-"+removeQuotation(artistName) +"\n";//+"-"+ removeQuotation(duration)
        final_output += songName+STANDARD_DELIMITER+artistName +"\n";//+"-"+ removeQuotation(duration)


    }  



    *output = final_output;

    return 0;
}

//TODO - implement this
int UniMusic::SpotifyInterface::getSong(string songId, string *output) {
    return 1;
}


int UniMusic::SpotifyInterface::getUserPlaylists(const string &user, std::vector<string> *output){
    map<string,string> m = map<string, string>();
    m.insert({"Authorization","Bearer "+accessToken});


    string requestResult;
    int result = curlWrapper.sendRequest("https://api.spotify.com/v1/users/"+user+"/playlists", m, UniMusic::Get, string(), &requestResult);
    //std::cout << requestResult << std::endl; //TODO - delete later



    //THIs loop is so janky but it works I suppose
    size_t bracket = requestResult.find("[");

    while (bracket != string::npos) {

        size_t spot = requestResult.find( "href",bracket);
        if (spot == string::npos) {
            break;
        }
        string url;
        requestResult = requestResult.substr(spot);
        findToken(requestResult,"href",&url);
        if (url.find("tracks") == string::npos && url.find("playlists") != string::npos) {
            size_t p = url.find("playlists")+10;
            url = url.substr(p,url.length() - p -1);
            output->push_back(url);

        }


        size_t collaborative = requestResult.find("[");

    }
    return 0;

}

int UniMusic::SpotifyInterface::getPlaylistName(string playlistId, string*name){
    string curlWrapperResult = string();
    string requestResult = string();


    map<string,string> m = map<string, string>();
    m.insert({"Authorization","Bearer "+accessToken});



    int result = curlWrapper.sendRequest("https://api.spotify.com/v1/playlists/"+playlistId, m, UniMusic::Get, string(), &requestResult);
    if (result != 0) {
        return 1;
    }

    if (name != nullptr) {
        findToken(requestResult,"\"name\"",name);
        return 0;
    } else {
        return 1;
    }
}




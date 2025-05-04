#ifndef _SPOTIFYINTERFACE_H_
#define _SPOTIFYINTERFACE_H_
#include "utils.h"
#include <string>
#include <memory>
#include <vector>

namespace UniMusic {

//Interface for interacting with the spotifyAPI
class SpotifyInterface {
    private:
        CommandWI curlWrapper;
        string clientId;
        string clientSecret;

        string command; 
        string accessToken;
        //Kinda the same thing as the getAccess token before,
        //If it results in 1, error occured, otherwise, with zero,
        //Everything is fine, and it saved the result in accessToken.
        int generateAccessToken();



    public:
        SpotifyInterface(const string clientId, const string clientSecret);
        ~SpotifyInterface() = default;

        //The Access Token is generated upon creation
        //It provides a simpler way to interact with spotify api
        //However it expires after 30 mins, and needs to be regenerated. 
        //TODO - error handelling for exec commnad
        //TOOD - setup regenerating access token
        string &getAccessToken(){return accessToken;};

        //TODO - all the following methods should have a way to check that their access token is valid.
        //TODO - check all outputs for error handeling

        //update -- SO MUCH ERROR HANDLING

        //This method  grabs a playlist given a playlistId and returns it in output, returns 0, if success, 1 if error, 2 if no songs found
        //The output is every song in songName-artist delimited by newlines
        int getPlaylist(string playlistId, int maxSongs, string *output); 

        //This method  grabs a songName and returns it in output, returns 0, if success, 1 if error
        int getSong(string songId, string *output);

        //This method grabs all the oublic playlistIds for the given user and puts it in output, 
        int getUserPlaylist(const string &user, std::vector<string> *output);
};



}



#endif
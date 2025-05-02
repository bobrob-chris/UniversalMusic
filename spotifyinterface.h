#ifndef _SPOTIFYINTERFACE_H_
#define _SPOTIFYINTERFACE_H_
#include "utils.h"
#include <string>
#include <memory>

namespace UniMusic {

class SpotifyInterface {
    private:
        CommandHP curlWrapper;
        string clientId; //TODO - when I make this public on github this needs to be made more secure. look into github secrets
        string clientSecret; //TODO - same as above but especially for this

        string command; 
        string accessToken;
        void generateAccessToken();


    public:
        SpotifyInterface(string clientId, string clientSecret); //TODO - probably going to need credentials in the constructor at some point
        ~SpotifyInterface() = default;

        string &getAccessToken(){return accessToken;};

        string getPlaylist(string playlistId); //TODO - implemnt a version of this that returns a vector instead of a string (might not be needed, we'll see).

        string getSong(string songId);

        string getTracks();

};



}



#endif
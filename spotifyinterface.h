#ifndef _SPOTIFYINTERFACE_H_
#define _SPOTIFYINTERFACE_H_
#include "htmlparser.h"
#include <string>


namespace UniMusic {

struct songNode {
    string id; //prolly name/artist
    std::unique_ptr<songNode> next;
    songNode(string _id) {id = _id; next = nullptr;}
    ~songNode() = default;
};

struct playlistBuilder {
    std::unique_ptr<songNode> song;
    //Honestly for the constrctor, I'll just have it as an object
    //Don't have to worry about a destructor because of smart pointers
    playlistBuilder() {song = std::unique_ptr<songNode>(new songNode("NULL"));}

    bool hasNext() {return song->id == "NULL";} // Damn janky this is, but I don't want to fix it right now
    // TODO - make this entire idea less janky
    void next() {std::unique_ptr<songNode> a = std::move(song->next); song = std::move(a);} //increments to next one
    string get() {return song->id;}//returns them in song - artist (at least for now)
                    //will err if doesn't have any more
};

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

        playlistBuilder getPlaylist(string playlistId);

        string getSong(string songId);

        string getTracks();

};



}



#endif
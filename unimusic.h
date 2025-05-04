#include <string>
#include <vector>
#include <thread>
#include <mutex>

#ifndef ___UNIMUSIC_H__
#define ___UNIMUSIC_H__

using std::string;

namespace UniMusic {

//I'm creating a class to run the 
class MusicPlayer {
    private:
        //Music player usses is to make sure 
        bool playing;

        //Creates a list of songs that the music player will and take the next one from the top.
        std::vector<string> currentSongList;

        //maintains the thread for the player so that the destructor can wait for it to finish before 
        //existing the program
        std::thread player;

        //maintains the current name of the file
        string currentFile; 

        //So we can reuse the spotify interface
        SpotifyInterface *si;

        //So we can reuse the youtube interface
        YoutubeInterface *yi;

    public:
        MusicPlayer(const string spot_client_id, const string &spot_client_secret, const string &yt_key){        
            si = new SpotifyInterface(spot_client_id, spot_client_secret);
            yi = new YoutubeInterface(yt_key);
            playing = false;
        }
        ~MusicPlayer(){
            delete si, yi;
        }

        

        //Runs interface from console initially, but eventually from interface Tina's making
        //Kinda has structure to runSimulator(). When you call it, there will be commands for doing various things
        //All commands will correspond to various commands that the graphic interface should be able to call.
        //Play/Pause - p
        //Toggle Shuffle - s //implementation details: should either recreate regular list or recreate random list
        //Skip -, kinda hard to do
        // 
        void runInterface();


        //A function to be run by a thread created by runInterface which reads class variables and manages
        //the music be played somewhat indepndent of the interface ocnsole.
        void startPlayer();


        //Pretty self explanatory, but important note is it will also
        //Include a time as the first line in the file which will be the date the file is written
        //Otherwise, everything in the file will be of format "[name]"-"[artist]"
        //TODO implement time and date functionality
        //Maybe have a separate file keep track of dates that playlists have been updated
        //TODO - maybe put in some error handelling 

        void savePlaylist(string playlistid, string filename);


        //Returns a playlist given a filename, with each entry in the returned vector being
        //"[name]"-"[artist]". Additionally if date is supplied 
        std::vector<string> readPlaylist(string filename);

        //Todo - write function and also write documenation for 
        void updatePlaylist();


        //I'm gonna need a file that converts names of playlists to their file numbers
        //and associated functionality with that
        //maybe just store a map

        //but also have an option to have no file associated with a playlist name
        //(but will have spotify playlist id)

        //so that I can have a function which gets all the playlists from your profile id


        void changeYoutube(int songIndex, string youtubeIdentifer,string filename);

        void insertYoutubeAllNotFilled(string filename);


        //TODO - add autoplay
        //TODO - then add shuffle




};
}




#endif
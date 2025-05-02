#ifndef __YOUTUBE_INTERFACE_H__
#define __YOUTUBE_INTERFACE_H__

#include <string>


namespace UniMusic {

using std::string;

class YoutubeInterface {
    public:
        
        //name and artist should be free of any extraneous characters,
        //returns a link that upon pasting into a search bar will pull up
        //a video of the song
        //can only do this 100 times per day apparently.
        // 1 if error, 0 if success, result in output
        static int findSongUrl(string &name, string &artist,const string &apiKey, string *output);

        //Opens the url of the video in your default browser
        //should either be of the format //https://www.youtube.com/watch?v=rtOvBOTyX00
        //or just /watch?v=rtOvBOTyX00
        static void openUrl(string &url);

        //TODO - make a function that returns a vector<string> of a bunch of youtube videos related to 
        //song search so that user can choose which one they want, as well as get the name of the video

};

}

#endif
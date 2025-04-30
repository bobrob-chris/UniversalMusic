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
        static string findSongUrl(string name, string artist, string apiKey);

        //should either be of the format //https://www.youtube.com/watch?v=rtOvBOTyX00
        //or just /watch?v=rtOvBOTyX00
        static void openUrl(string url);

};

}

#endif
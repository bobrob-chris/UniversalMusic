#ifndef __YOUTUBE_INTERFACE_H__
#define __YOUTUBE_INTERFACE_H__

#include <string>

namespace UniMusic {

using std::string;

class YoutubeInterface {
    public:
        static string findSongUrl(string name, string artist);
        static void openUrl(string url);

};

}

#endif
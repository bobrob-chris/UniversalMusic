#include "youtubeinterface.h"
#include <string>
#include <iostream>
#include <windows.h>
#include <shellapi.h>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#include "htmlparser.h"
#include "exec.h"

//This can't go wrong right?
const string stringRoot = "https://www.youtube.com";

using std::string;

//harder to implemnt of the two
string UniMusic::YoutubeInterface::findSongUrl(string name, string artist) {
    std::cout << "Not yet Implemented, come back later" << std::endl;
    //TODO - implement later
    return "Blllaaah";

}

void UniMusic::YoutubeInterface::openUrl(string url) {
    if (url.find(stringRoot) == string::npos) {
        exec(string("start "+stringRoot+url).c_str());
    } else {
        exec(string("start "+url).c_str());
    }
}

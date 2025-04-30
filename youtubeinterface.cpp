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



using std::string;

//harder to implemnt of the two
string UniMusic::YoutubeInterface::findSongUrl(string name, string artist) {
    std::cout << "Not yet Implemented, come back later" << std::endl;
    //TODO - implement later
    return "Blllaaah";

}

void UniMusic::YoutubeInterface::openUrl(string url) {
    //ShellExecute(0, 0, "http://www.google.com", 0, 0 , SW_SHOW );
    //TODO - I hate using null
    //so typing this into shell makes google open
    //start https://www.google.com
    //so...
    //Forget SheLlExecute (blah blah blah)
    //exec("start https://www.google.com");
    //ShellExecute(NULL, "start", "https://www.google.com", 0, 0 , SW_SHOWNORMAL);
    //TODO - get exec out of htmlparser - why the hell did I do it like that
    exec("start https://www.google.com");




}

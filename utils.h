/*Copyright 2025, by Robert Spencer, all rights reserved*/
#ifndef __UTILS_H_
#define __UTILS_H_

#include <string>
#include <vector>
#include <map>

using std::string, std::map;



namespace UniMusic {

/*
//Basic Structure defining how songs are organized in files and displayed
//Only mandatory components are song and artist
//Duration is in milliseconds
//Youtube id, name, and artist are all strings
struct Song {
    string name;
    string artist;
    int duration;
    string yId;
};
*/


//Enumeration to be used by all classes that inherit HTML Parser
//So that we can use type checking in function declaration
enum Method {
    Get,
    Post
};


// HTML is a broad interface that defines how various systems
// interact with the web. Provides the basic format to be able 
// to send a get request. Seems like a waste since only Command
// WI implements it as of right now but originally I had another interface that was going to use
// Sockets. 
class WebInterface{
    public: 
        //returns 0 if correct, something else otherwise

        virtual int sendRequest(string url, map<string, string> headers, Method method, string body, string *output) = 0;

};


// Windows commmand prompt based implementation of WebInterface. Uses
// curl or windows equivalent to send get requests to internet pages.
class CommandWI: public WebInterface {
    public:
     int sendRequest(string url, map<string,string> headers, Method method, string body, string *output);
};



}

//The main functionality of this is it provides an interface to execute 
//Commands in a bash terminal. The command is stored in a string format in cmd,
//and the result is stored in the output. 
//TODO - implement error handelling in this function - this is vital since most of the program depends on it..
//     - or maybe, the error from the terminal will just appear in the output, I don't know
std::string exec(string &cmd);


//Utility function for taking strings in the file and delimiting them into
//components for string. Equivalent to python's split function.
//TODO - implement a duplicate with constant char instead of string for the delimiter
std::vector<string> delimitString(string &input, string &delimiter);


//Strings from the spotify interface, always look like
//"Song name", so this just removes the quotation so it looks like
//Song name
//Should remove quotation marks separetely, if there's one at the beginning or one at the
//End without affecting broader functionality.
string removeQuotation(string &input);


//Given an identifer, it finds everything between the next colon and the 
//next comma (must be in that order), after the identifer and returns it.
//I've found it useful for parsing api results.
//
//ex: "identifier":"[what we return]",
//Returns -1, if error
//returns 0, if success
//otherwise puts things in output
int findToken(const string &input, const string &identifier, string *output);



//helper method to replace all instances of find in text with replace
string replaceAll(string text, string find, string replace);


#endif

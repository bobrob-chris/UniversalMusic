#ifndef __UTILS_H_
#define __UTILS_H_

#include <string>
#include <vector>
#include <map>

using std::string, std::map;

namespace UniMusic {

enum Method {
    Get,
    Post
};


// just an interface to be implemented later
class HTMLParser{
    public: 
        virtual int sendRequest(string url, map<string, string> headers, Method method, string body, string *output) = 0;

};

class CommandHP: public HTMLParser {
    public:
     int sendRequest(string url, map<string,string> headers, Method method, string body, string *output);
};



}


std::string exec(const char* cmd);


//Utility function for taking strings in the file and delimiting them into
//components for string
std::vector<string> delimitString(string &input, string &delimiter);
//TODO - implement a duplicate with constant char instead of string for the delimiter


//Strings from the spotify interface, always look like
//"Song name", so this just removes the quotation so it looks like
//Song name
string removeQuotation(string &input);


//useful for stringing parsing in results from apis
//in input, finding "identifier":"[what we return]"
string findToken(const string &input, const string &identifier);


#endif

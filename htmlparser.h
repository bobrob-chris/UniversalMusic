#ifndef _HTMLPARSER_H_
#define _HTMLPARSER_H_
#include <string>
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
        virtual int sendRequest(string url, map<string, string> headers, Method method, string body = nullptr) = 0;

};

class CommandHP: public HTMLParser {
    int sendRequest(string url, map<string,string> headers, Method method, string body);
};



}

#endif
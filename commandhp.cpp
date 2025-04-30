#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>


#include "htmlparser.h"
#include "exec.h"

using UniMusic::Method;

std::string exec(const char* cmd);


int UniMusic::CommandHP::sendRequest(string url, map<string, string> headers, Method method, string body, string *output) {
    string command("curl ");
    if (method == Post){
        command += "-X POST ";
    } else {
        command += "-X GET ";
    }
    command += "\""+url+"\" ";
    for (auto const& [header, content] : headers) {
        command += "-H \"" + header + ": " + content + "\" ";
    }
    command += " -d \"" + body + "\" -s"; 

    try {
    
       *output = string(exec(command.c_str()));
        return 0;
    } catch (std::runtime_error error) {
        return 1;
    }

}

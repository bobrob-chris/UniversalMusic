#include "utils.h"

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>


//TODO - understand this function
//https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}


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
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>


#include "htmlparser.h"

using UniMusic::Method;

int UniMusic::CommandHP::sendRequest(string url, map<string, string> headers, Method method, string body = nullptr) {
    std::cout << exec("curl \"https://accounts.spotify.com/api/token\" -Method Post -ContentType \"application/x-www-form-urlencoded\" -Body \"grant_type=client_credentials&client_id=8d3f4f0f52a3462dab3793c04eabcf50&client_secret=cdc52ba00539475a9f4e291fb0666626\"") << std::endl;
}


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
/*Copyright 2025, by Robert Spencer, all rights reserved*/
#include "utils.h"

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <vector>


//TODO - understand this function
//https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
std::string exec(string &cmd) {
    const char* cmd_c = cmd.c_str();
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd_c, "r"), _pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}


int UniMusic::CommandWI::sendRequest(string url, map<string, string> headers, Method method, string body, string *output) {
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
    
       *output = string(exec(command));
        return 0;
    } catch (std::runtime_error error) {
        return 1;
    }

}

std::vector<string> delimitString(string &input, string &delimiter){
    string copy = input;
    std::vector<string> result;
    size_t pos = copy.find(delimiter);
    if (pos == string::npos) {
        return result;
    }
    size_t oldPos = 0;
    do {
        string seg = copy.substr(oldPos, pos);
        result.push_back(seg);
        copy = copy.substr(pos+1);
        oldPos = pos;
        pos = copy.find(delimiter);
    } while (pos != string::npos);

    result.push_back(copy);
    return result;

}

string removeQuotation(string &input) {
    string output = string();
    if (output.substr(0,1) == "\""){
        output = output.substr(1);
    }
    if (output.substr(output.length()-1, 1) == "\"") {
        output = output.substr(0, output.length()-1);
    }
    return output;
}



int findToken(const string &input, const string &identifer, string *output) {

    size_t a,b,c;

    a = input.find(identifer);
    if (a == string::npos){
        return -1;
    }
    b = input.find(":",a);
    if (b == string::npos){
        return -1;
    }
    b++;
    c = input.find(",", b);
    if (c == string::npos){
        return -1;
    }
    *output = input.substr(b,c-b);
    return 0;
}

string replaceAll(string text, string find, string replace){
    //almost exactly copied from geeks for geeks

    string copy = text;

    size_t pos = copy.find(find);

    while (pos != string::npos) {

        copy.replace(pos, find.size(), replace);
        pos = copy.find(find,pos + replace.size());
    }

    return copy;

}
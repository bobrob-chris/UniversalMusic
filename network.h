#ifndef NETWORK_H
#define NETWORK_H
#include <winsock2.h>
#include <iostream>
#include <string>

using std::string;
namespace UniMusic {


// I need a class which will simplify the process of
// making https get and post requests for the spotify api

class NetworkInteface {
    private:
        WSADATA wsaData;
        SOCKET sock;

        string hostName;
        string responseBuffer;
        struct sockaddr_in serverAddr;

        string resolveHostName(const string &host);
        boolean invalid;
    public:
        //constructor
        //
        NetworkInteface(const string &host);
        //destructor
        ~NetworkInteface();

        //functions

        //sends request to host,
        //but wipes out responseBuffer in the process
        int sendRequest(const string &request);
        string& getResponseBuffer();


};

// This is going to be weird for a moment

int socketTest();

}

#endif
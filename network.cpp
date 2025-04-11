#include "network.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <iostream>


#define PORT 443

#define DEBUG true
//TODO - change to false when you're done

//TODO - figure out what this does
#pragma comment(lib, "Ws2_32.lib")




using std::cout, std::endl, std::cerr;

//To be implemented
UniMusic::NetworkInteface::NetworkInteface(const string &host){
    invalid = false;

    SOCKADDR_IN sin;

    //TODO - figure out what MAKEWORD does
    int startupResult = WSAStartup(MAKEWORD(2, 0), &wsaData);
    if (startupResult != 0) {
        if (DEBUG) {cerr << "WSAStartup failed: " <<  startupResult << endl;}
        //TODO - throw error 
        invalid = true;
        return;
    }


    //sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == INVALID_SOCKET) {
        if (DEBUG) {cerr << "Socket creation failed: " << WSAGetLastError() << endl;}
        //TODO - throw error instead, idk
        invalid = true;
        return;
    }


    sin.sin_addr.s_addr = inet_addr(resolveHostName(host).c_str()); 
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT); // port HTTP.

    // Probably there's a return for this too that I should check and make sure that nothing's broken
    connect(sock, (SOCKADDR *)&sin, sizeof(sin)); 

}

// I think I can include all the cleanup in the destructor
UniMusic::NetworkInteface::~NetworkInteface(){
    closesocket(sock);
    WSACleanup();
}


int UniMusic::NetworkInteface::sendRequest(const string &request) {
    if (invalid){
        return 1;
    }
    char buffer[4096], crequest[5000];
    int i;
    size_t request_tail;
    
    
    responseBuffer = "";    
    request_tail= request.size()+1;
    strncpy(crequest, request.c_str(), request_tail);

    size_t sent, total_sent;
    total_sent = 0;
    do {
       sent = send(sock, crequest+total_sent, strlen(crequest-total_sent), 0); 
        total_sent += sent;
    } while (total_sent < strlen(crequest));


    i = 0;
    do
    {
        i = recv(sock, buffer, sizeof(buffer), 0);
        responseBuffer += string(buffer);
    } while (i != 0);

    return 0;

}

string& UniMusic::NetworkInteface::getResponseBuffer(){
    //TODO - research if this is a copy or the actual thing;
    if (!invalid) {return responseBuffer;}
    else {return string();}
}


string UniMusic::NetworkInteface::resolveHostName(const string &host) {

    //getaddrinfo stuff

    struct addrinfo hints = {0};
    struct addrinfo* result = nullptr;


     // Setup hints
     hints.ai_family = AF_UNSPEC;      // AF_INET for IPv4 only, AF_INET6 for IPv6 only
     hints.ai_socktype = SOCK_STREAM;  // TCP
     hints.ai_protocol = IPPROTO_TCP;

    int  iResult = getaddrinfo(host.c_str(), NULL, &hints, &result);
    if (iResult != 0) {
        if (DEBUG) {cerr << "getaddrinfo failed for " <<host<<": " << gai_strerrorA(iResult) << endl;}
        invalid = true;
        return nullptr;
        //TODO - throw some sort of error here

    }

    char ipstr[INET6_ADDRSTRLEN];

    for (struct addrinfo* ptr = result; ptr != nullptr; ptr = ptr->ai_next) {

        void* addr;
        const char* ipver;

        if (ptr->ai_family == AF_INET) { // IPv4
            struct sockaddr_in* ipv4 = (struct sockaddr_in*)ptr->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else { // IPv6
            struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)ptr->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        inet_ntop(ptr->ai_family, addr, ipstr, sizeof(ipstr));
        if (DEBUG) {std::cout<< ipver << ": " << ipstr << "\n";}
    }
    freeaddrinfo(result);

    return string(ipstr);

}




int UniMusic::socketTest()
{
    // a couple of hardecoded values
    // for testing purposes
    //curl "https://accounts.spotify.com/api/token" -Method Post -ContentType "application/x-www-form-urlencoded" -Body "grant_type=client_credentials&client_id=8d3f4f0f52a3462dab3793c04eabcf50&client_secret=cdc52ba00539475a9f4e291fb0666626"



    cout << "Starting socket test" << endl;
    // Initialize Winsock
    
    WSADATA wsaData;
    int Bresult = WSAStartup(MAKEWORD(2, 0), &wsaData);
    if (Bresult != 0) {
        printf("WSAStartup failed: %d\n", Bresult);
        return 1;
    }

    SOCKET sock;
    SOCKADDR_IN sin;

    char buffer[4096];

    string request = "GET / HTTP/1.1\r\nHost: spotify.com\r\nConnection: close\r\n\r\n"; // I guess this works, idk yet
    size_t request_tail = request.size()+1;
    
    char crequest[5000];
    strncpy(crequest, request.c_str(), request_tail);



    cout << "Winsock initialized" << endl;

    int i = 0;
    // Create a socket
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        printf("Socket creation failed: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    cout << "Socket created" << endl;

    string source = "";
    
    sock = socket(AF_INET, SOCK_STREAM, 0);



    //getaddrinfo stuff

    struct addrinfo hints = {0};
    struct addrinfo* result = nullptr;


     // Setup hints
     hints.ai_family = AF_UNSPEC;      // AF_INET for IPv4 only, AF_INET6 for IPv6 only
     hints.ai_socktype = SOCK_STREAM;  // TCP
     hints.ai_protocol = IPPROTO_TCP;

     const char* hostname = "www.spotify.com";

    int iResult;
     // Resolve the domain name
    iResult = getaddrinfo(hostname, NULL, &hints, &result);
    if (iResult != 0) {
        std::cerr << "getaddrinfo failed: " << gai_strerrorA(iResult) << "\n";
        WSACleanup();
        return 1;
    }


    std::cout << "IP addresses for " << hostname << ":\n";

    char ipstr[INET6_ADDRSTRLEN];

    for (struct addrinfo* ptr = result; ptr != nullptr; ptr = ptr->ai_next) {

        void* addr;
        const char* ipver;

        if (ptr->ai_family == AF_INET) { // IPv4
            struct sockaddr_in* ipv4 = (struct sockaddr_in*)ptr->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else { // IPv6
            struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)ptr->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        inet_ntop(ptr->ai_family, addr, ipstr, sizeof(ipstr));
        std::cout << "  " << ipver << ": " << ipstr << "\n";
        std::cout << ipstr << std::endl;
    }

    freeaddrinfo(result);



    sin.sin_addr.s_addr = inet_addr(ipstr); 
    sin.sin_family = AF_INET;
    sin.sin_port = htons(443); // port HTTP.

    connect(sock, (SOCKADDR *)&sin, sizeof(sin)); 

    send(sock, crequest, strlen(crequest), 0); 


    do
    {
        i = recv(sock, buffer, sizeof(buffer), 0);
        source += buffer;
    } while (i != 0);

    cout << "_____-_-_______-" << endl;
    cout << source << endl;


    // Clean up
    closesocket(sock);

    WSACleanup();
    return 0;
}

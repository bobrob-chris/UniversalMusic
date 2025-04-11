#include <iostream>
#include "song.h"
#include "network.h"
#include "htmlparser.h"

// design

//song.cc
//song.h

//generates a new id, guranteed to be unique, for each song

//create song
//song.getTitle()
//song.getArtist()
//song.getAlbum() -- just a string
//delete

//overloaded operations probably

//need something to represent albums and playlists
//collection.h
//collection.cc

//displayAll() - for debugging
//create
//delete
//add
//addList - or other data type
//an iterator
//remove(by index)
//remove(by id)
//date added in reference list
//date added in this list


//maybe have a unique file type to save song lists?
//could make a file class
//(or just save it in a txt file to begin with)

//fileInterface.h
//fileInterface.cc

//load (returns collection object from file object, file name)
//save (makes file object from collection object, file name)

//also an interface to create/read/write files


//finally the necessary 
//goes through spotify and makes a list of everything you need


using std::cout;
using std::endl;



int main(){
    //testNetwork();
    testCommandHP();
}

void testNetwork() {
    //int result = socketTest();
    //cout << "Exit code: " <<result << endl;


    string request = "GET / HTTP/1.1\r\nConnection: close\r\n\r\n"; 
    //string request = "Post /api/token HTTP/1.1\r\n"
                    "Host: accounts.spotify.com\r\n"
                    "User-Agent: curl/8.2.1\r\n"
                    "Accept: */*\r\n"
                    "ContentType: application/x-www-form-urlencoded\r\n"
                    "Content-Type: application/x-www-form-urlencoded\r\n"
                    "Content-Length: 119\r\n"
                    "          \r\n"
                    "grant_type=client_credentials&client_id=8d3f4f0f52a3462dab3793c04eabcf50&client_secret=cdc52ba00539475a9f4e291fb0666626\r\n\r\n";



    UniMusic::NetworkInteface page = UniMusic::NetworkInteface("www.google.com");
    page.sendRequest(request);
    cout << page.getResponseBuffer() << endl;

}

void testCommandHP(){
    UniMusic::CommandHP p = UniMusic::CommandHP();
    p.sendRequest("hello",std::map<string,string>(), UniMusic::Get);
}

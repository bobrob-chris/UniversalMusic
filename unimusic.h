#include <string>
#include <vector>

#ifndef ___UNIMUSIC_H__
#define ___UNIMUSIC_H__

using std::string;
//Function declarations for actual usable functions for final product
//________________

//Pretty self explanatory, but important note is it will also
//Include a time as the first line in the file which will be the date the file is written
//Otherwise, everything in the file will be of format "[name]"-"[artist]"
void savePlaylist(string playlistid, string filename);

//Returns a playlist given a filename, with each entry in the returned vector being
//"[name]"-"[artist]". Additionally if date is supplied 
std::vector<string> readPlaylist(string filename);

//Todo - write function and also write documenation for 
void updatePlaylist();


//I need a function that's going to let me scroll through a list and choose songs via numbers.
//commands keys are i-up, k-down, l-pick, j,exit
void runSimulator();

//I'm gonna need a file that converts names of playlists to their file numbers
//and associated functionality with that
//maybe just store a map

//but also have an option to have no file associated with a playlist name
//(but will have spotify playlist id)

//so that I can have a function which gets all the playlists from your profile id

#endif
#ifndef SONG_H
#define SONG_H
#include <string>
#include <list>
typedef unsigned long IdType;


// Using UniMusic as the namespace for this project
// do I need a standard namespace for this project?
// TODO - reseach if I need a namespace
namespace UniMusic {

using std::string, std::list;


// Basic data structure to represent the very basic unit of the project
// The Song
// TODO - make this into a class later
class Song {

    //INFO
    //__Mandatory Info__
    // should be unique <- for class
    IdType id;
    string name;
    string artist;

   
    //static IdType numSongs;

    //Gurantee a unique id for each song
    //static IdType idGenerator();

    public:
        //CONSTRUCTORS
        Song(const string &n, const string &a): name(n), artist(a){id = 0;}

        Song(const Song &other);


        //FUNCTION DECLARATIONS

        IdType getId() const {return id;}   
        string getName() const {return name;}
        string getArtist() const { return artist;}
};


};

#endif
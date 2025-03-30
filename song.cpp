#include "song.h"

using namespace UniMusic;

/*
IdType Song::idGenerator() {
    numSongs = 0;
    return numSongs++;
}
*/


Song::Song(const Song &other){
    id = other.id;
    name = other.name;
    artist = other.artist;
}

//
//  User.cpp
//  Radio Station
//
//  Created by Jo‹o Almeida on 19/05/13.
//

#include "Playlist.h"
#include "Music.h"

Playlist::Playlist() {
    
}

Playlist::~Playlist() {
    
}

void Playlist::addSong(Music *theSong, int playcount) {
    
}

void Playlist::removeSong(Music *theSong){
    
}

const std::vector<Music *> Playlist::search(int musicId, std::string title,  std::string artist, std::string author, std::string album, std::string music_genre, int year) {
    std::vector<Music *> returnVec;
    
    // If everything is null, return the full song list.
    
    if (!musicId && !title.compare("") && !artist.compare("") && !album.compare("") && !music_genre.compare("") && !year)
        return _thePlaylist;
    
    for (int i = 0; i < _thePlaylist.size(); i++) {
        Music *aMusic = _thePlaylist[i];
        
        if (aMusic->getId() == musicId) {
            
        }
    }
}

void Playlist::shuffle(){
    
}

unsigned int Playlist::count() {
    
}
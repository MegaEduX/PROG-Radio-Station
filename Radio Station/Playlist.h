//
//  Playlist.h
//  Created by Eduardo Almeida, Joao Almeida and Joao Ramos
//
//  This class manages a single playlist object and its songs/song count.
//

#ifndef PlaylistHeader
#define PlaylistHeader

#include <iostream>
#include <vector>
#include <map>

#include "Music.h"

class Playlist {
private:
	std::vector <Music> _thePlaylist;

public:
    //
    // Add and remove songs to the playlist, nothing major here.
    //
    
	void addSong(Music *theSong, int playCount);
	void removeSong(Music *theSong);
    
    //
    // As we are using the Music objects by reference, and using
    // the same object on the global/user/... playlists, we can
    // generate the top ten songs list dynamically.
    //

    // Returns Music * as the key and the song count as the object.
    
    // As maps are ordered, we can just loop through this.
    
	const std::map <Music *, int> topTenSongs();
    
    // Searches through the playlist and returns a vector with matches.

	const std::vector<Music *> search(std::string title, int year, std::string artist, std::string music_genre);
};

#endif
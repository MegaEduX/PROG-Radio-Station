#include <iostream>
#include <vector>
#include <map>

#include "Music.h"

class Playlist {
private:
	std::map <Music, int> thePlaylist;

public:
	void addSong(Music theSong, int playCount);
	void removeSong(Music theSong);

	std::vector <Music> topTenSongs();
	std::vector <int> topTenSongCount();

	std::vector<Music> search(std::string title, int year, std::string artist, std::string music_genre);
};
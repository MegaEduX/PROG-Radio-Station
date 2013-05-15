#include "RadioStation.h"
#include "Music.h"
#include "Playlist.h"
#include <vector>


bool RadioStation::setName(std::string name){
	if (name.size() <= 0)
		return false;
	
	_name = name;
	
	return true;
}

void RadioStation::generateSet(){
	_currentPlaySet = _allTracks;

	_currentPlaySet.shufflePlaylist();
}
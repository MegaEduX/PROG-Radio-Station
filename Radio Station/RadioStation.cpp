//
//  User.cpp
//  Radio Station
//
//  Created by Eduardo Almeida on 13/05/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#include "RadioStation.h"
#include "Music.h"
#include "Playlist.h"

const int setDivisor = 4;

RadioStation *RadioStation::rs_pInstance = NULL;

RadioStation* RadioStation::Instance() {
    if (!rs_pInstance)
        rs_pInstance = new RadioStation;
    
    return rs_pInstance;
}

RadioStation::RadioStation() {
    
}

bool RadioStation::setName(std::string name) {
	if (name.size() <= 0)
		return false;
	
	_name = name;
	
	return true;
}

std::string RadioStation::name() {
    return _name;
}

void RadioStation::generateSet() {
	Playlist newPlaylist;
    
    _currentPlaySet = newPlaylist;
    
    int setCount = (int)(_allTracks.count() / setDivisor);
    
    if (!setCount && _allTracks.count() > 0)
        setCount = 1; // This prevents rounding to 0 when x/y < 0.5.
    
    for (int i = 0; i < setCount; i++) {
        Music *track = _allTracks.getAllTracks()[i];
        
        _currentPlaySet.addSong(track);
        
        track -> addPlay();
    }
    
	_currentPlaySet.shuffle();
}

Playlist* RadioStation::allTracks() {
    return &_allTracks;
}

Playlist RadioStation::topTen() {
    return _topTen;
}

bool RadioStation::updateTopTen(Playlist thePlaylist) {
    if (thePlaylist.count() != 10)
        return false;
    
    _topTen = thePlaylist;
        
    return true;
}

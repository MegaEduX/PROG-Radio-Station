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

void RadioStation::generateSet() {
	_currentPlaySet = _allTracks;

	_currentPlaySet.shuffle();
}
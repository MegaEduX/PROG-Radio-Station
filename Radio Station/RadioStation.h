//
//  RadioStation.h
//  Created by Eduardo Almeida, Joao Almeida and Joao Ramos
//
//  This class takes care of the main Radio Station.
//

#ifndef RadioStationHeader
#define RadioStationHeader

#include <iostream>
#include <vector>
#include <string>

#include "Music.h"
#include "Playlist.h"

class RadioStation {
    
private:
    
	RadioStation(); // There can only be one radio station, so a singleton here is completely appropriate.

	RadioStation(RadioStation const&); // Copy constructor is private.
	RadioStation& operator=(RadioStation const&); // Assignment operator is private.

	static RadioStation *rs_pInstance;

	std::string _name;

	Playlist _allTracks;

	Playlist _currentPlaySet;

public:
    
	static RadioStation* Instance();
    
    bool setName(std::string name);
    
    std::string name();

	void generateSet(); // Generates a set randomly

	Playlist allTracks(); // Adicionado por razoes obvias
	
};

#endif
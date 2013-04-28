#include <iostream>
#include <vector>
#include <string>

#include "Music.h";
#include "Playlist.h"

class RadioStation {
private:
	RadioStation(); // There can only be one radio station, so a singleton here is completely appropriate.

	RadioStation(RadioStation const&); // Copy constructor is private.
	RadioStation& operator=(RadioStation const&); // Assignment operator is private.

	static RadioStation *rs_pInstance;

	std::string Name;

	Playlist allTracks;

	Playlist currentPlaySet;

public:
	static RadioStation* Instance();

	void generateSet(); // Generates a set randomly
	
};


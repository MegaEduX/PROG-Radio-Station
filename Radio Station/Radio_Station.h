#include <iostream>
#include <vector>
#include <string>
#include "Users.h";
#include "Music.h";
class RadioStation
{
private:
	std::string Name;
	std::vector<music *> music_tracks;
	std::vector<std::string> radio_listeners;


public:
	void addMusic(); // Adds a music to the list of music tracks to broadcast
	
	void EditMusicTrack(); // Edit the music track
	void DisplayTrack (); // Display the track
	void GenerateSet(); // Generates a set randomly
	std::vector<music *> SearchMusic (std::string title , int year, std::string artist , std::string music_genre); // Search the music track list of the station
};


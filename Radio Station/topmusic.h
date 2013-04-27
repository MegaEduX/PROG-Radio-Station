#include <iostream>
#include <string>
#include <vector>
#include "Music.h"

class topmusic
{
private:
	std::vector<music *> top_music;
public:
	
	void UpdateTop (); // Update the top list by the difference of Likes/Dislikes
	void DisplayTrack (); // Display the track

};
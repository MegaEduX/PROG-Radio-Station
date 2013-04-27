#include <iostream>
#include <string>
class music
{
private:
	int music_id;
	std::string title;
	std::string artist;
	std::string author;
	std::string album;
	std::string music_genre;
	std::string year;
	std::string likes;
	std::string dislikes;

	bool available;

public:
	void addLike (); // Adds a Like to a music
	void addDislike (); // Adds a Dislike to a music
	void setAvailable(bool availability); // Signal the music as unavailable
	//void DisplayTrack (); // Display the track

	void setMusicId(int theMusicId);
	int musicId();

	// por ai fora

};


#include <iostream>
#include <string>

class Music {
private:
	unsigned int id;

public:
	// Doing this with constructors and deconstructors is much better as we can
	// automatically fill the song id by accessing the radio music database.

	Music();
	~Music();

	unsigned int year;

	unsigned int likes;
	unsigned int dislikes;

	bool available;

	bool addLike(); // Adds a Like to a music
	bool addDislike(); // Adds a Dislike to a music

	void setAvailability(bool availability); // Signal the music as unavailable
};


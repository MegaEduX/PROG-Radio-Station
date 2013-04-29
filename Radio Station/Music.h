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
    
    //
    // User variables.
    //

	unsigned int year;

	unsigned int likes;
	unsigned int dislikes;
    
    unsigned int playCount;

	bool available;

	bool addLike(); // Adds a Like to a music
	bool addDislike(); // Adds a Dislike to a music
};


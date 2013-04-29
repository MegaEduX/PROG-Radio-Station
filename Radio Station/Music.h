#include <iostream>
#include <string>

class Music {
    
private:
    
	unsigned int musicId;
    
    unsigned int year;
    
    unsigned int likes;
    unsigned int dislikes;
    
    unsigned int playCount;
    
    bool available;

public:
    
	// Doing this with constructors and deconstructors is much better as we can
	// automatically fill the song id by accessing the radio music database.

	Music();
	~Music();
    
    //
    // User variables.
    //
    
    bool setMusicId(unsigned int theId);
    const unsigned int musicId();
    
    bool setYear(unsigned int theYear);
    const unsigned int year();
    
    const unsigned int likes();
    const unsigned int dislikes();
    
    bool addLike();
    bool addDislike();
    
    const unsigned int playCount();
    bool addPlay();
    
    const bool available();
    bool setAvailable(bool availability);
    
};


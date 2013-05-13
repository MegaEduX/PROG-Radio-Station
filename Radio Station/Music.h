//
//  Music.h
//  Created by Eduardo Almeida, Joao Almeida and Joao Ramos
//
//  This class manages a single song object and its data.
//

#ifndef MusicHeader
#define MusicHeader

#include <iostream>
#include <string>

class Music {
    
private:
    
	unsigned int _musicId;
    
    unsigned int _year;
    
    unsigned int _likes;
    unsigned int _dislikes;
    
    unsigned int _playCount;
    
    bool _available;

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

#endif
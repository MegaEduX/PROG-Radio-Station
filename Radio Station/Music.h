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

	std::string _title;
	std::string _artist;
	std::string _author;
	std::string _album;
	std::string _music_genre;
	
	unsigned int _year;
    
    unsigned int _likes;
    unsigned int _dislikes;
    
    unsigned int _playCount;
    
    bool _available;

public:
    
	// Doing this with constructors and deconstructors is much better as we can
	// automatically fill the song id by accessing the radio music database.
    
	Music(unsigned int musicId , unsigned int year , std::string title, std::string artist, std::string author, std::string album, std::string music_genre, unsigned int _likes , unsigned int _dislikes , unsigned int playCount, bool available); 
	// Adicionado por questoes obvias
	~Music();
    
    //
    // User variables.
    //
    
    bool setMusicId(unsigned int theId);
    const unsigned int musicId();
    
    bool setYear(unsigned int theYear);
    const unsigned int year();

	bool setTitle(std::string title);

	bool getTitle(unsigned int theId);
	
	bool setArtist(std::string artist);
    
	bool setAuthor(std::string author);
	
	bool setAlbum(std::string album);

	bool setMusicGenre(std::string music_genre);
    
	const unsigned int likes();
    const unsigned int dislikes();
    
    void addLike(); // Por razoes Obvias de bool para void
    void addDislike(); // Por razoes Obvias de bool para void
    
    const unsigned int playCount();
    void addPlay(); // Por razoes Obvias de bool para void
    
    const bool available();
    void setAvailable(bool availability); // Por razoes Obvias de bool para void
    
};

#endif
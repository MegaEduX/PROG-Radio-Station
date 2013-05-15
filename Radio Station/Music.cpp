//
//  User.cpp
//  Radio Station
//
//  Created by João Almeida on 13/05/13.
#include <ctime>

#include "Music.h"
#include "Playlist.h"
#include "RadioStation.h"

Music::Music() {
    _musicId = 0;
    _year = 0;
    _likes = 0;
    _dislikes = 0;
    _playCount = 0;
	_available = true;
}
Music::Music ( unsigned int musicId , unsigned int year , unsigned int likes , unsigned int dislikes , unsigned int playCount, bool available){
	_musicId = musicId;
	_year = year;
	_likes = likes;
	_dislikes = dislikes;
	_playCount = playCount;
	_available = available;
}
bool Music::setMusicId ( unsigned int TheId){
	if (TheId > RadioStation::Instance()->allTracks().count())
		return false;

	_musicId = TheId;
}
bool Music::setYear ( unsigned int TheYear) {
	if ( (TheYear-1970) * 60 * 60 * 24 * 365 > time(NULL))
		return false;

	_year = TheYear;
		return true;
}
void Music::addLike(){
	_likes ++;
}
void Music::addDislike(){
	_dislikes ++;
}
void Music::addPlay (){
	_playCount ++;
}
void Music::setAvailable( bool availability) {
	_available = availability;
}





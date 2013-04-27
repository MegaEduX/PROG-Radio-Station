#include <iostream>
#include <string>
#include <vector>
class User
{
private:
	std::string user_id;
	std::string user_name;
	std::string user_age;
	std::string user_gender;
	std::vector<std::string> user_playlist;

public:
	void addUser(); // Register User
	void addTrack(music *theTrack); // Adds a track to User Playlist
	void RemoveTrack(music *theTrack); // Remove a track from User Playlist
	std::vector<std::string> DisplayPlaylist(); // Display User Playlist


};


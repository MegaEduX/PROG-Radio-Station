#include <iostream>
#include <string>
#include <vector>

#include "Playlist.h"

typedef enum {
	kSexMale,
	kSexFemale
} kSex;

struct User
{
	unsigned int id;
	unsigned int age;

	kSex gender;

	std::string name;

	bool isAdministrator;
	
	Playlist userPlaylist; // This is the Top 10 playlist.
};

class UserManager {
private:
	UserManager(); // There can only be one user manager, so a singleton here is completely appropriate.

	UserManager(UserManager const&); // Copy constructor is private.
	UserManager& operator=(UserManager const&); // Assignment operator is private.

	static UserManager *um_pInstance;

	std::vector<User> userVector;

public:
	static UserManager* Instance();

	bool addUser(User aUser);

	bool removeUser(User aUser);
	bool removeUser(int userId);
};
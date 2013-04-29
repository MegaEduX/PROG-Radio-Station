#include <iostream>
#include <string>
#include <vector>

class Playlist;

typedef enum {
	kSexMale,
	kSexFemale
} kSex;

class User {
    
private:
    
	unsigned int userId;
	unsigned int age;
    
	kSex gender;
    
	std::string name;
    
	bool isAdministrator;
	
	Playlist userPlaylist;
    
public:
    
    User();
    ~User();
    
    bool setUserId(unsigned int theId);
    const unsigned int userId();
    
    bool setGender(kSex theGender);
    const kSex gender();
    
    bool setName(std::string theName);
    const std::string name();
    
    bool setAsAdmin(bool isAdmin);
    const bool isAdmin();
    
    bool setPlaylist(Playlist thePlaylist);
    const Playlist playlist();
    
};

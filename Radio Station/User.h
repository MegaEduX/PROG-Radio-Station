//
//  User.h
//  Created by Eduardo Almeida, Joao Almeida and Joao Ramos
//
//  This class takes care of the User objects and their information.
//

#ifndef UserHeader
#define UserHeader

#include <iostream>
#include <string>
#include <vector>

#include "Playlist.h"

typedef enum {
	kSexMale,
	kSexFemale
} kSex;

class User {
    
private:
    
	unsigned int _userId;
	unsigned int _age;
    
	kSex _gender;
    
	std::string _name;
    
	bool _isAdministrator;
	
	Playlist _userPlaylist;
    
    int _trackHits;
    
public:
    
    User(int userId, int age, kSex gender, std::string name, Playlist playlist);
    
    ~User();
    
    bool setUserId(unsigned int theId);
    const unsigned int userId();
    
    bool setAge(unsigned int theAge);
    const unsigned int age();
    
    bool setGender(kSex theGender);
    const kSex gender();
    
    bool setName(std::string theName);
    const std::string name();
    
    // bool setAsAdmin(bool isAdmin); -> This is useless. Sincerly, me.
    const bool isAdmin();
    
    bool setPlaylist(Playlist thePlaylist);
    const Playlist playlist();
    
    void trackPlayed();
    
};

#endif
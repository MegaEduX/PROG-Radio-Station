//
//  User.cpp
//  Radio Station
//
//  Created by Eduardo Almeida on 13/05/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#include "User.h"

#include "UserManager.h"

User::User() {
    _userId = UserManager::Instance() -> userCount();
    _age = 0;
    _gender = kSexMale;
    _name = "";
    _userPlaylist = Playlist();
    
    if (!_userId) // If user id == 0
        _isAdministrator = false;
}

User::User(int userId, int age, kSex gender, std::string name, Playlist playlist) {
    _userId = userId;
    _age = age;
    _gender = gender;
    _name = name;
    _userPlaylist = playlist;
    
    if (!_userId) // If user id == 0
        _isAdministrator = true;
}

bool User::setUserId(unsigned int theId) {
    if (theId > UserManager::Instance() -> userCount())
        return false;
    
    _userId = theId;
    
    if (!_userId)
        _isAdministrator = true;
    
    return true;
}

const unsigned int User::userId() {
    return _userId;
}

bool User::setGender(kSex theGender) {
    if (theGender != kSexMale && theGender != kSexMale)
        return false;
    
    _gender = theGender;
    
    return true;
}

const kSex User::gender() {
    return _gender;
}

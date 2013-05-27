//
//  UserManager.cpp
//  Radio Station
//
//  Created by Eduardo Almeida on 19/05/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#include "UserManager.h"

#include "FilesIO.h"

UserManager *UserManager::um_pInstance = NULL;

UserManager* UserManager::Instance() {
    if (!um_pInstance)
        um_pInstance = new UserManager;
    
    return um_pInstance;
}

UserManager::UserManager() {
    
}

bool UserManager::addUser(User *aUser) {
    for (int i = 0; i < _userVector.size(); i++)
        if (_userVector[i] -> getId() == aUser -> getId())
            return false;
    
    _userVector.push_back(aUser);
    
    FilesIO::Instance() -> saveUser(aUser);
    
    return true;
}

bool UserManager::removeUser(User *aUser) {
    for (int i = 0; i < _userVector.size(); i++)
        if (_userVector[i] -> getId() == aUser -> getId()) {
            _userVector.erase(_userVector.begin() + i);
            
            return true;
        }
    
    return false;
}

bool UserManager::removeUser(int userId) {
    for (int i = 0; i < _userVector.size(); i++)
        if (_userVector[i] -> getId() == userId) {
            _userVector.erase(_userVector.begin() + i);
            
            return true;
        }
    
    return false;
}

void UserManager::removeAllUsers() {
    _userVector.clear();
}

User* UserManager::getUser(int userId) {
    for (int i = 0; i < _userVector.size(); i++)
        if (_userVector[i] -> getId() == userId)
            return _userVector[i];
    
    return NULL;
}

User* UserManager::getUser(std::string userName) {
    for (int i = 0; i < _userVector.size(); i++)
        if (!(_userVector[i] -> getName().compare(userName)))
            return _userVector[i];
    
    return NULL;
}

User* UserManager::getPrizeWinner() {
    User *currentWinner = NULL;
    int currentCount = 0;
    
    for (int i = 0; i < _userVector.size(); i++) {
        std::vector<Music *> songVec = _userVector[i] -> getPlaylist() -> getAllTracks();
        
        int userCount = 0;
        
        for (int j = 0; j < songVec.size(); j++)
            userCount += songVec[i] -> getPlayCount();
        
        if (userCount > currentCount) {
            currentWinner = _userVector[i];
            currentCount = userCount;
        }
    }
    
    return currentWinner;
}

const unsigned int UserManager::userCount() {
    return (const unsigned int) _userVector.size();
}

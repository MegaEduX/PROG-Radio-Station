//
//  UserManager.cpp
//  Radio Station
//
//  Created by Eduardo Almeida on 19/05/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#include "UserManager.h"

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
        if (_userVector[i] -> userId() == aUser -> userId())
            return false;
    
    _userVector.push_back(aUser);
    
    return true;
}

bool UserManager::removeUser(User *aUser) {
    for (int i = 0; i < _userVector.size(); i++)
        if (_userVector[i] -> userId() == aUser -> userId()) {
            _userVector.erase(_userVector.begin() + i);
            
            return true;
        }
    
    return false;
}

bool UserManager::removeUser(int userId) {
    for (int i = 0; i < _userVector.size(); i++)
        if (_userVector[i] -> userId() == userId) {
            _userVector.erase(_userVector.begin() + i);
            
            return true;
        }
    
    return false;
}

User* UserManager::getUser(int userId) {
    for (int i = 0; i < _userVector.size(); i++)
        if (_userVector[i] -> userId() == userId)
            return _userVector[i];
    
    return NULL;
}

User* UserManager::getUser(std::string userName) {
    for (int i = 0; i < _userVector.size(); i++)
        if (!(_userVector[i] -> name().compare(userName)))
            return _userVector[i];
    
    return NULL;
}

const unsigned int UserManager::userCount() {
    return (const unsigned int) _userVector.size();
}

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
    
}

bool UserManager::removeUser(User *aUser) {
    
}

bool UserManager::removeUser(int userId) {
    
}

User* UserManager::getUser(int userId) {
    
}

User* UserManager::getUser(std::string userName) {
    
}

const unsigned int UserManager::userCount() {
    
}
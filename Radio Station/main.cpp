//
//  main.cpp
//  Radio Station
//
//  Created by Eduardo Almeida on 13/05/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#include <iostream>
#include <string>
#include <ctype.h>

#include "UserManager.h"
#include "User.h"

#include "RadioStation.h"

#include "Playlist.h"

void start();

void login(){
	User *theUser = NULL;

    do {
        std::string username;
        
        std::cout << "Enter ID or Username: ";
        std::cin >> username;
        
        if (!username.compare("-1")) {
            std::cout << "Operation Canceled." << std::endl << std::endl;
            start();
        }
        
        if (atoi(username.c_str()))
            theUser = UserManager::Instance()->getUser(atoi(username.c_str()));
        else
            theUser = UserManager::Instance()->getUser(username);
        
        if (!theUser)
            std::cout << "ID/Username not found! Try again! You may also cancel with '-1'." << std::endl;
        
        
    } while (!theUser);
}
		
void newUser() {
	int age = 0;
    
	std::string name;
    std::string username;
    
    char sex;

    std::cout << "Username: ";
    std::cin >> username;
    
    std::cout << std::endl;
    
    do {
        std::cout << "Age: ";
		std::cin >> age;
        
		std::cout << std::endl;
    } while (!age);
    
    do {
		std::cout << "Gender(M/F): ";
		std::cin >> sex;
        
		std::cout << std::endl;
		
        sex = toupper(sex);
		
    } while (!(sex == 'M' || sex == 'F'));
    
    do {
		std::cout << "Full Name: ";
		
        std::cin >> name;
        
		std::cout << std::endl;
    } while (atoi(name.c_str()));
    
    Playlist newPlaylist;
    
    User *theUser = new User(UserManager::Instance()->userCount(), age, (sex == 'F' ? kSexFemale : kSexMale), name, newPlaylist);
    
    if (UserManager::Instance() -> addUser(theUser))
        std::cout << "You were registeried. You may now login!" << std::endl << std::endl;
    else
        std::cout << "There was a problem. Please try again." << std::endl << std::endl;
}

void start() {
	int opc = 0;
	
	std::string username;

	std::cout << "Welcome to " << (RadioStation::Instance() -> name().compare("") != 0 ? RadioStation::Instance() -> name() : "our radio station!") << std::endl << std::endl;
    
	std::cout << "1. Existing Users: Login!" << std::endl;
	std::cout << "2. New Users: Register!" << std::endl;
    
    std::cout << std::endl;
    
    std::cout << "Press any other key to quit." << std::endl;
    
    std::cout << std::endl;
    
    std::cout << "Select an Option: ";
	std::cin >> opc;

	switch (opc) {

        case 1:
            
            login();
			
            break;
            
        case 2:
            
            newUser();
            
            break;
            
        default:
            
            exit(0);
            
            break;
	}

}

int main() {
	start();

	return 0;
}

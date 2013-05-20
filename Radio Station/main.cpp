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

#ifdef WIN32
#include <conio.h>
#endif

#include "UserManager.h"
#include "User.h"

#include "RadioStation.h"

#include "Playlist.h"
#include "Additions.h"

//
// Function Definitions
//

void start();
void login();
void newUser();

//
// Code Start
//

void login() {
	User *theUser = NULL;

    do {
        std::string username;
        
        std::cout << "Enter ID or Name: ";
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
            std::cout << "ID/Name not found! Try again! You may also cancel with '-1'." << std::endl;
        else
            std::cout << "You are now logged-in as " << theUser -> getName() << std::endl;
        
        
    } while (!theUser);
}
		
void newUser() {
	int age = 0;
    
	std::string name;
    //std::string username;
    std::string sex;
    
    do {
		std::cout << "Name: ";
		
        std::cin >> name;
        
		std::cout << std::endl;
    } while (atoi(name.c_str()));

    /*std::cout << "Username: ";
    std::cin >> username;
    
    std::cout << std::endl;*/
    
    do {
        std::cout << "Age: ";
		std::cin >> age;
        
		std::cout << std::endl;
    } while (!age);
    
    do {
		std::cout << "Gender(M/F): ";
		std::cin >> sex;
		
		std::cout << std::endl;
		
        sex[0] = toupper(sex[0]);

	} while ( sex.size() > 1 );

	char sexChar = sex[0];
    
    
    
    Playlist newPlaylist;
    
    User *theUser = new User(UserManager::Instance()->userCount(), age, (sexChar == 'F' ? kSexFemale : kSexMale), name, newPlaylist);
    
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
    
    std::cout << "Press the zero key to quit." << std::endl;
    
    std::cout << std::endl;
    
    std::cout << "Please Select an Option." << std::endl << std::endl;
    
	opc = getch();
    
	switch (opc) {

        case 49:
            
            login();
			
            break;
            
        case 50:
            
            newUser();
            
            Additions::clearConsole();
            
            start();
            
            break;

		case 48:

			std::cout << std::endl << "© 2013 MIEIC 2012/2013 - T3G12 (PROG)" << std::endl << "Thanks for using this program. Please come back soon!";
            
            exit(0);
            
            break;

			            
        default:
            
           Additions::clearConsole();
            
           start();
            
           break;
	}

}

int main() {
	start();

	return 0;
}

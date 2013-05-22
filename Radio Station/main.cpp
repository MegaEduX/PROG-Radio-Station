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
#include "FilesIO.h"
#include "RadioStation.h"
#include "Playlist.h"

#include "Additions.h"

//
// Instance Variables
//

static const int baseASCIINumber = 48;

User *loggedInUser = NULL;

//
// Function Definitions
//

void start();
void login();
void newUser();
void adminPanel();
void loggedInMenu();

//
// Code Start
//

void adminPanel() {


}

void loggedInMenu() {
    std::cout << "Welcome to " << (RadioStation::Instance()->name().compare("") ? "the radio station" : RadioStation::Instance()->name()) << "!" << std::endl << std::endl;
    
    std::cout << "1. Top 10 Songs" << std::endl;
    std::cout << "2. Search our Music Library" << std::endl;
    std::cout << "3. Manage your Personal Playlist" << std::endl;
    if (loggedInUser -> isAdmin())  std::cout << "4. Administration Panel" << std::endl;
    std::cout << std::endl;
    std::cout << "0. Log Out" << std::endl;
    std::cout << std::endl;
    std::cout << "Please choose an option.";
    
    while (true) {
        int opc = getch();
        
        switch (opc) {
                
            case (baseASCIINumber + 1):
                
                Additions::clearConsole();
                
                // Jump to Top 10
                
                break;
                
            case (baseASCIINumber + 2):
                
                Additions::clearConsole();
                
                // Jump to Library
                
                break;
                
            case (baseASCIINumber + 3):
                
                Additions::clearConsole();
                
                // Jump to Playlist
                
                break;
                
            case (baseASCIINumber + 4):
                
                if (loggedInUser -> isAdmin()) {
                    // Jump to Admin Panel
                }
                
                break;
                
            case baseASCIINumber:
                
                Additions::clearConsole();
                
                loggedInUser = NULL;
                
                start();
                
                break;
                
            default:
                
                break;
        }
    }
}

void login() {
	User *theUser = NULL;
    
    FilesIO::Instance() -> loadAllUsers();
    
    do {
        std::string username;
        
        std::cout << "Enter ID or Name: ";
        std::cin >> username;
        
        if (!username.compare("-1")) {
            std::cout << "Operation Canceled." << std::endl << std::endl;
            
            Additions::clearConsole();
            
            start();
        }
        
        if (atoi(username.c_str()))
            theUser = UserManager::Instance()->getUser(atoi(username.c_str()));
        else
            theUser = UserManager::Instance()->getUser(username);
        
        if (!theUser)
            std::cout << "ID/Name not found! Try again! You may also cancel with '-1'." << std::endl;
        else {
            std::cout << "You are now logged-in with name " << theUser -> getName() << " and ID " << theUser->getId() << "." << std::endl;
        }
    } while (!theUser);
    
    loggedInUser = theUser;
    
    Additions::clearConsole();
    
    loggedInMenu();
}
		
void newUser() {
	int age = 0;
    
	std::string name;
    std::string age_str;
    std::string sex;
    
    do {
		std::cout << "Name: ";
		
        std::cin >> name;
        
		std::cout << std::endl;
    } while (atoi(name.c_str()));
    
    do {
        std::cout << "Age: ";
		std::cin >> age_str;
        
        if (atoi(age_str.c_str()))
            age = atoi(age_str.c_str());
        
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
        std::cout << "You were registered. You may now login!" << std::endl << "Press any key to go back to the main menu." << std::endl;
    else
        std::cout << "There was a problem. Please try again." << std::endl << "Press any key to go back to the main menu." << std::endl;
    
    getch(); // Clean the keyboard buffer from the "Return" above.
    
    waitForReturn();
    
    Additions::clearConsole();
}

void start() {
	std::cout << "Welcome to " << (RadioStation::Instance() -> name().compare("") != 0 ? RadioStation::Instance() -> name() : "our radio station!") << std::endl << std::endl;
    
	std::cout << "1. Existing Users: Login!" << std::endl;
	std::cout << "2. New Users: Register!" << std::endl;
    
    std::cout << std::endl;
    
    std::cout << "Press the zero key to quit." << std::endl;
    
    std::cout << std::endl;
    
    std::cout << "Please Select an Option." << std::endl << std::endl;
    
    while (true) {
        int opc = getch();
        
        switch (opc) {
                
            case (baseASCIINumber + 1):
                
                Additions::clearConsole();
                
                login();
                
                break;
                
            case (baseASCIINumber + 2):
                
                Additions::clearConsole();
                
                newUser();
                
                start();
                
                break;
                
            case baseASCIINumber:
                
                Additions::clearConsole();
                
                std::cout << std::endl << "© 2013 MIEIC 2012/2013 - T3G12 (PROG)" << std::endl << "Thanks for using this program. Please come back soon!";
                
                exit(0);
                
                break;
                
                
            default:
                
                break;
        }
    }
}

int main() {
	start();

	return 0;
}

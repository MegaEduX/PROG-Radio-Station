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
#include "Music.h"

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
void addMusic();
void adminPanel();
void loggedInMenu();
void editMusicMenu();
void editMusic(Music *theMusic);
void musicManager();

//
// Code Start
//

void editMusic(Music *theMusic) {
    std::cout << "Music Manager :: Editing Song " << theMusic -> getId() << std::endl << std::endl;
    
	std::cout << "Song Title [" << theMusic->getTitle() << "]: ";

	std::string newTitle = Additions::getline();
    
    if (Additions::gotESC(newTitle)) {
        std::cout << std::endl << std::endl << "The operation was canceled. Press Return to continue.";
        
        Additions::waitForReturn();
        Additions::clearConsole();
        
        editMusicMenu();
    }

	if (newTitle.compare(""))
		theMusic -> setTitle(newTitle); //changes title

	std::cout << std::endl;
    
	std::cout << "Song Album [" << theMusic->getAlbum() << "]: ";

	std::string newAlbum = Additions::getline();
    
    if (Additions::gotESC(newAlbum)) {
        std::cout << std::endl << std::endl << "The operation was canceled. Press Return to continue.";
        
        Additions::waitForReturn();
        Additions::clearConsole();
        
        editMusicMenu();
    }

	if (newAlbum.compare(""))
		theMusic -> setAlbum(newAlbum); //changes Album

	std::cout << std::endl;

	std::cout << "Song Artist [" << theMusic->getArtist() << "]: ";

	std::string newArtist = Additions::getline();
    
    if (Additions::gotESC(newArtist)) {
        std::cout << std::endl << std::endl << "The operation was canceled. Press Return to continue.";
        
        Additions::waitForReturn();
        Additions::clearConsole();
        
        editMusicMenu();
    }

	if (newArtist.compare(""))
		theMusic -> setArtist(newArtist); //changes Artist

	std::cout << std::endl;

    std::string newYear;
    
	do {
        
        std::cout << "Song Year [" << theMusic->getYear() << "]: ";

		newYear = Additions::getline();
        
        if (Additions::gotESC(newYear))
            editMusicMenu();
    
		if (newYear.compare("")) {
			if (atoi(newYear.c_str())) {
				theMusic -> setYear (atoi(newYear.c_str()));
                
                break;
            }
        } else
            break;
        
	} while (!atoi(newYear.c_str()));
    
	std::cout << std::endl;

	std::cout << "Song Genre [" << theMusic->getGenre() << "]: ";

	std::string newGenre = Additions::getline();
    
    if (Additions::gotESC(newGenre)) {
        std::cout << std::endl << std::endl << "The operation was canceled. Press Return to continue.";
        
        Additions::waitForReturn();
        Additions::clearConsole();
        
        editMusicMenu();
    }

	if (newGenre.compare(""))
		theMusic -> setGenre(newGenre); //changes Genre

	std::cout << std::endl << std::endl << "Done! Please press Return to go back.";
    
    Additions::waitForReturn();
    Additions::clearConsole();
    
    FilesIO::Instance() -> saveAllSongs();
    
    editMusicMenu();
}

void editMusicMenu() {
    std::cout << "Music Manager :: Edit Music" << std::endl;
    
    std::cout << std::endl;
    
    Playlist *allTracks = RadioStation::Instance() -> allTracks();
    
    std::vector<Music *> allTracksVec = allTracks -> getAllTracks();
    
    if (allTracksVec.size() == 0) {
        std::cout << "There are currently no tracks! Please press Return to go back.";
        
        Additions::waitForReturn();
        Additions::clearConsole();
        musicManager();
    }
        
    for (int i = 0 ; i < allTracksVec.size() ; i++)
        std::cout << "[" << i << "] " << allTracksVec[i]->getTitle() << " by " << allTracksVec[i]->getArtist() << " - " << (allTracksVec[i]->getAvailable() ? "(Available)" : "(Unavailable)") <<  std::endl;
    
    while (true) {
        std::cout << std::endl;
        
        std::cout << "Choose the music track you want to make changes to: ";
        
        std::string songIdStr = Additions::getline();
        
        if (Additions::gotESC(songIdStr)) {
            std::cout << std::endl << std::endl << "The operation was canceled. Press Return to continue.";
            
            Additions::waitForReturn();
            Additions::clearConsole();
            
            musicManager();
        }
        
        int songId = atoi(songIdStr.c_str());
        
        while (!(RadioStation::Instance()->allTracks()->count() > songId)) {
            std::cout << std::endl << "Invalid track. Please type another id: ";
            
            songIdStr = Additions::getline();
            
            if (Additions::gotESC(songIdStr)) {
                std::cout << std::endl << std::endl << "The operation was canceled. Press Return to continue.";
                
                Additions::waitForReturn();
                Additions::clearConsole();
                
                musicManager();
            }
            
            songId = atoi(songIdStr.c_str());
        }
        
        if (songId == -1) {
            Additions::clearConsole();
            adminPanel();
            break;
        } else {
            Additions::clearConsole();
            
            editMusic(allTracksVec[songId]);
        }
    }
}

void musicManager() {
    std::cout << "Music Manager :: Administrative Panel" << std::endl;
    std::cout << std::endl;
    std::cout << "1. Add New Song" << std::endl;
    std::cout << "2. Modify Existing Song" << std::endl;
    std::cout << std::endl;
    std::cout << "0. Go Back" << std::endl;
    std::cout << std::endl;
    std::cout << "Please choose an option.";
    
    while (true) {
        
        int opc = getch();
        
        switch (opc) {
            case (baseASCIINumber + 1):
                
                Additions::clearConsole();
                
                addMusic();
                
                break;
                
            case (baseASCIINumber + 2):
                
                Additions::clearConsole();
                
                editMusicMenu();
                
                break;
                
            case baseASCIINumber:
                
                Additions::clearConsole();
                
                adminPanel();
                
                break;
                
            default:
                
                break;
        }
        
    }
}

void addMusic() {
    std::cout << "Music Manager :: New Music" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Title: ";
    
    std::string title = Additions::getline();
    
    if (Additions::gotESC(title)) {
        std::cout << std::endl << std::endl << "The operation was canceled. Press Return to continue.";
        
        Additions::waitForReturn();
        Additions::clearConsole();
        
        editMusicMenu();
    }
    
    std::cout << std::endl;
    
    std::cout << "Artist: ";
    
    std::string artist = Additions::getline();
    
    if (Additions::gotESC(artist)) {
        std::cout << std::endl << std::endl << "The operation was canceled. Press Return to continue.";
        
        Additions::waitForReturn();
        Additions::clearConsole();
        
        editMusicMenu();
    }
    
    std::cout << std::endl;
    
    std::cout << "Author: ";
    
    std::string author = Additions::getline();
    
    if (Additions::gotESC(author)) {
        std::cout << std::endl << std::endl << "The operation was canceled. Press Return to continue.";
        
        Additions::waitForReturn();
        Additions::clearConsole();
        
        editMusicMenu();
    }
    
    std::cout << std::endl;
    
    std::cout << "Album: ";
    
    std::string album = Additions::getline();
    
    if (Additions::gotESC(album)) {
        std::cout << std::endl << std::endl << "The operation was canceled. Press Return to continue.";
        
        Additions::waitForReturn();
        Additions::clearConsole();
        
        editMusicMenu();
    }
    
    std::cout << std::endl;
    
    std::cout << "Genre: ";
    
    std::string genre = Additions::getline();
    
    if (Additions::gotESC(genre)) {
        std::cout << std::endl << std::endl << "The operation was canceled. Press Return to continue.";
        
        Additions::waitForReturn();
        Additions::clearConsole();
        
        editMusicMenu();
    }
    
    int year = 0;
    
    while (!year) {
        std::cout << std::endl;
        
        std::cout << "Year: ";
        
        std::string yearStr = Additions::getline();
        
        if (Additions::gotESC(yearStr)) {
            std::cout << std::endl << std::endl << "The operation was canceled. Press Return to continue.";
            
            Additions::waitForReturn();
            Additions::clearConsole();
            
            editMusicMenu();
        }
        
        if (atoi(yearStr.c_str()) > 0)
            year = atoi(yearStr.c_str());
    }
    
    bool available = false;
    
    std::cout << std::endl;
    
    std::cout << "Available? (y/n): ";
    
    while (true) {
        int ch = getch();
        
        bool shouldBreak = false;
        
        switch (ch) {
            case 121:   // y
            case 89:    // Y
                
                available = true;
                
                shouldBreak = true;
                
                break;
                
            case 110:   // n
            case 78:    // N
                
                available = false;
                
                shouldBreak = true;
                
                break;
                
            case 27:    // esc
                
                std::cout << std::endl << std::endl << "The operation was canceled. Press Return to continue.";
                
                Additions::waitForReturn();
                Additions::clearConsole();
                
                editMusicMenu();
                
                break;
                
            default:
                
                break;
        }
        
        if (shouldBreak) {
            std::cout << (char) ch;
            break;
        }
    }
    
    std::cout << std::endl << std::endl;
    
    Music *newMusic = new Music(RadioStation::Instance()->allTracks()->count(), year, title, artist, author, album, genre, 0, 0, 0, available);
    
    if (RadioStation::Instance()->allTracks()->addSong(newMusic))
        std::cout << "The track was successfully added!";
    else
        std::cout << "There was an error adding your track.";
    
    FilesIO::Instance() -> saveAllSongs();
    
    std::cout << " Please press return to continue.";
    
    Additions::waitForReturn();
    
    Additions::clearConsole();
    
    musicManager();
}

void reinitializeSet() {
    std::cout << "Radio Station :: Set Control Panel" << std::endl << std::endl;
    
    std::cout << "Are you sure you want to reinitialize the station set? (y/n): ";
    
    bool reinitialize = false;
    
    while (true) {
        int ch = getch();
        
        bool shouldBreak = false;
        
        switch (ch) {
            case 121:   // y
            case 89:    // Y
                
                reinitialize = true;
                
                shouldBreak = true;
                
                break;
                
            case 110:   // n
            case 78:    // N
                
                reinitialize = false;
                
                shouldBreak = true;
                
                break;
                
            case 27:    // esc
                
                std::cout << std::endl << std::endl << "The operation was canceled. Press Return to continue.";
                
                Additions::waitForReturn();
                Additions::clearConsole();
                
                adminPanel();
                
                break;
                
            default:
                
                break;
        }
        
        if (shouldBreak) {
            std::cout << (char) ch;
            break;
        }
    }
    
    std::cout << std::endl << std::endl;
    
    if (reinitialize) {
        RadioStation::Instance() -> generateSet();
        
        std::cout << "The set was reinitialized! ";
    } else
        std::cout << "The set wasn't reinitialized. ";
    
    std::cout << "Please press Return to continue.";
    
    Additions::waitForReturn();
    Additions::clearConsole();
    
    adminPanel();
}

void changeName() {
    std::cout << "Radio Station :: Name Changer" << std::endl << std::endl;
    
    std::cout << "Current Name: " << (RadioStation::Instance() -> name().compare("") ? RadioStation::Instance() -> name() : "None!") << std::endl;
    std::cout << "New Name (press ESC to cancel): ";
    
    std::string newName = Additions::getline();
    
    if (Additions::gotESC(newName)) {
        std::cout << std::endl << std::endl << "The operation was canceled. Press Return to continue.";
        
        Additions::waitForReturn();
        Additions::clearConsole();
        
        adminPanel();
    }
    
    RadioStation::Instance() -> setName(newName);
    
    FilesIO::Instance() -> storeGlobals();
    
    std::cout << std::endl << std::endl;
    
    if (!newName.compare("")) {
        std::cout << "The name has been deleted.";
    } else
        std::cout << "The Radio Station is now called " << RadioStation::Instance() -> name();
    
    std::cout << std::endl << std::endl << "Please press Return to proceed.";
    
    Additions::waitForReturn();
    Additions::clearConsole();
    
    adminPanel();
}

void adminPanel() {
    std::cout << "Welcome to the administrative panel!" << std::endl << std::endl;
    
    std::cout << "1. Manage the Music Library" << std::endl;
    std::cout << "2. Reinitialize the Set" << std::endl;
    std::cout << "3. Change the Radio Station Name" << std::endl;
    std::cout << std::endl;
    std::cout << "0. Go Back" << std::endl;
    std::cout << std::endl;
    std::cout << "Please choose an option.";
    
    while (true) {
		
		int opc = getch();
        
        switch (opc) {
                
            case (baseASCIINumber + 1):
                
                Additions::clearConsole();
                
                musicManager();
                
                break;
                
            case (baseASCIINumber + 2):
                
                Additions::clearConsole();
                
                reinitializeSet();
                
                break;
                
            case (baseASCIINumber + 3):
                
                Additions::clearConsole();
                
                changeName();
                
                break;
                
            case baseASCIINumber:
                
                Additions::clearConsole();
                
                loggedInMenu();
                
                break;
                
            default:
                
                break;
        }
    }
}

void searchLibrary() {
    bool name = false, artist = false, author = false, album = false, genre = false;
    
    while (true) {
        std::cout << "Radio Station :: Library Search" << std::endl << std::endl;
        
        std::cout << "Search by..." << std::endl;
        std::cout << (name ? " - 1. Name (Selected)" : " - 1. Name") << std::endl;
        std::cout << (artist ? " - 2. Artist (Selected)" : " - 2. Artist") << std::endl;
        std::cout << (author ? " - 3. Author (Selected)" : " - 3. Author") << std::endl;
        std::cout << (album ? " - 4. Album (Selected)" : " - 4. Album") << std::endl;
        std::cout << (genre ? " - 5. Genre (Selected)" : " - 5. Genre") << std::endl;
        std::cout << " - 9. Next Step" << std::endl;
        std::cout << " - 0. Go Back" << std::endl;
        
        int ch = getch();
        
        switch (ch) {
            case (baseASCIINumber + 1):
            
                name = (name ? false : true);
            
                break;
            
            case (baseASCIINumber + 2):
            
                artist = (artist ? false : true);
                
                break;
                
            case (baseASCIINumber + 3):
                
                author = (author ? false : true);
                
                break;
                
            case (baseASCIINumber + 4):
                
                album = (album ? false : true);
                
                break;
                
            case (baseASCIINumber + 5):
                
                genre = (genre ? false : true);
                
                break;
                
            case (baseASCIINumber + 9):
                
                // Jump to next step;
                
                break;
                
            case baseASCIINumber:
                
                // Go back
                
                break;
            
            default:
                
                break;
        }
        
        Additions::clearConsole();
    }
    
}

void loggedInMenu() {
    std::cout << "Welcome to " << (!RadioStation::Instance()->name().compare("") ? "the radio station" : RadioStation::Instance()->name()) << ", " << loggedInUser -> getName() << "!" << std::endl << std::endl;
    
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
                
                searchLibrary();
                
                // Jump to Library
                
                break;
                
            case (baseASCIINumber + 3):
                
                Additions::clearConsole();
                
                // Jump to Playlist
                
                break;
                
            case (baseASCIINumber + 4):
                
                if (loggedInUser -> isAdmin()) {
                    Additions::clearConsole();
                    
                    adminPanel();
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
    
    std::cout << "Radio Station :: Login" << std::endl << std::endl;
    
    do {
        std::cout << "Enter ID or Name: ";
        
        std::string username = Additions::getline();
        
        if (Additions::gotESC(username)) {
            std::cout << std::endl << std::endl << "The operation was canceled. Press Return to continue.";
            
            Additions::waitForReturn();
            Additions::clearConsole();
            
            start();
        }
        
        if (atoi(username.c_str()))
            theUser = UserManager::Instance()->getUser(atoi(username.c_str()));
        else
            theUser = UserManager::Instance()->getUser(username);
        
        std::cout << std::endl;
        
        if (!theUser)
            std::cout << "ID/Name not found! Please try again!" << std::endl;
        else
            std::cout << "You are now logged-in with name " << theUser -> getName() << " and ID " << theUser->getId() << "." << std::endl;
    } while (!theUser);
    
    loggedInUser = theUser;
    
    Additions::clearConsole();
    
    loggedInMenu();
}
		
void newUser() {
    std::cout << "Radio Station :: New User" << std::endl << std::endl;
    
    if (UserManager::Instance() -> userCount() == 0)
        std::cout << "There are currently no registeried users. This will be the admin user." << std::endl << std::endl;
    
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
    
    std::cout << "Gender(M/F): ";
    
    while (true) {
        int ch = getch();
        
        bool shouldBreak = false;
        
        switch (ch) {
            case 109:   // m
            case 77:    // M
                
                sex = "M";
                
                shouldBreak = true;
                
                break;
                
            case 102:   // f
            case 70:    // F
                
                sex = "F";
                
                shouldBreak = true;
                
            default:
                
                break;
        }
        
        if (shouldBreak) {
            std::cout << (char) ch;
            break;
        }
    }
    
    std::cout << std::endl << std::endl;

	char sexChar = sex[0];
    
    Playlist newPlaylist;
    
    User *theUser = new User(UserManager::Instance()->userCount(), age, (sexChar == 'F' ? kSexFemale : kSexMale), name, newPlaylist);
    
    if (UserManager::Instance() -> addUser(theUser))
        std::cout << "You were registered. You may now login!" << std::endl << "Press any key to go back to the main menu." << std::endl;
    else
        std::cout << "There was a problem. Please try again." << std::endl << "Press any key to go back to the main menu." << std::endl;
    
    Additions::waitForReturn();
    
    Additions::clearConsole();
}

void start() {
	std::cout << "Welcome to " << (RadioStation::Instance() -> name().compare("") ? RadioStation::Instance() -> name() : "our radio station") << "!" << std::endl << std::endl;
    
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
    FilesIO::Instance() -> loadAllSongs();
    
    FilesIO::Instance() -> loadGlobals();
    
	start();

	return 0;
}

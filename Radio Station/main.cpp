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

static const int escKey = 27;

static const int returnKeyPOSIX = 13;
static const int returnKeyWindows = 10;

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
void userWorkWithSong(Music *theMusic);
void musicManager();
void searchLibraryStepTwo(bool name, bool artist, bool author, bool album, bool genre, bool year);
void PlaylistManager();

//
// Code Start
//

void editMusic(Music *theMusic) {
    std::cout << "Music Manager :: Editing Song " << theMusic -> getId() << std::endl << std::endl;
    
	std::cout << "Song Title [" << theMusic->getTitle() << "]: ";

	std::string newTitle = Additions::getline();
    
    if (Additions::gotESC(newTitle)) {
        Additions::clearConsole();
        
        editMusicMenu();
    }

	if (newTitle.compare(""))
		theMusic -> setTitle(newTitle); //changes title

	std::cout << std::endl;
    
	std::cout << "Song Album [" << theMusic->getAlbum() << "]: ";

	std::string newAlbum = Additions::getline();
    
    if (Additions::gotESC(newAlbum)) {
        Additions::clearConsole();
        
        editMusicMenu();
    }

	if (newAlbum.compare(""))
		theMusic -> setAlbum(newAlbum); //changes Album

	std::cout << std::endl;

	std::cout << "Song Artist [" << theMusic->getArtist() << "]: ";

	std::string newArtist = Additions::getline();
    
    if (Additions::gotESC(newArtist)) {
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
        
        if (Additions::gotESC(newYear)) {
            Additions::clearConsole();
            
            editMusicMenu();
        }
    
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
        Additions::clearConsole();
        
        editMusicMenu();
    }

	if (newGenre.compare(""))
		theMusic -> setGenre(newGenre); //changes Genre
    
    bool available = false;
    
    std::cout << std::endl;
    
    std::cout << "Available? " << (theMusic -> getAvailable() ? "[Y]" : "[N]") << " (y/n): ";
    
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
                
            case returnKeyPOSIX:    // Return (POSIX)
            case returnKeyWindows:    // Return (Windows)
                
                available = theMusic -> getAvailable();
                
                shouldBreak = true;
                
                break;
                
            case escKey:    // ESC
                
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
    
    theMusic -> setAvailable(available);

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
        
        if (Additions::gotESC(songIdStr))
            musicManager();
        
        int songId = atoi(songIdStr.c_str());
        
        while (!(RadioStation::Instance()->allTracks()->count() > songId)) {
            std::cout << std::endl << "Invalid track. Please type another id: ";
            
            songIdStr = Additions::getline();
            
            if (Additions::gotESC(songIdStr))
                musicManager();
            
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
                
            case escKey:
                
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
        Additions::clearConsole();
        
        editMusicMenu();
    }
    
    std::cout << std::endl;
    
    std::cout << "Artist: ";
    
    std::string artist = Additions::getline();
    
    if (Additions::gotESC(artist)) {
        Additions::clearConsole();
        
        editMusicMenu();
    }
    
    std::cout << std::endl;
    
    std::cout << "Author: ";
    
    std::string author = Additions::getline();
    
    if (Additions::gotESC(author)) {
        Additions::clearConsole();
        
        editMusicMenu();
    }
    
    std::cout << std::endl;
    
    std::cout << "Album: ";
    
    std::string album = Additions::getline();
    
    if (Additions::gotESC(album)) {
        Additions::clearConsole();
        
        editMusicMenu();
    }
    
    std::cout << std::endl;
    
    std::cout << "Genre: ";
    
    std::string genre = Additions::getline();
    
    if (Additions::gotESC(genre)) {
        Additions::clearConsole();
        
        editMusicMenu();
    }
    
    int year = 0;
    
    while (!year) {
        std::cout << std::endl;
        
        std::cout << "Year: ";
        
        std::string yearStr = Additions::getline();
        
        if (Additions::gotESC(yearStr)) {
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
                
            case escKey:    // esc
                
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
            case escKey:
                
                reinitialize = false;
                
                shouldBreak = true;
                
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
    std::cout << "New Name: ";
    
    std::string newName = Additions::getline();
    
    if (Additions::gotESC(newName)) {
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
                
            case escKey:
                
                Additions::clearConsole();
                
                loggedInMenu();
                
                break;
                
            default:
                
                break;
        }
    }
}

void searchLibrary() {
    bool name = false, artist = false, author = false, album = false, genre = false, year = false;
    
    while (true) {
        std::cout << "Radio Station :: Library Search :: (Step 1 of 2)" << std::endl << std::endl;
        
        std::cout << "Search by..." << std::endl;
        std::cout << (name ? " - 1. Name (Selected)" : " - 1. Name") << std::endl;
        std::cout << (artist ? " - 2. Artist (Selected)" : " - 2. Artist") << std::endl;
        std::cout << (author ? " - 3. Author (Selected)" : " - 3. Author") << std::endl;
        std::cout << (album ? " - 4. Album (Selected)" : " - 4. Album") << std::endl;
        std::cout << (genre ? " - 5. Genre (Selected)" : " - 5. Genre") << std::endl;
        std::cout << (year ? " - 6. Year (Selected)" : " - 6. Year") << std::endl;
        std::cout << std::endl;
        std::cout << std::endl << "Please choose a value option to select/unselect or return to proceed.";
        
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
                
            case (baseASCIINumber + 6):
                
                year = (year ? false : true);
                
                break;
                
            case returnKeyPOSIX: // Return (POSIX)
            case returnKeyWindows: // Return (Windows)
                
                Additions::clearConsole();
                
                searchLibraryStepTwo(name, artist, author, album, genre, year);
                
                break;
                
            case escKey: // ESC
                
                Additions::clearConsole();
                
                loggedInMenu();
                
                break;
            
            default:
                
                break;
        }
        
        Additions::clearConsole();
    }
}

void searchLibraryStepTwo(bool name, bool artist, bool author, bool album, bool genre, bool year) {
    std::cout << "Radio Station :: Library Search :: (Step 2 of 2)" << std::endl << std::endl;
    
    std::string nameStr, artistStr, authorStr, albumStr, genreStr;
    
    int yearInt = 0;
    
    if (name) {
        std::cout << "Name: ";
        
        nameStr = Additions::getline();
        
        std::cout << std::endl;
        
        if (Additions::gotESC(nameStr)) {
            Additions::clearConsole();
            
            loggedInMenu();
        }
    }
    
    if (artist) {
        std::cout << "Artist: ";
        
        artistStr = Additions::getline();
        
        std::cout << std::endl;
        
        if (Additions::gotESC(artistStr)) {
            Additions::clearConsole();
            
            loggedInMenu();
        }
    }
    
    if (author) {
        std::cout << "Author: ";
        
        authorStr = Additions::getline();
        
        std::cout << std::endl;
        
        if (Additions::gotESC(authorStr)) {
            Additions::clearConsole();
            
            loggedInMenu();
        }
    }
    
    if (album) {
        std::cout << "Album: ";
        
        albumStr = Additions::getline();
        
        std::cout << std::endl;
        
        if (Additions::gotESC(albumStr)) {
            Additions::clearConsole();
            
            loggedInMenu();
        }
    }
    
    if (genre) {
        std::cout << "Genre: ";
        
        genreStr = Additions::getline();
        
        std::cout << std::endl;
        
        if (Additions::gotESC(genreStr)) {
            Additions::clearConsole();
            
            loggedInMenu();
        }
    }
    
    if (year) {
        std::string yearStr;
        
        while (!atoi(yearStr.c_str())) {
            std::cout << "Year: ";
            
            yearStr = Additions::getline();
            
            if (Additions::gotESC(yearStr)) {
                Additions::clearConsole();
                
                loggedInMenu();
            }
            
            if (atoi(yearStr.c_str()))
                yearInt = atoi(yearStr.c_str());
            
            std::cout << std::endl;
        }
    }
    
    std::cout << std::endl << "Search Results:" << std::endl << std::endl;
    
    std::vector<Music *> searchResult = RadioStation::Instance() -> allTracks() -> search(-1, nameStr, artistStr, authorStr, albumStr, genreStr, (yearInt == 0 ? -1 : yearInt));
    
    for (int i = 0; i < searchResult.size(); i++) {
        std::cout << "[" << searchResult[i] -> getId() << "] " << searchResult[i] -> getTitle() << " by " << searchResult[i] -> getArtist() << " " << (searchResult[i] -> getAvailable() ? "(Available)" : "(Unavailable)") << std::endl;
    }
    
    std::cout << std::endl << "Type a song ID to select it: ";
    
    while (true) {
        std::string songIdStr = Additions::getline();
        
        std::cout << std::endl;
        
        if (Additions::gotESC(songIdStr)) {
            Additions::clearConsole();
            
            loggedInMenu();
        }
        
        int songId = atoi(songIdStr.c_str());
        
        bool found = false;
        
        for (int i = 0; i < searchResult.size(); i++) {
            if (searchResult[i] -> getId() == songId) {
                Additions::clearConsole();
                
                userWorkWithSong(searchResult[i]);
                
                found = true;
                
                break;
            }
        }
        
        if (found)
            break;
        
        std::cout << "Song not found. Please try again: ";
    }
}

void userWorkWithSong(Music *theMusic) {
    while (true) {
        std::cout << "Radio Station :: Song Details (" << theMusic -> getId() << ")" << std::endl << std::endl;
        
        std::vector<Music *> songSearch = loggedInUser -> getPlaylist() -> search(theMusic->getId(), "", "", "", "", "", -1);
        
        std::cout << "ID: " << theMusic -> getId() << std::endl;
        std::cout << "Title: " << theMusic -> getTitle() << std::endl;
        std::cout << "Artist: " << theMusic -> getArtist() << std::endl;
        std::cout << "Author: " << theMusic -> getAuthor() << std::endl;
        std::cout << "Album: " << theMusic -> getAlbum() << std::endl;
        std::cout << "Genre: " << theMusic -> getGenre() << std::endl;
        
        std::cout << std::endl;
        
        std::cout << "Likes: " << theMusic -> getLikes() << std::endl;
        std::cout << "Dislikes: " << theMusic -> getDislikes() << std::endl;
        
        std::cout << std::endl;
        
        std::cout << "Comulative Play Count: " << theMusic -> getPlayCount() << std::endl;
        
        std::cout << std::endl << std::endl;
        
        std::cout << "1. Like this track" << std::endl;
        std::cout << "2. Dislike this track" << std::endl;
        std::cout << "3. " << (songSearch.size() ? "Remove from" : "Add to") << " Playlist" << std::endl;
        
        std::cout << std::endl;
        
        std::cout << "Please choose your option.";
        
        int ch = getch();
        
        switch (ch) {
            case (baseASCIINumber + 1):
                
                theMusic -> addLike();
                
                FilesIO::Instance() -> saveAllSongs();
                
                break;
                
            case (baseASCIINumber + 2):
                
                theMusic -> addDislike();
                
                FilesIO::Instance() -> saveAllSongs();
                
                break;
                
            case (baseASCIINumber + 3):
                
                if (songSearch.size()) {
                    if (!loggedInUser -> getPlaylist() -> removeSong(theMusic)) {
                        std::cout << std::endl << std::endl << "An error has occoured. We could not remove the song from the playlist. Press Return to continue.";
                        
                        Additions::waitForReturn();
                    }
                } else {
                    if (!loggedInUser -> getPlaylist() -> addSong(theMusic)) {
                        std::cout << std::endl << std::endl << "An error has occoured. We could not add the song to the playlist. Press Return to continue.";
                        
                        Additions::waitForReturn();
                    }
                }
                
                FilesIO::Instance()->saveUser(loggedInUser);
                
                FilesIO::Instance()->storePlaylistForUser(loggedInUser->getId());
                
                break;
                
            case escKey: // ESC
                
                Additions::clearConsole();
                
                searchLibrary();
                
                break;
                
            default:
                
                break;
        }
        
        Additions::clearConsole();
    }
}

void PlaylistManager(){
	std::cout << "Playlist Manager" << std::endl;
    std::cout << std::endl;
    std::cout << "1. Add New Song" << std::endl;
    std::cout << "2. Delete Song" << std::endl;
	std::cout << "3. Display My Playlist" << std::endl;
    std::cout << std::endl;
    std::cout << "Please choose an option." ;

	Playlist *allTracks = RadioStation::Instance() -> allTracks();
	
	std::vector<Music *> allTracksVec = allTracks -> getAllTracks();


	while (true) {
        int opc = getch();
        
        switch (opc) {

			case baseASCIINumber:
                
                Additions::clearConsole();
                
                loggedInMenu();
                
                break;
                
            case (baseASCIINumber + 1): {
                
				Additions::clearConsole();
				
				if (allTracksVec.size() == 0) {
					std::cout << "There are currently no songs on the radio station. Please press Return to go back.";
                    Additions::waitForReturn();
					Additions::clearConsole();
					loggedInMenu();
				}
                
				for (int i = 0 ; i < allTracksVec.size() ; i++)
					std::cout << "[" << i << "] " << allTracksVec[i]->getTitle() << " by " << allTracksVec[i]->getArtist() <<  std::endl;
                
                std::cout << std::endl << "Please select the ID of the song you want to add to your Playlist" << std::endl;

				std::string songIdStr = Additions::getline();

				if (Additions::gotESC(songIdStr)) {
					std::cout << std::endl << std::endl << "The operation was canceled. Press Return to continue.";
            
					Additions::waitForReturn();
					Additions::clearConsole();
					start();
                }
                
                int songId = atoi(songIdStr.c_str());
                
                while (!(songId > RadioStation::Instance()->allTracks()->count() - 1 && songId < 0 ) && atoi(songIdStr.c_str())) {
                    std::cout << std::endl << "Invalid track. Please type another id: " << std::endl;
                    
                    songIdStr = Additions::getline();
                }
                
                loggedInUser->getPlaylist()->addSong(allTracksVec[songId]);
                
                std::cout << "Music ' " << allTracksVec[songId]->getTitle() << " ' has been sucessfuly added to your playlist" << std::endl;
                
                Additions::waitForReturn();
                Additions::clearConsole();
                PlaylistManager();
					
				break;
            }

				
            case (baseASCIINumber + 2):
                
                Additions::clearConsole();
                
                searchLibrary();
                
                // Jump to Library
                
                break;
                
            case (baseASCIINumber + 3):
                
                Additions::clearConsole();
                
                // Jump to Playlist
                
                break;
                
            case escKey:
                
                // Go back. ESC key pressed.
                
                break;
		}
    }
}

void loggedInMenu() {
    std::cout << "Welcome to " << (!RadioStation::Instance()->name().compare("") ? "the radio station" : RadioStation::Instance()->name()) << ", " << loggedInUser -> getName() << "!" << std::endl << std::endl;
    
    std::cout << "1. Top 10 Songs" << std::endl;
    std::cout << "2. Search our Music Library" << std::endl;
    std::cout << "3. Manage your Personal Playlist" << std::endl;
    if (loggedInUser -> isAdmin())  std::cout << "4. Administration Panel" << std::endl;
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
				PlaylistManager();
                
                // Jump to Playlist
                
                break;
                
            case (baseASCIINumber + 4):
                
                if (loggedInUser -> isAdmin()) {
                    Additions::clearConsole();
                    
                    adminPanel();
                }
                
                break;
                
            case escKey:
                
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
            Additions::clearConsole();
            
            start();
        }
        
        if (atoi(username.c_str()) || !username.compare("0")) // if (int)0, this would return false, so... yeah.
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
        std::cout << "There are currently no registered users. This will be the admin user." << std::endl << std::endl;
    
	int age = 0;
    
	std::string name;
    std::string age_str;
    std::string sex;
    
    do {
		std::cout << "Name: ";
        
        name = Additions::getline();
        
        if (Additions::gotESC(name)) {
            Additions::clearConsole();
            
            start();
        }
		
        std::cin >> name;
        
		std::cout << std::endl;
        
        if (UserManager::Instance() -> getUser(name)) {
            name = "1";
            
            std::cout << "An user with this name already exists. Please choose another name." << std::endl;
        }
    } while (atoi(name.c_str()));
    
    do {
        std::cout << "Age: ";
		
        age_str = Additions::getline();
        
        if (Additions::gotESC(age_str)) {
            Additions::clearConsole();
            
            start();
        }
        
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
                
            case escKey:
                
                Additions::clearConsole();
                
                start();
                
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

	char sexChar = sex[0];
    
    Playlist newPlaylist;
    
    User *theUser = new User(UserManager::Instance()->userCount(), age, (sexChar == 'F' ? kSexFemale : kSexMale), name, newPlaylist);
    
    if (UserManager::Instance() -> addUser(theUser))
        std::cout << "You are registered and may login now!" << std::endl << "Press any key to go back to the main menu." << std::endl;
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
    
    std::cout << "The ESC key can be pressed at any time to go to the previous menu (or, in this case, to terminate the program)." << std::endl;
    
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
                
            case escKey:
                
                Additions::clearConsole();
                
                std::cout << "Radio Station (1.0)" << std::endl << std::endl << "© 2013 MIEIC 2012/2013 - T3G12 (PROG)" << std::endl << std::endl << "Thanks for using this program. Please come back soon!";
                
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

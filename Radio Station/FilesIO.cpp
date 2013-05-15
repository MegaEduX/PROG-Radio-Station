//
//  FilesIO.cpp
//  Radio Station
//
//  Created by Eduardo Almeida on 13/05/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#include "FilesIO.h"
#include "RadioStation.h"
#include "UserManager.h"

#include "CSVParser.h"
#include "Additions.h"

static const std::string userBase = "playListUser";
static const std::string usersFile = "users.csv";
static const std::string globalsFile = "globals.csv";

FilesIO *FilesIO::fio_pInstance = NULL;

FilesIO* FilesIO::Instance() {
    if (!fio_pInstance)
        fio_pInstance = new FilesIO;
    
    return fio_pInstance;
}

//
// Globals File Format: (prone to change!)
// key,value
// name,the-name
//

bool FilesIO::loadGlobals() {
    CSVParser parser(globalsFile);
    
    std::vector<std::vector<std::string>> parsedCsv = parser.tableRows(true);
    
    if (parsedCsv.size() < 1)
        return false;
    
    RadioStation::Instance()->setName(parsedCsv[1][1]);
    
    return true;
}

bool FilesIO::storeGlobals() {
    
}

//
//  Users File Format: (prone to change!)
//
//  id,name,age,gender
//

User* FilesIO::loadUser(int userId) {
    CSVParser parser(usersFile);
    
    std::vector<std::vector<std::string>> parsedCsv = parser.tableRows(true);
    
    User *aUser;
    
    for (int i = 0; i < parsedCsv.size(); i++) {
        if (atoi(parsedCsv[i][0].c_str()) == userId) { // We found the record we want.
            std::vector<std::string> userRecord = parsedCsv[i];
            
            aUser = new User(userId,
                             atoi(userRecord[2].c_str()),
                             (atoi(userRecord[3].c_str()) == 0 ? kSexMale : kSexFemale),
                             userRecord[1],
                             playlistForUser(userId));
        }
    }
    
    return aUser;
}

bool FilesIO::saveUser(User *theUser) {
    // Load the whole user list
    
    CSVParser parser(usersFile.c_str());
    
    std::vector<std::vector<std::string>> userList = parser.tableRows(true);
    
    // Do the change on the row
    
    bool foundRow = false;
    
    std::vector<std::string> vecToReplace;
    
    vecToReplace.push_back(std::to_string(theUser->userId()));
    vecToReplace.push_back(theUser->name());
    vecToReplace.push_back(std::to_string(theUser->age()));
    vecToReplace.push_back(std::to_string(theUser->gender()));
    
    for (int i = 0; i < userList.size(); i++)
        if (atoi(userList[i][0].c_str()) == theUser->userId()) {
            userList[i] = vecToReplace;
            
            foundRow = true;
        }
    
    if (!foundRow)
        userList.push_back(vecToReplace);
    
    // Re-convert back to CSV
    
    std::string outCsv = parser.encodeCSV(userList);
    
    // Save the changes back to the file
    
    std::remove(usersFile.c_str());
    
    std::ofstream thefile(usersFile);
    
    if (thefile.is_open()) {
        thefile << outCsv;
        
        thefile.close();
        
        return true;
    } else
        return false;
}

//
//  Playlist File Format: (prone to change!)
//
//  musicId,playCount
//

Playlist FilesIO::playlistForUser(int userId) {
    Playlist returnPlaylist;
    
    std::string playlistFileName = "playListUser";
    
    std::ostringstream oss;
    
    oss << userId;
    
    playlistFileName += oss.str();
    
    playlistFileName += ".csv";
    
    CSVParser parser(playlistFileName);
    
    std::vector<std::vector<std::string>> rows = parser.tableRows(true);
    
    for (int i = 0; i < rows.size(); i++) {
        std::vector<Music *> searchResult = RadioStation::Instance()->allTracks().search(atoi(rows[i][0].c_str()), "", 0, "", "");
        
        if (searchResult.size() != 1) {
            std::cout << "A music track wasn't found for ID " << rows[i][0] << ", or the result was ambiguous. Please look into this!" << std::endl;
        } else
            returnPlaylist.addSong(searchResult[0], atoi(rows[i][1].c_str()));
    }
    
    return returnPlaylist;
}

Playlist FilesIO::playlistForUser(std::string userName) {
    return playlistForUser(UserManager::Instance()->getUser(userName)->userId());
}

bool FilesIO::storePlaylistForUser(int userId) {
    Playlist userPlaylist = UserManager::Instance()->getUser(userId)->playlist();
    
    std::vector<Music *> result = userPlaylist.search(0, "", 0, "", "");
    
    std::vector<std::vector<std::string>> csvVec;
    
    std::vector<std::string> headerVec;
    
    headerVec.push_back("musicId");
    headerVec.push_back("playCount");
    
    csvVec.push_back(headerVec);
    
    for (int i = 0; i < result.size(); i++) {
        Music *song = result[i];
        
        std::vector<std::string> songVec;
        
        songVec.push_back(std::to_string(song->musicId()));
        songVec.push_back(std::to_string(song->playCount()));
        
        csvVec.push_back(songVec);
    }
    
    CSVParser parser;
    
    std::string outCsv = parser.encodeCSV(csvVec);
    
    std::string userFileName = userBase;
    
    userFileName.append(std::to_string(userId));
    
    userFileName.append(".csv");
    
    std::remove(userFileName.c_str());
    
    std::ofstream thefile(userFileName);
    
    if (thefile.is_open()) {
        thefile << outCsv;
        
        thefile.close();
        
        return true;
    } else
        return false;
}

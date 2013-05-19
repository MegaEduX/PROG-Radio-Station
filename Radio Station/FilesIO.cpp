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
static const std::string topTenFile = "topTen.csv"; // Still not done!

FilesIO *FilesIO::fio_pInstance = NULL;

FilesIO* FilesIO::Instance() {
    if (!fio_pInstance)
        fio_pInstance = new FilesIO;
    
    return fio_pInstance;
}

bool FilesIO::_writeToFile(std::string filePath, std::string contents, bool replace) {
    if (replace)
        std::remove(filePath.c_str());
    
    std::ofstream thefile(filePath);
    
    if (thefile.is_open()) {
        thefile << contents;
        
        thefile.close();
        
        return true;
    }
    
    return false;
}

//
//  Globals File Format: (prone to change!)
//  key,value
//  name,the-name
//

bool FilesIO::loadGlobals() {
    CSVParser parser(globalsFile);
    
    std::vector<std::vector<std::string>> parsedCsv = parser.tableRows(true);
    
    if (parsedCsv.size() < 1)
        return false;
    
    RadioStation::Instance()->setName(parsedCsv[0][1]);
    
    return true;
}

bool FilesIO::storeGlobals() {
    CSVParser parser(globalsFile);
    
    // Check for file existance
    
    std::ifstream thefile(globalsFile);
    
    std::vector<std::vector<std::string>> parsedCsv;
    
    if (thefile.is_open()) {
        thefile.close();
        
        parsedCsv = parser.tableRows(true);
        
        if (strcmp(parsedCsv[0][0].c_str(), "name") == 0)
            parsedCsv[0][1] = RadioStation::Instance()->name();
        else
            return false;
    } else {
        std::vector<std::string> headerVec;
        
        headerVec.push_back("key");
        headerVec.push_back("value");
        
        parsedCsv.push_back(headerVec);
        
        std::vector<std::string> kvVec;
        
        kvVec.push_back("name");
        kvVec.push_back(RadioStation::Instance()->name());
        
        parsedCsv.push_back(kvVec);
    }
    
    std::string outCsv = parser.encodeCSV(parsedCsv);
    
    return _writeToFile(globalsFile, outCsv, true);
}

//
//  Top 10 File Format: (prone to change!)
//
//  id
//

bool FilesIO::loadTopTen() {
    CSVParser parser(topTenFile);
    
    std::vector<std::vector<std::string>> parsedCsv = parser.tableRows(true);
    
    Playlist topTenPlaylist;
    
    if (parsedCsv.size() < 1)
        return false;
    
    bool foundErrors = false;
    
    for (int i = 0; i < parsedCsv.size(); i++) {
        std::vector<Music *> search = RadioStation::Instance()->allTracks().search(atoi(parsedCsv[i][0].c_str()), "", 0, "", "", "", 0);
        
        if (search.size() > 0) {
            topTenPlaylist.addSong(search[0], atoi(parsedCsv[i][1].c_str()));
        } else {
            std::cout << "Couldn't find song with ID " << parsedCsv[i][0] << ". Maybe the database is corrupt? Proceeding anyway..." << std::endl;
            
            foundErrors = true;
        }
    }
    
    if (RadioStation::Instance() -> updateTopTen(topTenPlaylist) && !foundErrors)
        return true;
    
    return false;
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
    
    return _writeToFile(usersFile, outCsv, true);
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
        std::vector<Music *> searchResult = RadioStation::Instance()->allTracks().search(atoi(rows[i][0].c_str()), "", 0, "", "", "", 0);
        
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
    
    std::vector<Music *> result = userPlaylist.search(0, "", 0, "", "", "", 0);
    
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
    
    return _writeToFile(userFileName, outCsv, true);
}

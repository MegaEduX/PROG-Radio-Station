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

FilesIO *FilesIO::fio_pInstance = NULL;

FilesIO* FilesIO::Instance() {
    if (!fio_pInstance)
        fio_pInstance = new FilesIO;
    
    return fio_pInstance;
}

//
//  Users File Format:
//
//  name,age,gender
//

bool FilesIO::loadGlobals() {
    
}

bool FilesIO::storeGlobals() {
    
}

//
//  Playlist File Format: (prone to change!)
//
//  musicId
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
        for (int j = 0; j < rows[i].size(); i++) {
            std::vector<Music *> searchResult = RadioStation::Instance()->allTracks().search(atoi(rows[i][j].c_str()), "", 0, "", "");
            
            if (searchResult.size() != 1) {
                std::cout << "A music track wasn't found for ID " << rows[i][j] << ", or the result was ambiguous. Please look into this!" << std::endl;
            } else
                returnPlaylist.addSong(searchResult[0], 0);
        }
    }
    
    return returnPlaylist;
}

Playlist FilesIO::playlistForUser(std::string userName) {
    return playlistForUser(UserManager::Instance()->getUser(userName)->userId());
}

bool FilesIO::storePlaylistForUser(int userId) {
    
}

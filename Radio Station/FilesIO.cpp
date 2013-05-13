//
//  FilesIO.cpp
//  Radio Station
//
//  Created by Eduardo Almeida on 13/05/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#include "FilesIO.h"

FilesIO *FilesIO::fio_pInstance = NULL;

FilesIO* FilesIO::Instance() {
    if (!fio_pInstance)
        fio_pInstance = new FilesIO;
    
    return fio_pInstance;
}

bool FilesIO::loadGlobals() {
    
}

bool FilesIO::storeGlobals() {
    
}

Playlist FilesIO::playlistForUser(int userId) {
    
}

Playlist FilesIO::playlistForUser(std::string userName) {
    
}

bool FilesIO::storePlaylistForUser(int userId) {
    
}
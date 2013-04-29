#include <iostream>
#include <vector>
#include <string>

#include "Music.h";
#include "Playlist.h"

class FilesIO {
private:
	FilesIO(); // By this point, you must already have noticed that I love singletons.

	FilesIO(FilesIO const&); // Copy constructor is private.
	FilesIO& operator=(FilesIO const&); // Assignment operator is private.

	static FilesIO *fio_pInstance;

public:
	static FilesIO* Instance();
    
    //
    // The global files
    //  - radioStationMusics.csv
    //  - topTen.csv
    //  - users.csv
    //
    // Usually only need to be loaded / written to
    // a few times per session.
    //
    // So we can merge them, for simplicity.
    //
    
    bool loadGlobals();
    bool storeGlobals();
    
    //
    // Loads the playlistUserXXX.csv or searches
    // for an user with that username.
    //
    
    Playlist playlistForUser(int userid);
    Playlist playlistForUser(std::string userName);
    
    //
    // Saves the user playlist.
    //

    bool storePlaylistForUser(int userid);
};

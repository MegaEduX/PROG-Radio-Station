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
    
    bool loadGlobals();
    bool storeGlobals();
    
    Playlist playlistForUser(int userid);
    Playlist playlistForUser(std::string userName);

    bool storePlaylistForUser(int userid);
};

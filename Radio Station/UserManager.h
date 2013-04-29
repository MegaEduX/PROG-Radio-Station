#include <iostream>
#include <string>
#include <vector>

class User;

class UserManager {
    
private:
    
	UserManager(); // There can only be one user manager, so a singleton here is completely appropriate.

	UserManager(UserManager const&); // Copy constructor is private.
	UserManager& operator=(UserManager const&); // Assignment operator is private.

	static UserManager *um_pInstance;

	std::vector<User *> userVector;

public:
    
	static UserManager* Instance();

	bool addUser(User *aUser);

	bool removeUser(User *aUser);
	bool removeUser(int userId);
    
    const User* getUser(int userId);
    const User* getUser(std::string userName);
    
};
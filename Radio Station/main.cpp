//
//  main.cpp
//  Radio Station
//
//  Created by Eduardo Almeida on 13/05/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#include <iostream>
#include <string>
#include "UserManager.h"
#include "User.h"
#include <ctype>
#include "Playlist.h"


void Login(){
	
	User *theUser = NULL;

		do {
			std::cout << "Enter ID or Username: ";
			std::getline(std::cin, username);

			if (atoi(username.c_str()))
				theUser = UserManager::Instance()->getUser(atoi(username.c_str()));
			else
				theUser = UserManager::Instance()->getUser(username);

			if (!theUser)
				std::cout << "ID/Username not found! Try again!" << std::endl;
			

		} while (!theUser);		
}
		
void NewUser(){

	std::string age;
	char sex;
	std::string name;


		std::cout << "Username: ";
		std::getline(std::cin, username);
		std::cout << std::endl;

		do{

		std::cout << "Age: ";
		std::cin >> age;
		atoi(age.c_str());
		std::cout << std::endl;

		} while (!atoi(age.c_str()));

		do{

		std::cout << "Gender(M/F): ";
		std::cin >> sex;
		std::cout << std::endl;
		sex=toupper(sex);
		
		}while (!( sex == 'M' || sex == 'F' ));

		do{

		std::cout << "Full Name: ";
		std::getline(std::cin, name);
		std::cout << std::endl;

		} while (atoi(name.c_str()));

		Playlist newPlaylist;

		theUser = new User(UserManager::Instance()->userCount(), age, (sex == 'F' ? kSexFemale : kSexMale), name, newPlaylist);

}

void startscreen(){
	
	int opc = 0;
	
	std::string username;

	std::cout << "HELLO AND WELCOME TO THE RADIO!\n" << std::endl;
	std::cout << "1. Login (ID or Username) \n";
	std::cout << "2. Create New User\n";

	std::cin >> opc;

	switch (opc){

	case 1 :

		Login();
			
		break;

	case 2:

		NewUser();

		break;
	}

}

int main(int argc, const char * argv[]){

	startscreen();

	system("pause");
	return 0;


}
//
//  Additions.h
//  Radio Station
//
//  Created by Eduardo Almeida on 13/05/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#ifndef AdditionsHeader
#define AdditionsHeader

#include <iostream>
#include <sstream>
#include <fstream>
#include <cerrno>
#include <vector>

#ifndef WIN32
int getch();
#endif

static const std::string esc = "__esc_key_pressed__";

namespace Additions {
    std::vector<std::string> explode(const std::string &delimiter, const std::string &str);
    
    std::string get_file_contents(const char *filename);
    
    std::string getline();
    
    bool checkForOnlyNumeric(std::string str);
    
    bool gotESC(std::string str);
    
    void clearConsole();
    
    void waitForReturn();
}

#endif

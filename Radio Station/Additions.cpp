//
//  Additions.cpp
//  Radio Station
//
//  Created by Eduardo Almeida on 13/05/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#include "Additions.h"

#ifdef WIN32
#include <windows.h>
#endif

namespace Additions {
    std::vector<std::string> explode(const std::string &delimiter, const std::string &str) {
        std::vector<std::string> arr;
        
        int strleng = (int) str.length();
        int delleng = (int) delimiter.length();
        
        if (delleng == 0)
            return arr;
        
        int i = 0;
        int k = 0;
        
        while (i < strleng) {
            int j = 0;
            while (i + j < strleng && j < delleng && str[i + j] == delimiter[j])
                j++;
            
            if (j == delleng) {
                arr.push_back(str.substr(k, i-k));
                i += delleng;
                k = i;
            } else {
                i++;
            }
        }
        
        arr.push_back(  str.substr(k, i-k) );
        return arr;
    }
    
    std::string get_file_contents(const char *filename) {
        std::ifstream in (filename, std::ios::in | std::ios::binary);
        if (in) {
            std::string contents;
            in.seekg(0, std::ios::end);
            contents.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&contents[0], contents.size());
            in.close();
            return(contents);
        }
        throw(errno);
    }
    
    void clearConsole() {
#ifndef WIN32
        std::cout << "\033[2J";
        std::cout.flush();
#else
        COORD upperLeftCorner = {0,0};
        DWORD charsWritten;
        DWORD conSize;
        HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO  csbi;
        
        GetConsoleScreenBufferInfo(hCon, &csbi);
        conSize = csbi.dwSize.X * csbi.dwSize.Y;
        
        FillConsoleOutputCharacter(hCon, TEXT(' '), conSize, upperLeftCorner, &charsWritten);
        GetConsoleScreenBufferInfo(hCon, &csbi);
        FillConsoleOutputAttribute(hCon, csbi.wAttributes, conSize, upperLeftCorner, &charsWritten);
        
        SetConsoleCursorPosition(hCon, upperLeftCorner);
#endif
    }
}

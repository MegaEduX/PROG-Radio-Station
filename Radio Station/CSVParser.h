//
//  CSVParser.h
//  Radio Station
//
//  Created by Eduardo Almeida on 13/05/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#ifndef CSVParserHeader
#define CSVParserHeader

#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>

class CSVParser {
    
private:
    
    std::string _filePath;
    
public:
    
    CSVParser(std::string filePath);
    
    std::vector<std::vector<std::string>> parseCSV();
};

#endif

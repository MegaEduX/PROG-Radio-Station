//
//  CSVParser.cpp
//  Radio Station
//
//  Created by Eduardo Almeida on 13/05/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#include "CSVParser.h"

#include "Additions.h"

CSVParser::CSVParser(std::string filePath) {
    _filePath = filePath;
}

std::vector<std::vector<std::string>> CSVParser::parseCSV() {
    std::vector<std::vector<std::string>> returnVec;
    
    std::ifstream ifile (_filePath);
    
    std::string line;
    
    while (std::getline(ifile, line))
        returnVec.push_back(explode(",", line));
    
    return returnVec;
}
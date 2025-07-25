//
//  Utils.cpp
//  Engine
//
//  Created by Daniel Almeida on 25/07/2025.
//

#include "Utils.hpp"


bool checkFileExists(const std::string& path) {
    ofFile file(path);
    return file.exists();
}


bool checkFileExistsInData(const std::string& path) {
    std::string dataPath = ofToDataPath("", true);
    std::string fullPath = dataPath + "/" + path;
    
    return checkFileExists(fullPath);
}


std::string base36(std::uintptr_t value) {
    const char* chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string result;
    do {
        result = chars[value % 36] + result;
        value /= 36;
    } while (value > 0);
    return result;
}




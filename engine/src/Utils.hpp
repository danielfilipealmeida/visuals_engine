//
//  Utils.hpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 11/07/2025.
//

#ifndef Utils_h
#define Utils_h


/// \brief Checks if a file exists anywhere on the local computer
///
/// \param path - the path to the file
///
/// \returns boolean value 
inline bool checkFileExists(const std::string& path) {
    ofFile file(path);
    return file.exists();
}

/// \brief Checks if a file exists anywhere inside the data folder, next to the executable
///
/// \param path - the path to the file
///
/// \returns boolean value
inline bool checkFileExistsInData(const std::string& path) {
    std::string dataPath = ofToDataPath("", true);
    std::string fullPath = dataPath + "/" + path;
    
    return checkFileExists(fullPath);
}


#endif /* Utils_h */

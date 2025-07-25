//
//  Utils.hpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 11/07/2025.
//

#ifndef Utils_h
#define Utils_h

#include <iostream>
#include <cstdint>
#include <string>
#include <cctype>
#include "ofMain.h"


/// \brief Checks if a file exists anywhere on the local computer
///
/// \param path - the path to the file
///
/// \returns boolean value 
bool checkFileExists(const std::string& path);


/// \brief Checks if a file exists anywhere inside the data folder, next to the executable
///
/// \param path - the path to the file
///
/// \returns boolean value
bool checkFileExistsInData(const std::string& path);


/// \brief Returns the base36 string from an address
///
/// \param value - the address value
///
/// \returns a string representing the address encoded in base46
std::string base36(std::uintptr_t value);


/// \brief gets the base64 representation of the address of a pointer
///
/// \param ptr - the pointer
///
/// \returns the base36 representation of the pointer in a string
template <typename T>
std::string hashFromAddress(T* ptr) {
    std::uintptr_t addr = reinterpret_cast<std::uintptr_t>(ptr);
    return base36(addr);
}

#endif /* Utils_h */

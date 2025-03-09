//
//  Set.hpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 13/01/2025.
//


#ifndef __set_hpp__
#define __set_hpp__

#include "Elements/Visuals.hpp"
#include "Elements/BaseClasses.hpp"


//! @class Set
//! @abstract Class that Gathers all data of a VJSet
class Set: public Encodable {
public:
    //! @var visuals
    //! @abstract a vector containing all visuals to be used in the Set
    std::vector<VisualsInterface*> visuals;
    
    //! @var thubnails
    //! @abstract a vector of FBOs storing all thumbnails of all visuals
    std::vector<ofFbo> thumbnails;
    
    //! \brief Adds a visual to the list of visuals in the set
    //!
    //! \param visual an object that inherints VisualsInterface
    void addVisual(VisualsInterface* visual);
    
    //! \brief Generates a JSON representation of the set
    //!
    //! \return a ofJson object representing the current state of the sets
    ofJson encode();
    
    //! @abstract Sets the set data from the json
    //! @param data json data
    void decode(ofJson data);
    
    //! @abstract Saves a set to the filesystem into a json gile
    //! @param path a string defining the filepath
    void save(std::string path);
    
    //! @abstract Loads the content of a json file storing a set
    //! @param path the path of the file to load in a string
    void load(std::string path);
};

#endif

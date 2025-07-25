//
//  Set.hpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 13/01/2025.
//


#ifndef __set_hpp__
#define __set_hpp__

#include "Visuals.hpp"
#include "BaseClasses.hpp"


/// @class Set
///
/// @brief Class that Gathers all data of a VJSet
///
/// @details Gathers all visuals used on an App, as well as the thumbnails for displaying. This stores all visual instances used on an App.
/// There can be several visual instance of the same base visual, with different configurations.
class Set: public Encodable {
public:
    
    
    /// @var visuals
    /// @brief a vector containing all visuals to be used in the Set
    std::vector<VisualsInterface*> visuals;
    
    /// @var thubnails
    /// @brief a vector of FBOs storing all thumbnails of all visuals
    /// @todo: move this to the visual repositoryu
    std::vector<ofFbo> thumbnails;
    
    /// \brief Adds a visual to the list of visuals in the set
    ///
    /// \param visual an object that inherints VisualsInterface
    void addVisual(VisualsInterface* visual);
    
    /// \brief Generates a JSON representation of the set
    ///
    /// \return a ofJson object representing the current state of the sets
    ofJson encode();
    
    /// @brief Sets the set data from the json
    ///
    /// @param data json data
    void decode(ofJson data);
    
    /// @brief Saves a set to the filesystem into a json file
    ///
    /// @param path a string defining the filepath
    void save(std::string path);
    
    /// @brief Loads the content of a json file storing a set
    ///
    /// @param path the path of the file to load in a string
    void load(std::string path);
    
    
    /// \brief Returns the visual in the vector at the provided index or NULL if outside the elements
    ///
    /// \param index - the position of the visual in the visuals vector
    ///
    /// \returns the visual if inside the vector or NULL
    VisualsInterface* getVisualAtIndex(unsigned int index);
    
    
    /// \brief Returns the visual with a given id
    ///
    /// \details This is used only when loading a file. the id is only generated on save so it is possible to associate what visual is set in what layer.
    ///
    /// \param id - the id of the visual
    ///
    /// \returns the visual with the given id
    VisualsInterface* getVisualById(std::string id);
    
};

#endif

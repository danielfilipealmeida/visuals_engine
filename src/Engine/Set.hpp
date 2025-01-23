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


/// Class that Gathers all data of a VJSet
class Set: public Encodable {
public:
    std::vector<VisualsInterface*> visuals;
    std::vector<ofFbo> thumbnails;
    
    /// \brief Adds a visual to the list of visuals in the set
    ///
    /// \param visual an object that inherints VisualsInterface
    void addVisual(VisualsInterface* visual) {
        visuals.push_back(visual);
    };
    
    
    ofJson encode() {
        ofJson visualsJson;
        
        for (VisualsInterface *visual : visuals) {
            visualsJson.push_back(visual->encode());
        }
        
        ofJson result = {
            {"visuals", visualsJson}
        };
        
        
        return result;
    };
};

#endif

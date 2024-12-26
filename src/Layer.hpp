//
//  Layer.hpp
//  emptyExample
//
//  Created by Daniel Almeida on 26/12/2024.
//

#ifndef Layer_hpp
#define Layer_hpp

#include "BaseClasses.hpp"
#include <vector>


class Layer: Drawable {
    std::vector<VisualsInterface *> visuals;
    
public:
    void update();
    void draw();
    void insert(VisualsInterface* visual);
};

#endif

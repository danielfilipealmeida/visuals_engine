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
    float alpha;
    VisualsInterface* visual;
    ofBlendMode blendMode;
    
public:
    Layer(
          VisualsInterface* _visual,
          float alpha = 1,
          ofBlendMode blendMode = OF_BLENDMODE_ADD
        );
    void update();
    void draw();
};


class LayerStack: Drawable {
    std::vector<Layer *> layers;
    
public:
    void update();
    void draw();
    void insert(Layer* visual);
};
#endif

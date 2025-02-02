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


class Layer: public VisualsInterface {
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
    void draw(ofRectangle rect);
    ofJson encode();
};


class LayerStack: public VisualsInterface {
    std::vector<Layer *> layers;
    ofFbo buffer;
    float width;
    float height;
    
public:
    LayerStack(float _width, float _height);
    void update();
    void draw();
    void draw(ofRectangle rect);
    void insert(Layer* visual);
    ofJson encode();
};
#endif

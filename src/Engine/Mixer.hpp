//
//  Mixer.hpp
//  emptyExample
//
//  Created by Daniel Almeida on 27/12/2024.
//

#ifndef __Mixer_hpp__
#define __Mixer_hpp__

#include "Layer.hpp"


class Mixer: public Drawable {
    LayerStack *a, *B;
    float mix;
    ofFbo *buffer;
public:
    Mixer(LayerStack* _A, LayerStack* _B, float _bufferWidth, float _bufferHeight);
   
    void update();
    void draw();
    void draw(ofRectangle rect);
    
    void setMix(float _mix);
};

#endif

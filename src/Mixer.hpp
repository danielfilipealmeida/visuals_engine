//
//  Mixer.hpp
//  emptyExample
//
//  Created by Daniel Almeida on 27/12/2024.
//

#ifndef __Mixer_hpp__
#define __Mixer_hpp__

#include "Layer.hpp"

class Mixer: Drawable {
    LayerStack *a, *B;
    float mix;
public:
    Mixer(LayerStack* _A, LayerStack* _B);
   
    void update();
    void draw(ofRectangle rect);
    
    void setMix(float _mix);
};

#endif

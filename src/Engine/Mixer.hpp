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
    float mix;
    ofFbo *buffer;
public:
    VisualsInterface *a, *b;
    
    Mixer(VisualsInterface* _A, VisualsInterface* _B, float _bufferWidth, float _bufferHeight);
   
    void update();
    void draw();
    void draw(ofRectangle rect);
    
    void setMix(float _mix);
};

#endif

//
//  Mixer.hpp
//  emptyExample
//
//  Created by Daniel Almeida on 27/12/2024.
//

#ifndef __Mixer_hpp__
#define __Mixer_hpp__

#include "Layer.hpp"
#include "Observer.hpp"

enum class MixerObservableParameters {
    MIX
};

class Mixer: public Drawable, public Observer<float> {
    float mix;
    ofFbo *buffer;
public:
    VisualsInterface *a, *b;
    
    std::map<MixerObservableParameters, std::string> parameters = {
        {MixerObservableParameters::MIX, "mix"}
    };
    
    Mixer(VisualsInterface* _A, VisualsInterface* _B, float _bufferWidth, float _bufferHeight);
   
    void update() override;
    void draw() override;
    void draw(ofRectangle rect)  override;
    
    void setMix(float _mix);
    
    void update(float val, std::string key) override;
};



#endif

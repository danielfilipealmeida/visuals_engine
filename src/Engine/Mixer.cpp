//
//  Mixer.cpp
//  emptyExample
//
//  Created by Daniel Almeida on 27/12/2024.
//

#include "Mixer.hpp"
#include <cmath>

Mixer::Mixer(LayerStack* _a, LayerStack* _b, float _bufferWidth, float _bufferHeight) {
    a = _a;
    B = _b;
    mix = 0.5;
    buffer = new ofFbo();
    buffer->allocate(_bufferWidth, _bufferHeight);
    rect = ofRectangle(0,0, _bufferWidth, _bufferHeight);
}


void Mixer::update() {
    a->update();
    B->update();
    
    buffer->begin();
    ofEnableAlphaBlending();
    //ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofClear(0,0,0);
    ofSetColor(255,255,255);
    a->draw(rect);
    int alpha = (int) round(255.0 * mix);
    ofSetColor(255, 255, 255, alpha);
    B->draw(rect);
    //ofDisableBlendMode();
    ofDisableAlphaBlending();
    ofSetColor(255,255,255);
    buffer->end();
}

void Mixer::draw() {
    draw(rect);
}

void Mixer::draw(ofRectangle rect) {
    
    ofSetColor(255,255,255);
    buffer->draw(rect);
}

/// \brief Sets the mix,
///
/// \param _mix 0 is for A channel and 1 is for B channel. in betwen is the mix value
void Mixer::setMix(float _mix) {
    mix = ofClamp(_mix, 0.0, 1.0);
}

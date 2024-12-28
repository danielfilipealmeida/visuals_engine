//
//  Mixer.cpp
//  emptyExample
//
//  Created by Daniel Almeida on 27/12/2024.
//

#include "Mixer.hpp"
#include <cmath>

Mixer::Mixer(LayerStack* _a, LayerStack* _b) {
    a = _a;
    B = _b;
    mix = 0.5;
}


void Mixer::update() {
    a->update();
    B->update();
}

void Mixer::draw(ofRectangle rect) {
    ofSetColor(255,255,255);
    a->draw(rect);
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255, (int) round(255 * mix));
    B->draw(rect);
    ofDisableAlphaBlending();
}

void Mixer::setMix(float _mix) {
    mix = ofClamp(_mix, 0.0, 1.0);
}

//
//  Layer.cpp
//  emptyExample
//
//  Created by Daniel Almeida on 26/12/2024.
//


#include "Layer.hpp"
#include "ofMain.h"


Layer::Layer(
             float bufferWidth,float bufferHeight,
             VisualsInterface* _visual,
             float _alpha,
             ofBlendMode _blendMode
) {
    visual = _visual;
    alpha = _alpha;
    blendMode = _blendMode;
    rect = ofRectangle(0,0, bufferWidth, bufferHeight);
}

void Layer::draw() {
    draw(rect);
}

void Layer::draw(ofRectangle _rect) {
    if (!visual) {
        return;
    }
    ofEnableAlphaBlending();
    ofEnableBlendMode(blendMode);
    ofSetColor(255, 255, 255, (int) (alpha * 255.0));
    visual->draw(_rect);
    ofDisableBlendMode();
    ofDisableAlphaBlending();
}

void Layer::update() {
    if (!visual) {
        return;
    }
    visual->update();
}

ofJson Layer::encode() {
    ofJson json;
    
    return json;
}

void Layer::set(VisualsInterface* _visual) {
    visual = _visual;
}

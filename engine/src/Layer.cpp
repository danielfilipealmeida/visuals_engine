//
//  Layer.cpp
//  emptyExample
//
//  Created by Daniel Almeida on 26/12/2024.
//


#include "Layer.hpp"
#include "ofMain.h"


Layer::Layer(
             VisualsInterface* _visual,
             float _alpha,
             ofBlendMode _blendMode
) {
    visual = _visual;
    alpha = _alpha;
    blendMode = _blendMode;
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
    visual->draw();
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


/** Layer Stack implementation */

LayerStack::LayerStack(float _width, float _height) {
    width = _width;
    height = _height;
    buffer.allocate(width, height);
    rect = ofRectangle(0,0,width, height);
}

void LayerStack::update() {
    // updates all
    for (auto layer: layers) {
        layer->update();
    }
    
    // draws all into buffer
    buffer.begin();
    ofEnableAlphaBlending();
    ofClear(0, 0, 0);
    ofSetColor(255, 255, 255);
    for (auto layer: layers) {
        layer->draw();
    }
    ofDisableAlphaBlending();
    buffer.end();
}

void LayerStack::draw() {
    draw(rect);
}

void LayerStack::draw(ofRectangle _rect) {
    buffer.draw(_rect);
}

void LayerStack::insert(Layer *layer) {
    layers.push_back(layer);
}

ofJson LayerStack::encode() {
    ofJson json;
    
    return json;
}

void LayerStack::setVisualForLayer(unsigned int layerNumber, VisualsInterface *visual) {
    // add the layer if it doesn't exist.
    
    
    }

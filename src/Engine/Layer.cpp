//
//  Layer.cpp
//  emptyExample
//
//  Created by Daniel Almeida on 26/12/2024.
//


#include "Layer.hpp"
#include "ofMain.h"

Layer::Layer(VisualsInterface* _visual,
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
    ofEnableAlphaBlending();
    ofEnableBlendMode(blendMode);
    ofSetColor(255, 255, 255, (int) (alpha * 255.0));
    visual->draw();
    ofDisableBlendMode();
    ofDisableAlphaBlending();
}

void Layer::update() {
    visual->update();
}


/** Layer Stack implementation */

LayerStack::LayerStack(float _width, float _height) {
    width = _width;
    height = _height;
    buffer.allocate(width, height);
}

void LayerStack::update() {
    // updates all
    for (auto layer: layers) {
        layer->update();
    }
    
    // draws all into buffer
    buffer.begin();
    ofClear(0, 0, 0);
    ofSetColor(255, 255, 255);
    for (auto layer: layers) {
        layer->draw();
    }
    buffer.end();
}

void LayerStack::draw() {
    draw(rect);
}

void LayerStack::draw(ofRectangle rect) {
    buffer.draw(rect);
}

void LayerStack::insert(Layer *layer) {
    layers.push_back(layer);
}

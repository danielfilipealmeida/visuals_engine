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


void LayerStack::update() {
    for (auto layer: layers) {
        layer->update();
    }
}

void LayerStack::draw() {
    for (auto layer: layers) {
        layer->draw();
    }
}

void LayerStack::insert(Layer *layer) {
    layers.push_back(layer);
}

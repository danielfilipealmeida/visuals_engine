//
//  LayerStack.cpp
//  Hello World
//
//  Created by Daniel Almeida on 14/07/2025.
//

#include "LayerStack.hpp"
#include "ofMain.h"
#include "Visuals.hpp"

LayerStack::LayerStack(float _width, float _height) {
    width = _width;
    height = _height;
    buffer.allocate(width, height);
    rect = ofRectangle(0,0,width, height);
}


LayerStack::~LayerStack() {
    for(Layer *layer : layers ) {
        if (typeid(layer) == typeid(VisualsInterface)) {
            delete (layer);
        }
    }
    
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
    
    json["type"] = "layerstack";
    json["width"] = width;
    json["height"] = height;
    
    std::vector<ofJson> layersEncode;
    for(Layer* layer : layers) {
        layersEncode.push_back(layer->encode());
    }
    json["layers"] = layersEncode;
    
    return json;
}


void LayerStack::decode(ofJson json) {
    
}


void LayerStack::setVisualForLayer(unsigned int layerNumber, VisualsInterface *visual) {
    // returns if the layerNumber is outside the layers
    if (layerNumber >= layers.size()) {
        return;
    }
    
    // stop the current visual if it is still playing
    VisualsInterface *currentVisual = layers[layerNumber]->visual;
    if (currentVisual) {
        currentVisual->stop();
    }

    layers[layerNumber]->set(visual);
    visual->play();
}

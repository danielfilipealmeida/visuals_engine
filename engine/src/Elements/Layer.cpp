//
//  Layer.cpp
//  emptyExample
//
//  Created by Daniel Almeida on 26/12/2024.
//


#include "Layer.hpp"
#include "ofMain.h"
#include "Utils.hpp"

std::map<ofBlendMode, std::string>  blendModeMappings = {
    {ofBlendMode::OF_BLENDMODE_DISABLED, "disabled"},
    {ofBlendMode::OF_BLENDMODE_ALPHA, "alpha"},
    {ofBlendMode::OF_BLENDMODE_ADD, "add"},
    {ofBlendMode::OF_BLENDMODE_SUBTRACT, "subtract"},
    {ofBlendMode::OF_BLENDMODE_MULTIPLY, "multiply"},
    {ofBlendMode::OF_BLENDMODE_SCREEN, "screen"}
};

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

Layer::~Layer() {
    if (visual == NULL) {
        return;
    }
    
    delete(visual);
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
    
    json["type"] = "layer";
    json["width"] = rect.width;
    json["height"] = rect.height;
    json["alpha"] = alpha;
    json["blendMode"] = blendModeMappings[blendMode];
    json["visualId"] = hashFromAddress(visual);
    
    return json;
}

Layer* Layer::FromJson(ofJson json) {
    float width = json["width"].get<float>();
    float height = json["height"].get<float>();
    float alpha = json["alpha"].get<float>();
    
    // todo: move this elsewhere to be executed only once
    std::map<std::string, ofBlendMode>  invertedBlendModeMapping;
    for (const auto& pair : blendModeMappings) {
        invertedBlendModeMapping[pair.second] = pair.first;
    }
    
    ofBlendMode blendMode = invertedBlendModeMapping[json["blendMode"].get<string>()];
    
    
    Layer *layer = new Layer(width, height, NULL, alpha, blendMode);
    
    return layer;
}

void Layer::set(VisualsInterface* _visual) {
    visual = _visual;
}

//
//  Layer.cpp
//  emptyExample
//
//  Created by Daniel Almeida on 26/12/2024.
//


#include "Layer.hpp"

void Layer::update() {
    for (auto visual: visuals) {
        visual->update();
    }
}

void Layer::draw() {
    for (auto visual: visuals) {
        visual->draw();
    }
}

void Layer::insert(VisualsInterface *visual) {
    visuals.push_back(visual);
}

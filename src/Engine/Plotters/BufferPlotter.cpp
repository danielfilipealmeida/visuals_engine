//
//  BufferPlotter.cpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 17/03/2025.
//

#include "BufferPlotter.hpp"


BufferPlotter::BufferPlotter(
                             vector<float> *_data,
                             unsigned int _width,
                             unsigned int _height
                             ) : Plotter(_width, _height)
{
    data = _data;
    nSamples = _data->size();
    setSampleWith(data->size());
    gain = 255.0;
    lineWidth = 1.0;
}

void BufferPlotter::update() {
    buffer.begin();
    ofClear(0, 0, 0, 255);          // Clear the FBO
    ofSetColor(color);
    ofPath path;
    ofEnableAntiAliasing();
    path.setStrokeColor(ofColor::white);
    path.setStrokeWidth(lineWidth);
    path.setFilled(false);
    
    float midScreen = rect.height / 2.0;
    
    path.moveTo(0, midScreen - (*data)[0] * gain);
    for(int f=1; f<data->size(); f++) {
        float val = (*data)[f] * gain;
        path.lineTo(f * sampleWidth, midScreen - val);
    }
    
    path.draw();
    buffer.end();
}

void BufferPlotter::draw() {
    buffer.draw(ofRectangle(0,0,ofGetWidth(), ofGetHeight()));
}

void BufferPlotter::draw(ofRectangle _rect) {
     buffer.draw(_rect);
};


void BufferPlotter::play() {}

void BufferPlotter::stop() {}

void BufferPlotter::setSampleWith(unsigned long newSize) {
    sampleWidth = rect.width / (float) newSize;
}

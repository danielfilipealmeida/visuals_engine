//
//  SignalPlotter.cpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 23/01/2025.
//

//
//  SignalPlotter.hpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 13/01/2025.
//

#include "SignalPlotter.hpp"

SignalPlotter::SignalPlotter(){}

SignalPlotter::SignalPlotter(Signal<float> *_signal, unsigned int _nSamples, unsigned int _height) {
    signal = _signal;
    nSamples = _nSamples;
    height = _height;
    buffer.allocate(nSamples, height);
    color = ofColor::white;
    mode = SignalPlotterMode::Lines;
};

void SignalPlotter::update() {
    if (samples.size() == nSamples) {
        samples.erase(samples.begin());
    }
    samples.push_back(signal->getValue());
    
    buffer.begin();
    ofClear(0, 0, 0, 255);          // Clear the FBO
    ofSetColor(color);
    
    float previousY, currentY;
    
    float half = height / 2.0;
    for (int f=0; f<nSamples; f++) {
        if (f==samples.size()) {
            break;
        }
        
        currentY = half + samples[f] * half;
        switch (mode) {
            case SignalPlotterMode::Dots:
                ofDrawRectangle(f,currentY, 1, 1);
                break;
                
            case SignalPlotterMode::Lines:
                if (f == 0) {
                    continue;
                }
                ofDrawLine(f-1, previousY, f, currentY);
                break;
        }
        previousY = currentY;
        
    }
    
    buffer.end();
};

void SignalPlotter::draw() {
    buffer.draw(ofRectangle(0,0,ofGetWidth(), ofGetHeight()));
};

void SignalPlotter::draw(ofRectangle _rect) {
    buffer.draw(_rect);
};

void SignalPlotter::play(){}
void SignalPlotter::stop(){}


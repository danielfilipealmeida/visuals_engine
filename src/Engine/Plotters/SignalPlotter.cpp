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

SignalPlotter::SignalPlotter(
                             Signal<float> *_signal,
                             unsigned int _nSamples,
                             unsigned int _width,
                             unsigned int _height) : Plotter(_width, _height)
{
    signal = _signal;
    nSamples = _nSamples;
    
    sampleWidth = rect.width / (float) nSamples;
};


void SignalPlotter::update() {
    if (samples.size() == nSamples) {
        samples.erase(samples.begin());
    }
    samples.push_back(signal->getValue());
    
    Plotter::draw(samples, nSamples);
};

void SignalPlotter::draw() {
    buffer.draw(ofRectangle(0,0,ofGetWidth(), ofGetHeight()));
};

void SignalPlotter::draw(ofRectangle _rect) {
    buffer.draw(_rect);
};

void SignalPlotter::play(){}
void SignalPlotter::stop(){}


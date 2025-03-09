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

SignalPlotter::SignalPlotter(Signal<float> *_signal, unsigned int _nSamples, unsigned int _width, unsigned int _height) {
    signal = _signal;
    nSamples = _nSamples;
    rect = ofRectangle(0,0,_width, _height);
    buffer.allocate(rect.width, rect.height);
    color = ofColor::white;
    mode = SignalPlotterMode::Lines;
    sampleWidth = rect.width / (float) nSamples;
    
    lineWidth = 8.0;
    dotWidth = 8.0;
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
    
    float half = rect.height / 2.0;
    for (int f=0; f<nSamples; f++) {
        if (f==samples.size()) {
            break;
        }
        ofEnableAntiAliasing();
        currentY = half + samples[f] * half;
        switch (mode) {
            case SignalPlotterMode::Dots:
                ofDrawCircle(f*sampleWidth,currentY, dotWidth);
                
                break;
                
            case SignalPlotterMode::Lines:
                if (f == 0) {
                    break;
                }
                ofSetLineWidth(lineWidth);
                ofDrawLine((f-1)*sampleWidth, previousY, f * sampleWidth, currentY);
                
                break;
                
            case SignalPlotterMode::Steps:
                ofSetLineWidth(lineWidth);
                ofDrawLine(f*sampleWidth, currentY, ((f+1) * sampleWidth) - 1, currentY);
                
                break;
                
            case SignalPlotterMode::FilledSteps:
                if (f == 0) {
                    break;
                }
                ofSetLineWidth(lineWidth);
                ofDrawRectangle((f-1)*sampleWidth, previousY, sampleWidth, currentY - previousY);
                
                break;
                
            case SignalPlotterMode::Wave:
                if (f == 0) {
                    break;
                }
                ofSetLineWidth(lineWidth);
                ofDrawRectangle((f-1)*sampleWidth, previousY, f * sampleWidth, currentY);
                
                break;
        }
        ofDisableAntiAliasing();
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


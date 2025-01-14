//
//  SignalPlotter.hpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 13/01/2025.
//

#ifndef __SignalPlotter_H__
#define __SignalPlotter_H__

#include "BaseClasses.hpp"
#include "ofMain.h"


enum class SignalPlotterMode {
    Dots,
    Lines
};
    
class SignalPlotter {
public:
    Signal<float> *signal;
    unsigned int nSamples;
    vector<float> samples;
    ofFbo buffer;
    SignalPlotterMode mode;
    ofColor color;
    
    
    SignalPlotter() {}
    
    SignalPlotter(Signal<float> *_signal, unsigned int _nSamples=514) {
        signal = _signal;
        nSamples = _nSamples;
        buffer.allocate(nSamples, nSamples);
        color = ofColor::white;
        mode =SignalPlotterMode::Lines;
    };
    
    void update() {
        if (samples.size() == nSamples) {
            samples.erase(samples.begin());
        }
        samples.push_back(signal->getValue());
        
        buffer.begin();
        ofClear(0, 0, 0, 255);          // Clear the FBO
        ofSetColor(color);
        
        float previousY, currentY;
        
        float half = nSamples / 2.0;
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
    
    void draw() {
        buffer.draw(ofRectangle(0,0,ofGetWidth(), ofGetHeight()));
    };
    
    void draw(ofRectangle _rect) {
        buffer.draw(_rect);
    };
    
    void play(){}
    void stop(){}
};

#endif



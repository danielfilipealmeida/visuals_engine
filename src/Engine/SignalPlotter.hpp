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
#include "Signals.hpp"


enum class SignalPlotterMode {
    Dots,
    Lines
};
    
class SignalPlotter {
public:
    Signal<float> *signal;
    unsigned int nSamples, height;
    vector<float> samples;
    ofFbo buffer;
    SignalPlotterMode mode;
    ofColor color;
    
    
    /// Constructor of the Signal Plotter
    SignalPlotter();
    
    
    /// Constructor of the Signal Plotter with parameters
    /// - Parameter _signal: The signal to be plotted
    /// - Parameter _nSamples: the number of samples to plot on the screen. will be also considerd the width of the signal
    /// - Parameter _height: the height of the FBO where the signal is internally plotted
    SignalPlotter(Signal<float> *_signal, unsigned int _nSamples=256, unsigned int _height=256);
    
    void update();
    
    void draw();
    
    void draw(ofRectangle _rect);
    
    void play();
    void stop();
    
    void getWidth();
    
    void getHeight();
};

#endif



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
#include "Plotter.hpp"


   
/**
 * @class SignalPlotter
 * @abstract a Drawable that creates a representation of a signal
 */
class SignalPlotter: public Plotter {
public:
    
    //! @var signal
    //! @abstract the signal being displayed
    Signal<float> *signal;

    //! @var nSamples
    //! @abstract the number of samples to draw on the plotter
    unsigned int nSamples;

    //! @var samples
    //! @abstract a vector storing all the last <nSamples> samples
    vector<float> samples;
    
    SignalPlotter(){};
    
    /**
     * @abstract Constructor of the Signal Plotter with parameters
     * @param _signal The signal to be plotted
     * @param _nSamples the number of samples to plot on the screen. will be also considerd the width of the signal
     * @param _height: the height of the FBO where the signal is internally plotted
     */
    SignalPlotter(Signal<float> *_signal, unsigned int _nSamples=32, unsigned int _width=640,unsigned int _height=480);
    
    /**
     * @abstract updates the Signal ploter
     * Should be executed every frame on the update method, if it is to be displayed
     */
    void update();
    
    /**
     * @abstract draws the Signal ploter
     * Should be executed every frame on the draw method, if it is to be displayed
     */
    void draw();
    
    /**
     * @abstract draws the Signal ploter inside a rectangle
     * @param _rect defines the location where to draw the signal plotter
     */
    void draw(ofRectangle _rect);
    
    /**
     * @abstract unused
     */
    void play();
    
    /**
     * @abstract unused
     */
    void stop();
    
    /**
     * @abstract returns the width of the plotter
     */
    void getWidth();
    
    /**
     * @abstract returns the height of the plotter
     */
    void getHeight();
};

#endif

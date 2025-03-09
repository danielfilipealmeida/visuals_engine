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

/**
 * @enum SignalPlotterMode
 * @abstract An enumeration class to define the modes of the Signal Plotter
 */
enum class SignalPlotterMode {
    Dots,           ///< plot dots for each value
    Lines,          ///< use lines to connect all values
    Steps,          ///< uses horizontal lines for each values
    FilledSteps,    ///< similar to Steps but uses filled boxes instead
    Wave            ///< similar to FilledSteps but kinda lool like a wave
};
   
/**
 * @class SignalPlotter
 * @abstract a Drawable that creates a representation of a signal
 */
class SignalPlotter: public Drawable {
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

    //! @var buffer
    //! @abstract a FBO to draw the plotter in memory
    ofFbo buffer;

    //! @var mode
    //! @abstract the mode that the plotter is going to be set
    SignalPlotterMode mode;

    //! @var color
    //! @abstract what color the plotter will use to draw
    ofColor color;

    //! @var sampleWidth
    //! @abstract how much a sample occupies in the fbo
    float sampleWidth;
    
    //! @var lineWidth
    //! @abstract the thickness of the line for the Lines mode
    float lineWidth;
    
    //! @var dotWidth
    //! @abstract the radius of the dot in the Dots mode
    float dotWidth;
        
    //! @abstract Constructor of the Signal Plotter
    SignalPlotter();
    
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

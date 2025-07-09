//
//  BufferPlotter.hpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 16/03/2025.
//

#ifndef __BufferPlotter_H__
#define __BufferPlotter_H__

#include "BaseClasses.hpp"
#include "ofMain.h"
#include "Plotter.hpp"
#include <functional>

//! @class BufferPloter
//! @abstract A plotter specialized on displaying buffers. buffers are set currently just vectors of float. if new types of data are needed in the future, this must be transformed into a class template
class BufferPlotter: public Plotter {
    vector<float> *data;
    
    //! @var nSamples
    //! @abstract the number of samples to draw on the plotter
    unsigned int nSamples;
    
 
public:
    
    BufferPlotter() {}
    
    //! @abstract Default constructor
    //!
    //! @param *_data
    //! @param _width
    //! @param _height
    BufferPlotter(vector<float> *_data, unsigned int _width=640, unsigned int _height=480);
    
    void update();
    
    void draw();
    
    /**
     * @abstract draws the Signal ploter inside a rectangle
     * @param _rect defines the location where to draw the signal plotter
     */
    void draw(ofRectangle _rect);
    
    void play();
    
    void stop();
    
    void setSampleWith(unsigned long newSize);
};

#endif

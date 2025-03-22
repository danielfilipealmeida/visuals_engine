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

class BufferPlotter: public Plotter {
    vector<float> *data;
    
    //! @var nSamples
    //! @abstract the number of samples to draw on the plotter
    unsigned int nSamples;
    
    //! @var buffer
    //! @abstract a FBO to draw the plotter in memory
    ofFbo buffer;
 
public:
    
    BufferPlotter(vector<float> *_data, unsigned int _nSamples, unsigned int _width, unsigned int _height);
    
    void update();
    
    void draw();
    
    void play();
    
    void stop();
};

#endif

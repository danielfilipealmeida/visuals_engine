//
//  Plotter.hpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 17/03/2025.
//


#ifndef __Plotter_Hpp__
#define __Plotter_Hpp__

#include "BaseClasses.hpp"
#include "ofMain.h"

/**
 * @enum PlotterMode
 * @abstract An enumeration class to define the modes of the  Plotter
 */
enum class PlotterMode {
    Dots,           ///< plot dots for each value
    Lines,          ///< use lines to connect all values
    Steps,          ///< uses horizontal lines for each values
    FilledSteps,    ///< similar to Steps but uses filled boxes instead
    Wave,           ///< similar to FilledSteps but kinda lool like a wave
    VerticalLines   ///<
};

class Plotter : public Drawable {
public:
    
    //! @var buffer
    //! @abstract a FBO to draw the plotter in memory
    ofFbo buffer;
    
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
    
    
    Plotter();
    
    //! @var mode
    //! @abstract the mode that the plotter is going to be set
    PlotterMode mode;
    
    Plotter(unsigned int _width, unsigned int _height);

    //! is nPoints really needed? remove it
    void draw(vector<float> points, unsigned int nPoints);
};

#endif

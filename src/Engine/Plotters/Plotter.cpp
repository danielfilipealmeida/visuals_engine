//
//  Plotter.cpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 17/03/2025.
//

#include "Plotter.hpp"


Plotter::Plotter() {}

Plotter::Plotter(unsigned int _width, unsigned int _height) {
    
    rect = ofRectangle(0,0,_width, _height);
    buffer.allocate(rect.width, rect.height);
    
    lineWidth = 4.0;
    dotWidth = 8.0;
    
    color = ofColor::white;
    mode = PlotterMode::VerticalLines;
}


void Plotter::draw(vector<float> points, unsigned int nPoints) {
    buffer.begin();
    ofClear(0, 0, 0, 255);          // Clear the FBO
    ofSetColor(color);
    ofSetLineWidth(lineWidth);
    ofEnableAntiAliasing();
    
    float previousY = 0, currentY = 0;
    
    float half = rect.height / 2.0;
    for (int f=0; f<nPoints; f++) {
        if (f==points.size()) {
            break;
        }
        
        currentY = half + points[f] * half;
        switch (mode) {
            case PlotterMode::Dots:
                ofDrawCircle(f*sampleWidth,currentY, dotWidth);
                
                break;
                
            case PlotterMode::Lines:
                if (f == 0) {
                    break;
                }
                ofDrawLine((f-1)*sampleWidth, previousY, f * sampleWidth, currentY);
                
                break;
                
            case PlotterMode::Steps:
                ofDrawLine(f*sampleWidth, currentY, ((f+1) * sampleWidth) - 1, currentY);
                
                break;
                
            case PlotterMode::FilledSteps:
                if (f == 0) {
                    break;
                }
                ofDrawRectangle((f-1)*sampleWidth, previousY, sampleWidth, currentY - previousY);
                break;
                
            case PlotterMode::Wave:
                if (f == 0) {
                    break;
                }
                
                ofDrawRectangle((f-1)*sampleWidth, previousY, f * sampleWidth, currentY);
                
                break;
                
            case PlotterMode::VerticalLines:
                ofDrawLine( f * sampleWidth, currentY , f * sampleWidth, rect.height);
                
                break;
        }
        ofDisableAntiAliasing();
        previousY = currentY;
        
    }
    
    buffer.end();
}

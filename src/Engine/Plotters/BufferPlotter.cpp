//
//  BufferPlotter.cpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 17/03/2025.
//

#include "BufferPlotter.hpp"


BufferPlotter::BufferPlotter(
                             vector<float> *_data,
                             unsigned int _nSamples,
                             unsigned int _width,
                             unsigned int _height
                             ) : Plotter(_width, _height)
{
    nSamples = _nSamples;
    //rect = ofRectangle(0,0,_width, _height);
    data = _data;
    //buffer.allocate(rect.width, rect.height);
}

void BufferPlotter::update() {
    
}

void BufferPlotter::draw() {
    
}

void BufferPlotter::play() {
    
}

void BufferPlotter::stop() {
    
}

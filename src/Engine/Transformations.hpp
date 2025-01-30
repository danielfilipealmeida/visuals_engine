//
//  Transformations.hpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 28/01/2025.
//

#ifndef __transformations_hpp__
#define __transformations_hpp__

#include "Visuals.hpp"

class TransformationDecorator : public VisualsInterface {
    VisualsInterface *visual;
    ofShader shader;
public:
    TransformationDecorator(VisualsInterface *_visual) {
        visual = _visual;
        shader.load("Base.vert", "FastBlur.frag");
    }
    void update() {
        visual->update();
    }
    void draw() {
        shader.begin();
        visual->draw();
        shader.end();
    }
    void draw(ofRectangle _rect) {
        shader.begin();
        shader.setUniform1f("contrast", 1.0);
        shader.setUniform1f("brightness", 1.0);
        shader.setUniform1f("saturation", 1.0);
        shader.setUniform1f("blurH", 10.0);
        shader.setUniform1f("blurV", 10.0);
        shader.setUniform1f("redTint", 0.0);
        shader.setUniform1f("greenTint", 0.0);
        shader.setUniform1f("blueTint", 0.0);
        
        visual->draw(_rect);
        shader.end();
    }
    
    void play() {}
    void stop() {}
    ofJson encode() {
        return {};
    }
};


class TransformationFactory {
public:
    
    static VisualsInterface* GLSL(VisualsInterface *visual) {
        TransformationDecorator *transformation = new TransformationDecorator(visual);
        
        return transformation;
    };
    
};


#endif

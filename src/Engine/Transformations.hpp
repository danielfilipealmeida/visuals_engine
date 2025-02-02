//
//  Transformations.hpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 28/01/2025.
//

#ifndef __transformations_hpp__
#define __transformations_hpp__

#include "Visuals.hpp"
#include "Signals.hpp"

class GLSLTransformationDecorator : public VisualsInterface {
    VisualsInterface *visual;
    ofShader shader;
public:
    std::map<std::string, Signal<float>*> floatParameters;
    
    GLSLTransformationDecorator(VisualsInterface *_visual, std::string shaderName, bool useDefaultBase = true) {
        visual = _visual;
        
        std::string fragFilename = shaderName + ".frag";
        std::string vertFilename = useDefaultBase ? "Base.frag" : shaderName + ".vert";
        
        shader.load(vertFilename, fragFilename);
    }
    void update() {
        visual->update();
        rect = visual->rect;
        
    }
    void draw() {
        draw(rect);
    }
    void draw(ofRectangle _rect) {
        shader.begin();
        for (auto parameter : floatParameters) {
            float value = parameter.second->getValue();
            shader.setUniform1f(parameter.first, value);
        }
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
    
    static VisualsInterface* GLSL(
                                  VisualsInterface *visual,
                                  std::string shaderName,
                                  bool useDefaultBase = true,
                                  std::map<std::string, Signal<float>*> _floatParameters = {}
                                  ) {
        GLSLTransformationDecorator *transformation = new GLSLTransformationDecorator(visual, shaderName, useDefaultBase);
        
        transformation->floatParameters = _floatParameters;
        return transformation;
    };
    
};


#endif

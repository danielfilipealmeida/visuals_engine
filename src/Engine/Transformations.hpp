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

using glslParameterType = std::variant<float*, Signal<float>*>;

/// \brief A Visual Interface Decorator that wraps a visual around a GLSL shader
class GLSLTransformationDecorator : public VisualsInterface {
public:

    VisualsInterface *visual;
    ofShader shader;

    std::map<std::string, glslParameterType> floatParameters;
    std::vector<string> parameterNames;
    
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
    
    /// \brief Draws the shader around the decorated visua
    void draw() {
        draw(rect);
    }
    
    /// \brief Draws the shader around the decorated visual in a rect
    /// \param _rect - the rectangular area where to draw the decorated visual
    void draw(ofRectangle _rect) {
        shader.begin();
        for (auto parameter : floatParameters) {
            float value;
            
            /// gets the actual value for the parameter
            if (std::holds_alternative<Signal<float>*>(parameter.second)) {
                Signal<float>* signalPtr = std::get<Signal<float>*>(parameter.second);
                value = signalPtr->getValue();
            }
            if (std::holds_alternative<float*>(parameter.second)) {
                float *parameterFloat = std::get<float*>(parameter.second);
                value = *(parameterFloat);
            }
            
            shader.setUniform1f(parameter.first, value);
        }
        visual->draw(_rect);
        shader.end();
    }
    
    /// \brief Sets the value of a float parameter
    /// \param parameter - a string naming the parameter
    /// \param value - the float value
    void setParameter(string parameterName, float value) {
        floatParameters[parameterName] = &value;
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
                                  std::map<std::string, glslParameterType> _floatParameters = {}
                                  ) {
        GLSLTransformationDecorator *transformation = new GLSLTransformationDecorator(visual, shaderName, useDefaultBase);
        
        transformation->floatParameters = _floatParameters;
        return transformation;
    };
    
};


#endif

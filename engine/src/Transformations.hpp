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
#include "Utils.hpp"

using glslParameterType = std::variant<float*, Signal<float>*>;

/// \brief A Visual Interface Decorator that wraps a visual around a GLSL shader
///
/// \details Implements a ping-pong FBO shader pipeline in order to apply a variable set of shaders to the decorated visual
class GLSLTransformationDecorator : public VisualsInterface {
public:
    
    /// \var visual
    /// \brief decorated visual
    VisualsInterface *visual;
    
    /// \var shaders
    /// \brief vector containing all loaded shaders
    std::vector<ofShader> shaders;
    
    /// \var shadersParameters
    /// \brief vector with configured parameters for each shader
    /// \details A vector of a map. Each entry in the vector is the set of configured parameters for the shader with the same index in the `shaders` vector. Each `second` value in the map is a pointer to a state variable, where the `first` value is the actual shader variable.
    std::vector<std::map<std::string, glslParameterType>> shadersParameters;
    
    ofFbo ping, pong;
    ofFbo* src;
    ofFbo* dst;
    
    /// \brief Initialize the decorator and loads the shaders
    ///
    /// \brief Sets up the internal FBOs for the ping-pong pipelne and loads the shaders
    ///
    /// \param _visual - decorated visual
    /// \param _shaderNames - the names of all shaders to load into the decorator
    GLSLTransformationDecorator(VisualsInterface *_visual, std::vector<std::string> shaderNames) {
        visual = _visual;
        rect = visual->rect;
        
        // sets up FBOs
        setupPipeline(_visual);
        
        // loads all shaders
        for(std::string shaderName: shaderNames) {
            loadShader(shaderName);
        }
    }
    
    
    /// \brief Loads a shader by its name
    ///
    /// \param shaderName - the filename without extension for the shader files.
    ///
    /// \details Will load vert and frag files by concatonating the extensions and looking for files inside the `data/` folder. if no `.vert` file exists, will use the `base.vert` file.
    void loadShader(std::string shaderName) {
        std::string fragFilename = shaderName + ".frag";
        std::string vertFilename = shaderName + ".vert";
        if (!checkFileExistsInData(vertFilename)) {
            ofLog(OF_LOG_WARNING, "Shader Vert file %s does not exist. Using Base.vert.", vertFilename.c_str());
            vertFilename = "Base.vert";
        }
        
        ofShader shader;
        shader.load(vertFilename, fragFilename);
        shaders.push_back(shader);
    }
    
    
    /// \brief Sets the Ping-Pong buffers
    ///
    /// \param _visual - the decorated visual
    void setupPipeline(VisualsInterface *_visual) {
        ofFbo::Settings settings;
        settings.width = _visual->rect.width;
        settings.height = _visual->rect.height;
        settings.internalformat = GL_RGBA;
        settings.useDepth = false;
        
        ping.allocate(settings);
        pong.allocate(settings);
    }
    
    /// \brief apply the parameters to the shader
    ///
    /// \param index - the index in the `shaders` vector where the shader is stored
    void applyParametersToShader(size_t index) {
        std::map<std::string, glslParameterType> floatParameters = shadersParameters[index];
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
            
            shaders[index].setUniform1f(parameter.first, value);
        }
    }
    
    /// \brief updates the decorated visual
    ///
    /// \details applies the ping-ping shader pipeline to the decorated visual. Will apply all visuals from top to bottom, which means the last shader is the one on top.
    void update() {
        visual->update();
        
        src = &ping;
        dst = &pong;
        
        src->begin();
        ofClear(0,0,0,255);
        visual->draw(rect);
        src->end();
        
        for(size_t i = 0; i < shaders.size(); i++) {
            dst->begin();
            ofClear(0,0,0,255);
            
            shaders[i].begin();
            applyParametersToShader(i);
            src->draw(0,0);
            shaders[i].end();
            
            dst->end();
            
            std::swap(src, dst);
        }
    }
    
    /// \brief Draws the shader around the decorated visual
    void draw() {
        draw(rect);
    }
    
    /// \brief Draws the shaders in the vector around the decorated visual in a rect
    /// \param _rect - the rectangular area where to draw the decorated visual
    void draw(ofRectangle _rect) {
        src->draw(_rect);
       
    }
    
    /// \brief Sets the value of a float parameter
    ///
    /// \param shaderIndex - the index of the shader in the vector
    /// \param parameter - a string naming the parameter
    /// \param value - the float value
    void setParameter(unsigned int shaderIndex, string parameterName, float value) {
        shadersParameters[shaderIndex][parameterName] = &value;
    }
    
    
    /// \brief empty because it isn't needed
    void play() {}
    
    /// \brief empty because it isn't needed
    void stop() {}
    
    /// \brief Encode the data of the transformation into a json
    ofJson encode() {
        return {};
    }
};


/// \brief Factory class for generating transformation decorators
class TransformationFactory {
public:
    
    /// \brief construct a decortaror around a VisualInterface that contains a list of shaders
    ///
    /// \details If a visual interface needs shaders, all should be set in this decorator
    ///
    /// \param visual - the visual to be decorated
    /// \param shaderNames - the names of the shaders in a vector. the names must match the shader filenames. if the .vert file doesn't exist, use the template in base.vert
    /// \param _floatParametersPerShader
    ///
    /// \return VisualInterface* a new Visual interface containing the shaders and the decorated visual interface
    static VisualsInterface* GLSL(
                                  VisualsInterface *visual,
                                  std::vector<std::string> shaderNames,
                                  std::vector<std::map<std::string, glslParameterType>> _shadersParameters = {}
                                  ) {
        GLSLTransformationDecorator *transformation = new GLSLTransformationDecorator(visual, shaderNames);
        
        transformation->shadersParameters = _shadersParameters;
        
        return transformation;
    };
    
};


#endif

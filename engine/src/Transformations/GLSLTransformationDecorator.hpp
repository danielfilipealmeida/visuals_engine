//
//  GLSLTransformationDecorator.hpp
//  Engine
//
//  Created by Daniel Almeida on 27/07/2025.
//

#ifndef GLSLTransformationDecorator_hpp
#define GLSLTransformationDecorator_hpp

#include "Visuals.hpp"
#include "Signals.hpp"
#include "Utils.hpp"


///  \brief defines the type for the running shaders
///  \details this type is used to connect signals end variables to the shader and to do 2-way binding
using GLSLDataInputParameterType = std::variant<float*, Signal<float>*>;

/// \brief defines the type of a glsl parmeter definition
/// \details this is used on the GLSL catalogue to specifty each filter
using GLSLParamDefinitionType = std::variant<int, float>;


/// \brief defines the possible types of glsl  variab
enum GLSLType {
    INT,
    FLOAT
};

/// \brief definition of the data of a GLSL shader uniform input variable
struct GLSLParameterDefinition {
    string var;
    string name;
    GLSLType type;
    GLSLParamDefinitionType min;
    GLSLParamDefinitionType max;
    GLSLParamDefinitionType _default;
};

/// \brief all shader parameters definitions
using GLSLShaderParameters = std::vector<GLSLParameterDefinition>;

/// \brief all shaders definitions
using GLSLShadersDefinitions = std::map<string, GLSLShaderParameters>;


/// \brief Definition of all Engine GLSL shaders and its parameters
extern GLSLShadersDefinitions glslShaders;

/// todo: create a way to allow for user-defined shaders and how to extract the information from the shaders


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
    std::vector<std::map<std::string, GLSLDataInputParameterType>> shadersParameters;
    
    ofFbo ping, pong;
    ofFbo* src;
    ofFbo* dst;
    
    /// \brief Initialize the decorator and loads the shaders
    ///
    /// \brief Sets up the internal FBOs for the ping-pong pipelne and loads the shaders
    ///
    /// \param _visual - decorated visual
    /// \param _shaderNames - the names of all shaders to load into the decorator
    GLSLTransformationDecorator(VisualsInterface *_visual, std::vector<std::string> shaderNames);
    
    
    /// \brief Loads a shader by its name
    ///
    /// \param shaderName - the filename without extension for the shader files.
    ///
    /// \details Will load vert and frag files by concatonating the extensions and looking for files inside the `data/` folder. if no `.vert` file exists, will use the `base.vert` file.
    void loadShader(std::string shaderName);
    
    
    /// \brief Sets the Ping-Pong buffers
    ///
    /// \param _visual - the decorated visual
    void setupPipeline(VisualsInterface *_visual);
    
    
    /// \brief apply the parameters to the shader
    ///
    /// \param index - the index in the `shaders` vector where the shader is stored
    void applyParametersToShader(size_t index);
    
    
    /// \brief updates the decorated visual
    ///
    /// \details applies the ping-ping shader pipeline to the decorated visual. Will apply all visuals from top to bottom, which means the last shader is the one on top.
    void update();
    
    
    /// \brief Draws the shader around the decorated visual
    void draw();
    
    /// \brief Draws the shaders in the vector around the decorated visual in a rect
    /// \param _rect - the rectangular area where to draw the decorated visual
    void draw(ofRectangle _rect);
    
    /// \brief Sets the value of a float parameter
    ///
    /// \param shaderIndex - the index of the shader in the vector
    /// \param parameterName - a string naming the parameter
    /// \param value - the float value
    void setParameter(unsigned int shaderIndex, string parameterName, float value);
    
    /// \brief empty because it isn't needed
    void play();
    
    
    /// \brief empty because it isn't needed
    void stop();
    
    /// \brief Encode the data of the transformation into a json
    ofJson encode();
    
    /// \brief Decode the data and set the object
    void decode(ofJson json);
};

#endif /* GLSLTransformationDecorator_hpp */

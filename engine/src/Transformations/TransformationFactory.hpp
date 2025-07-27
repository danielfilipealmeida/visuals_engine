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
#include "GLSLTransformationDecorator.hpp"




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
                                  std::vector<std::map<std::string, GLSLDataInputParameterType>> _shadersParameters = {}
                                  ) {
        GLSLTransformationDecorator *transformation = new GLSLTransformationDecorator(visual, shaderNames);
        
        transformation->shadersParameters = _shadersParameters;
        
        return transformation;
    };
    
};


#endif

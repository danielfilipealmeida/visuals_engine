//
//  GLSLTransformationDecorator.cpp
//  Engine
//
//  Created by Daniel Almeida on 27/07/2025.
//

#include "GLSLTransformationDecorator.hpp"


GLSLShadersDefinitions glslShaders = {
    {"RGBTint", {
        {"redTint", "Red Tint", GLSLType::FLOAT, 0, 2, 1},
        {"greenTint", "Green Tint", GLSLType::FLOAT, 0, 2, 1},
        {"blueTint", "Blue Tint", GLSLType::FLOAT, 0, 2, 1}
    }},
    {"ContrastBrightnessSaturation", {
        {"brightness", "Brightness", GLSLType::FLOAT, 0, 2, 1},
        {"contrast", "Contrast", GLSLType::FLOAT, 0, 2, 1},
        {"saturation", "Saturation", GLSLType::FLOAT, 0, 2, 1}
    }},
    {"FastBlur", {
        {"blurH", "Horizontal Blur", GLSLType::FLOAT, 0, 32, 0},
        {"blurV", "Vertical Blur", GLSLType::FLOAT, 0, 32, 0}
    }}
};


GLSLTransformationDecorator::GLSLTransformationDecorator(VisualsInterface *_visual, std::vector<std::string> shaderNames) {
    visual = _visual;
    rect = visual->rect;
    
    // sets up FBOs
    setupPipeline(_visual);
    
    // loads all shaders
    for(std::string shaderName: shaderNames) {
        loadShader(shaderName);
    }
}



void GLSLTransformationDecorator::loadShader(std::string shaderName) {
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



void GLSLTransformationDecorator::setupPipeline(VisualsInterface *_visual) {
    ofFbo::Settings settings;
    settings.width = _visual->rect.width;
    settings.height = _visual->rect.height;
    settings.internalformat = GL_RGBA;
    settings.useDepth = false;
    
    ping.allocate(settings);
    pong.allocate(settings);
}


void GLSLTransformationDecorator::applyParametersToShader(size_t index) {
    std::map<std::string, GLSLDataInputParameterType> floatParameters = shadersParameters[index];
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


void GLSLTransformationDecorator::update() {
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


void GLSLTransformationDecorator::draw() {
    draw(rect);
}


void GLSLTransformationDecorator::draw(ofRectangle _rect) {
    src->draw(_rect);
    
}


void GLSLTransformationDecorator::setParameter(unsigned int shaderIndex, string parameterName, float value) {
    shadersParameters[shaderIndex][parameterName] = &value;
}



void GLSLTransformationDecorator::play() {}


void GLSLTransformationDecorator::stop() {}

ofJson GLSLTransformationDecorator::encode() {
    return {};
}


void GLSLTransformationDecorator::decode(ofJson json){}


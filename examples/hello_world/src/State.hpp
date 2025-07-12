//
//  State.hpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 05/07/2025.
//

#ifndef State_h
#define State_h

#include "Set.hpp"
#include "Transformations.hpp"


/// \brief Stores the state of the application.
struct State {
    
#pragma mark State external references
    
    Set *set;
    float bufferWidth;
    float bufferHeight;
    
#pragma mark State variables
    
    float blurAmount;
    float contrast;
    float saturation;
    float brightness;
    
    float redTint, blueTint, greenTint;
    
#pragma mark Main Visuals
    
    LayerStack *layerStackA, *layerStackB;
    Mixer *mixer;
    Signal<float> signal1, signal2;
    
    
#pragma mark Methods
    
    /// \brief Sets up the state and initialize all visual eleme
    ///
    /// \param bufferWidth - the width for the visuals buffer
    /// \param bufferHeight - the height of the visuals buffer
    void setup(
               Set* set,
               float bufferWidth,
               float bufferHeight
               ) {
        
        this->set = set;
        this->bufferWidth = bufferWidth;
        this->bufferHeight = bufferHeight;
        
        signal1 = SignalsFactory::SineWave();
        signal2 = SignalsFactory::Random(10, 1);
        
        layerStackA = new LayerStack(bufferWidth, bufferHeight);
        layerStackA->insert(new Layer(set->visuals[0]));
        
        layerStackB = new LayerStack(bufferWidth, bufferHeight);
        layerStackB->insert(new Layer(set->visuals[1]));
        
        contrast = -0.5;
        saturation = -0.5;
        brightness = 10;
        
        redTint = 0.1;
        blueTint= 1;
        greenTint = 1;
        
        mixer = new Mixer(
                          TransformationFactory::GLSL(
                                                      layerStackA,
                                                      { "LayerShader", "FastBlur", "RGBTint"},
                                                      {
                                                          {
                                                          {"contrast", &contrast},
                                                          {"saturation", &saturation},
                                                          {"brightness", &brightness}
                                                          
                                                          },
                                                          {
                                                          {"blurH", &blurAmount},
                                                          {"blurV", &blurAmount}
                                                          },
                                                      
                                                          {
                                                          
                                                          {"redTint", &redTint},
                                                          {"greenTint", &greenTint},
                                                          {"blueTint", &blueTint}
                                                          
                                                          }
                                                      
                                                      }
                                                      
                                                      ),
                          layerStackB,
                          bufferWidth, bufferHeight);
        
        mixer->setMix(0.5);
        
        signal1.regist(mixer, mixer->parameters[MixerObservableParameters::MIX]);
        
    }
    
    /// \brief Update everything in the state
    void update() {
        mixer->update();
        signal1.update();
        signal2.update();
    }
};

#endif /* State_h */

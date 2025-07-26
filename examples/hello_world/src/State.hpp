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
#include "LayerStack.hpp"
#include "VisualsFactory.hpp"
#include "Mixer.hpp"

enum Channel {
    A,
    B
};


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
    VisualsInterface *decoratedMixer;
    Signal<float> signal1, signal2;
    
    Channel selectedChannel = Channel::A;
    unsigned int selectedLayer = 0;
    
    
#pragma mark Methods
    
    ~State();
    
    /// \brief Sets up the state and initialize all visual eleme
    ///
    /// \param bufferWidth - the width for the visuals buffer
    /// \param bufferHeight - the height of the visuals buffer
    void setup(
               Set* set,
               float bufferWidth,
               float bufferHeight
               );
    
    /// \brief Update everything in the state
    void update();
    
    /// \brief Triggers a visual on the current selected channel/layer
    ///
    /// \param visual - the visual to play
    void triggerVisualAtSelectedLayer(VisualsInterface *visual);
    
    /// \brief Saves the State into a json file inside the data folder
    ///
    /// \param filename - the json filename. needs the .json extension.
    void save(of::filesystem::path filename);
    
    
    /// \brief Loads a State stored in a Json file inside the data folder
    ///
    /// \param filename - the json filename to load. needs the json extension.
    void load(of::filesystem::path filename);
    
    
    /// \brief adds the default set files to the state
    void defaultSet();
    
    /// \brief update the visuals on a channel
    ///
    /// \param channel - the LayerStack that implements the channel
    /// \param layersJson - the subset of the json defining the layers in the layerStack
    void setPlayingVisualsInChannel(LayerStack *channel, ofJson layersJson);
    



};

#endif /* State_h */

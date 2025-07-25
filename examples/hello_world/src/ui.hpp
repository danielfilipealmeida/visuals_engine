//
//  ui.hpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 09/07/2025.
//

#ifndef ui_h
#define ui_h

#include "ofxGui.h"
#include "State.hpp"
#include "DrawableGuiElement.hpp"
#include "Mixer.hpp"

/// \brief Implements a centralized two-way binding mechanism for binding GUI parameters with states variables
///
/// \details This successully allows the update of the app states by the GUI parameters, as well as the update of the GUI paremeters when the state changes via other means (i.e MIDI)
template<typename T>
class ParameterBinder {
public:
    ParameterBinder(ofParameter<T>& param, T* target) : param(param), target(target), lastSyncedValue(*target) {
        param.addListener(this, &ParameterBinder::onChangeParameter);
    }
    
    ~ParameterBinder() {
        param.removeListener(this, &ParameterBinder::onChangeParameter);
    }
    
    void onChangeParameter(T& newValue) {
        *target = newValue;
        lastSyncedValue = newValue;
    }
    
    void sync() {
        if(*target != lastSyncedValue) {
            param = *target;
            lastSyncedValue = *target;
        }
    }
    
private:
    ofParameter<T>& param;
    T* target;
    T lastSyncedValue;
};


/// \brief Implements the UI of the application using the ofxGui addon
class ui {
    shared_ptr<State> state;
    ofxPanel previewsPanel, audiAndFFTPanel, mainOptionsPanel, channelsPanel;
    std::vector<std::pair<string, VisualsInterface *>> additionalVisuals;
    
    ofxLabel channelALabel, channelBLabel;
    
    ofParameter<float> blur;
    ofParameter<float> mix;
    ofParameter<float> brightness, contrast, saturation;
    ofParameter<float> redTint, greenTint, blueTint;
    
    std::vector<std::unique_ptr<ParameterBinder<float>>> binders;

    float panelsWidth = 192;
    float panelsMargin = 8;
public:
    ui() {};
    
    void setup(shared_ptr<State> state, std::vector<std::pair<string, VisualsInterface *>> additionalVisuals) {
        this->state = state;
        this->additionalVisuals = additionalVisuals;
        
        // setup mixer and channels previews
        previewsPanel.setup("Previews", "previewPanelConfig");
        previewsPanel.setWidthElements(panelsWidth);
        previewsPanel.setPosition(panelsMargin, panelsMargin);
        previewsPanel.add(new DrawableGuiElement<Mixer *>(this->state->mixer, "Mixer"));
        previewsPanel.add(new DrawableGuiElement<VisualsInterface *>(this->state->mixer->a, "Channel A"));
        previewsPanel.add(new DrawableGuiElement<VisualsInterface *>(this->state->mixer->b, "Channel B"));
        
        
        // Channels previews
        channelsPanel.setup("Channels Previews", "channelsPreviewsConfig");
        channelsPanel.setWidthElements(panelsWidth);
        channelsPanel.setPosition(panelsMargin*2 + panelsWidth, panelsMargin);
        
        unsigned int layerInChannelA = ((LayerStack*)this->state->mixer->a)->layers.size();
        channelsPanel.add(channelALabel.setup("Channel A", ofToString(layerInChannelA) + " Layers"));
        unsigned int count = 1;
        for (Layer *layer : ((LayerStack*)this->state->mixer->a)->layers) {
            channelsPanel.add(new DrawableGuiElement<VisualsInterface *>(layer , "Channel A / Layer " + ofToString(count)));
            
            count++;
        }
        
        unsigned int layerInChannelB = ((LayerStack*)this->state->mixer->b)->layers.size();
        channelsPanel.add(channelBLabel.setup("Channel B", ofToString(layerInChannelB) + " Layers"));
        count = 1;
        for (Layer *layer : ((LayerStack*)this->state->mixer->b)->layers) {
            channelsPanel.add(new DrawableGuiElement<VisualsInterface *>(layer , "Channel B / Layer " + ofToString(count)));
            
            count++;
        }
        
        // add additional plots
        audiAndFFTPanel.setup("Audio and FFT", "audioAndFFTConfig");
        audiAndFFTPanel.setWidthElements(panelsWidth);
        audiAndFFTPanel.setPosition(panelsMargin*3 + panelsWidth * 2, panelsMargin);
        for(std::pair<string, VisualsInterface *> plot : this->additionalVisuals) {
            audiAndFFTPanel.add(new DrawableGuiElement<VisualsInterface *>(plot.second, plot.first));
        }
        
        
        // setup. needs a listener to update the state
        mainOptionsPanel.setup("Attributes", "attributesConfig");
        mainOptionsPanel.setWidthElements(panelsWidth);
        mainOptionsPanel.setPosition(panelsMargin*4 + panelsWidth * 3, panelsMargin);
       
        // Blur
        mainOptionsPanel.add(blur.set("blur", 0, 0, 10));
        binders.emplace_back(std::make_unique<ParameterBinder<float>>(blur, &this->state->blurAmount));
        
        // Mix
        mainOptionsPanel.add(mix.set("mix", this->state->mixer->mix, -1, 1));
        binders.emplace_back(std::make_unique<ParameterBinder<float>>(mix, &this->state->mixer->mix));
        
        // Brightness
        mainOptionsPanel.add(brightness.set("brightness", 1, 0, 2));
        binders.emplace_back(std::make_unique<ParameterBinder<float>>(brightness, &this->state->brightness));
        
        // Contrast
        mainOptionsPanel.add(contrast.set("contrast", 1, 0, 2));
        binders.emplace_back(std::make_unique<ParameterBinder<float>>(contrast, &this->state->contrast));
        
        // Saturation
        mainOptionsPanel.add(saturation.set("saturation", 1, 0, 2));
        binders.emplace_back(std::make_unique<ParameterBinder<float>>(saturation, &this->state->saturation));
        
        // Red Tint
        mainOptionsPanel.add(redTint.set("red Tint", 1, 0, 2));
        binders.emplace_back(std::make_unique<ParameterBinder<float>>(redTint, &this->state->redTint));
        
        // Green Tint
        mainOptionsPanel.add(greenTint.set("green Tint", 1, 0, 2));
        binders.emplace_back(std::make_unique<ParameterBinder<float>>(greenTint, &this->state->greenTint));
        
        // Blue Tint
        mainOptionsPanel.add(blueTint.set("blue Tint", 1, 0, 2));
        binders.emplace_back(std::make_unique<ParameterBinder<float>>(blueTint, &this->state->blueTint));
    }
    
    
    void draw() {
        for (auto& b : binders) b->sync();
        
        // draw
        previewsPanel.draw();
        channelsPanel.draw();
        audiAndFFTPanel.draw();
        mainOptionsPanel.draw();
    }
    
};


#endif /* ui_h */

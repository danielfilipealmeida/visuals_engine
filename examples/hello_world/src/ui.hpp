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
    ofxPanel previewsPanel, audiAndFFTPanel, mainOptionsPanel;
    std::vector<std::pair<string, VisualsInterface *>> additionalVisuals;
    
    ofParameter<float> blur;
    ofParameter<float> mix;
    ofParameter<float> brightness, contrast, saturation;
    
    std::vector<std::unique_ptr<ParameterBinder<float>>> binders;

    float panelsWidth = 256;
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
        
        // add additional plots
        audiAndFFTPanel.setup("Audio and FFT", "audioAndFFTConfig");
        audiAndFFTPanel.setWidthElements(panelsWidth);
        audiAndFFTPanel.setPosition(panelsMargin*2 + panelsWidth, panelsMargin);
        for(std::pair<string, VisualsInterface *> plot : this->additionalVisuals) {
            audiAndFFTPanel.add(new DrawableGuiElement<VisualsInterface *>(plot.second, plot.first));
        }
        
        
        // setup. needs a listener to update the state
        mainOptionsPanel.setup("Attributes", "attributesConfig");
        mainOptionsPanel.setWidthElements(panelsWidth);
        mainOptionsPanel.setPosition(panelsMargin*3 + panelsWidth * 2, panelsMargin);
       
        // Blur
        mainOptionsPanel.add(blur.set("blur", 0, 0, 10));
        binders.emplace_back(std::make_unique<ParameterBinder<float>>(blur, &this->state->blurAmount));
        
        // Mix
        mainOptionsPanel.add(mix.set("mix", this->state->mixer->mix, -1, 1));
        binders.emplace_back(std::make_unique<ParameterBinder<float>>(mix, &this->state->mixer->mix));
        
        // Brightness
        mainOptionsPanel.add(brightness.set("brightness", 0, 0, 1));
        binders.emplace_back(std::make_unique<ParameterBinder<float>>(brightness, &this->state->brightness));
        
        // Contrast
        mainOptionsPanel.add(contrast.set("contrast", 0, 0, 1));
        binders.emplace_back(std::make_unique<ParameterBinder<float>>(contrast, &this->state->contrast));
        
        // Saturation
        mainOptionsPanel.add(saturation.set("saturation", 0, 0, 1));
        binders.emplace_back(std::make_unique<ParameterBinder<float>>(saturation, &this->state->saturation));
    }
    
    
    void draw() {
        for (auto& b : binders) b->sync();
        
        // draw
        previewsPanel.draw();
        audiAndFFTPanel.draw();
        mainOptionsPanel.draw();
    }
    
};


#endif /* ui_h */

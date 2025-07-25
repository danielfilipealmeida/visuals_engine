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
    // Pointer-based constructor
    ParameterBinder(ofParameter<T>& param, T* target)
    : param(param), target(target), useFunctionBinding(false), lastSyncedValue(*target) {
        param.addListener(this, &ParameterBinder::onChangeParameter);
    }
    
    // Function-based constructor
    ParameterBinder(ofParameter<T>& param, std::function<T()> getter, std::function<void(T)> setter)
    : param(param), getter(getter), setter(setter), useFunctionBinding(true), lastSyncedValue(getter()) {
        param.addListener(this, &ParameterBinder::onChangeParameter);
    }
    
    ~ParameterBinder() {
        param.removeListener(this, &ParameterBinder::onChangeParameter);
    }
    
    void onChangeParameter(T& newValue) {
        if (useFunctionBinding && setter) {
            setter(newValue);
        } else if (target) {
            *target = newValue;
        }
        lastSyncedValue = newValue;
    }
    
    void sync() {
        T currentValue;
        if (useFunctionBinding && getter) {
            currentValue = getter();
        } else if (target) {
            currentValue = *target;
        } else {
            return;
        }
        
        if (currentValue != lastSyncedValue) {
            param = currentValue;
            lastSyncedValue = currentValue;
        }
    }
    
private:
    ofParameter<T>& param;
    T* target = nullptr;
    std::function<T()> getter;
    std::function<void(T)> setter;
    bool useFunctionBinding = false;
    T lastSyncedValue;
};


/// \brief Implements the UI of the application using the ofxGui addon
class ui {
    shared_ptr<State> state;
    ofxPanel previewsPanel, audiAndFFTPanel, mainOptionsPanel, channelsPanel;
    std::vector<std::pair<string, VisualsInterface *>> additionalVisuals;
    
    ofxLabel channelALabel, channelBLabel;
    
    
    // Attributes
    ofParameter<float> blur;
    ofParameter<float> mix;
    ofParameter<float> brightness, contrast, saturation;
    ofParameter<float> redTint, greenTint, blueTint;
    
    // the binders - for 2-way binding
    std::vector<std::unique_ptr<ParameterBinder<float>>> floatBinders;
    std::vector<std::unique_ptr<ParameterBinder<int>>> intBinders;

    // layer parameters
    std::vector<ofParameter<float>> channeAAlpha;
    std::vector<ofParameter<float>> channelBAlpha;
    std::vector<ofParameter<int>> channelABlendMode;
    std::vector<ofParameter<int>> channelBBlendMode;
    
        
    
    
    float panelsWidth = 192;
    float panelsMargin = 8;
public:
    ui() {};
    
    /// \brief sets up the UI and create all parameters
    ///
    /// \param state - the current state of the application
    /// \param additionalVisuals - ???
    void setup(
               shared_ptr<State> state,
               std::vector<std::pair<string, VisualsInterface *>> additionalVisuals
               );
    
    
    /// \brief Draw the UI
    void draw();
    
};


#endif /* ui_h */

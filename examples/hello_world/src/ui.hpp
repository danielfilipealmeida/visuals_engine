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

class ui {
    shared_ptr<State> state;
    ofxPanel previewsPanel, audiAndFFTPanel, mainOptionsPanel;
    ofParameter<float> blur;
    ofParameter<float> mix;
    
    std::vector<std::pair<string, VisualsInterface *>> additionalVisuals;

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
        mainOptionsPanel.add(blur.set("blur", 0, 0, 10));
        blur.addListener(this, &ui::onBlurChanged);
        
        mainOptionsPanel.add(mix.set("mix", 0, -1, 1));
        mix.addListener(this, &ui::onMixChanged);
    }
    
    
    void draw() {
        // manually sync the parameters
        blur.set(this->state->blurAmount);
        mix.set(this->state->mixer->mix);
        
        // draw
        previewsPanel.draw();
        audiAndFFTPanel.draw();
        mainOptionsPanel.draw();
    }
    
    void onBlurChanged(float& value) {
        this->state->blurAmount = value;
    }
    
    void onMixChanged(float& value) {
        this->state->mixer->mix = value;
    }
    
};


#endif /* ui_h */

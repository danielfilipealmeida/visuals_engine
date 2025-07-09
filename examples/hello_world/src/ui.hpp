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
    ofxPanel gui;
    ofParameter<float> blur;
    ofParameter<float> mix;
    
    std::vector<std::pair<string, VisualsInterface *>> additionalVisuals;

public:
    ui() {};
    
    void setup(shared_ptr<State> state, std::vector<std::pair<string, VisualsInterface *>> additionalVisuals) {
        this->state = state;
        this->additionalVisuals = additionalVisuals;
        
        gui.setup();
        
        // setup mixer and channels previews
        gui.add(new DrawableGuiElement<Mixer *>(this->state->mixer, "Mixer"));
        gui.add(new DrawableGuiElement<VisualsInterface *>(this->state->mixer->a, "Channel A"));
        gui.add(new DrawableGuiElement<VisualsInterface *>(this->state->mixer->b, "Channel B"));
        
        // add additional plots
        for(std::pair<string, VisualsInterface *> plot : this->additionalVisuals) {
            gui.add(new DrawableGuiElement<VisualsInterface *>(plot.second, plot.first));
        }
        
        
        // setup. needs a listener to update the state
        gui.add(blur.set("blur", 0, 0, 10));
        blur.addListener(this, &ui::onBlurChanged);
        
        gui.add(mix.set("mix", 0, -1, 1));
        mix.addListener(this, &ui::onMixChanged);
    }
    
    
    void draw() {
        // manually sync the parameters
        blur.set(this->state->blurAmount);
        mix.set(this->state->mixer->mix);
        
        // draw
        gui.draw();
    }
    
    void onBlurChanged(float& value) {
        this->state->blurAmount = value;
    }
    
    void onMixChanged(float& value) {
        this->state->mixer->mix = value;
    }
    
};


#endif /* ui_h */

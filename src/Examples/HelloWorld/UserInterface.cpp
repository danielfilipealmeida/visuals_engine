//
//  UserInterface.cpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 02/02/2025.
//

#include "UserInterface.hpp"

void UserInterface::setup(
                          ofRectangle rect,
                          Mixer *mixer,
                          Signal<float> *signal1,
                          Signal<float> *signal2,
                          State *state
                          ) {
    this->state = state;
    
    horizontalSplitter.addColumn(UI::CREATE<UI::Container>({
        new UI::Viewer<Mixer>(mixer, "Mixer", 100),
        new UI::Viewer<LayerStack>((LayerStack*) mixer->a, "A", 100),
        new UI::Viewer<LayerStack>((LayerStack*) mixer->b, "B", 100)
        
    }), 0.33);
    
    horizontalSplitter.addColumn(UI::CREATE<UI::Container>({

        new UI::Slider(
                       "Sinewave Signal",
                       0.0,
                       0.0,
                       1.0,
                       [](UI::Element *element) {
                           UI::Slider* slider = static_cast<UI::Slider*>(element);
                       }),
        
        new UI::Slider(
                       "Random Signal",
                       0.0,
                       0.0,
                       10.0,
                       [](UI::Element *element) {
                           UI::Slider* slider = static_cast<UI::Slider*>(element);
                       }),
        
        new UI::Slider(
                       "Blur Amount",
                       &state->blurAmount,
                       0.0,
                       10.0)
    }), 0.66);
    
    ui.rect = rect;
    ui.add(&horizontalSplitter);
    ui.calculate();
    
    
    signal1->setCallback([&](float value){
        UI::Slider *slider = ((UI::Slider *) horizontalSplitter.columns[1].first->children[0]);
        slider->setValue((value + 1) / 2.0);
    });
    
    signal2->setCallback([&](float value){
        UI::Slider *slider = ((UI::Slider *) horizontalSplitter.columns[1].first->children[1]);
        slider->setValue((value + 1) / 2.0);
    });
    
}

void UserInterface::draw()
{
    ui.draw();
}

void UserInterface::update() {
    ui.update(ofGetMouseX(),
              ofGetMouseY(),
              ofGetMousePressed(OF_MOUSE_BUTTON_1),
              ofGetMousePressed(OF_MOUSE_BUTTON_2)
    );
}

void UserInterface::resize(int width, int height) {
    ui.rect.width = width;
    ui.rect.height = height;
    ui.calculate();
}


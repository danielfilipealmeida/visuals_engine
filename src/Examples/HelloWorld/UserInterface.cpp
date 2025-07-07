//
//  UserInterface.cpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 02/02/2025.
//

#include "UserInterface.hpp"


void UserInterface::setupPreviews() {
   
    LayerStack* a = (LayerStack *) ((GLSLTransformationDecorator *) this->state->mixer->a)->visual;
    
    LayerStack* b = (LayerStack *) ((GLSLTransformationDecorator *) this->state->mixer->b);
    /*
    layersHorizontalSplitter->addColumn(UI::CREATE<UI::Container>({
        
    }), 50);
    layerCount = 1;
    for (Layer* layer: b->layers) {
        std::string label = "Layer " + std::to_string(layerCount);
        UI::Viewer<Layer> *layerViewer = new UI::Viewer<Layer>(layer, label, 100);
        ((UI::Container *) layersHorizontalSplitter->columns[1].first)->add(layerViewer);
        layerCount++;
    }
     */
    
    
    horizontalSplitter.addColumn(UI::CREATE<UI::Container>({
        new UI::Viewer<Mixer>(this->state->mixer, "Mixer", 256),
        new UI::Viewer<LayerStack>(a, "A", 256),
        new UI::Viewer<LayerStack>(b, "B", 256)
    }), 0.33);
    
    /*
    horizontalSplitter.addColumn(UI::CREATE<UI::Container>({
        new UI::Label("A")
    }), 0.16);
    */
    /*
    uint8 layerCount = 1;
    for (Layer* layer: a->layers) {
        std::string label = "Layer " + std::to_string(layerCount);
        UI::Viewer<Layer> *layerViewer = new UI::Viewer<Layer>(layer, label, 100);
        ((UI::Container *) horizontalSplitter.columns[1].first)->add(layerViewer);
        layerCount++;
        
    }
     */
}


void UserInterface::setup(
                          ofRectangle rect,
                          State *state
                          ) {
    this->state = state;
    
    setupPreviews();
    
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
    
    
    state->signal1.setCallback([&](float value){
        UI::Slider *slider = ((UI::Slider *) horizontalSplitter.columns[1].first->children[0]);
        slider->setValue((value + 1) / 2.0);
    });
    
    state->signal2.setCallback([&](float value){
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


#include "ofApp.h"
//#include "UI/Primitives.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
    layerStackA = new LayerStack(bufferWidth, bufferHeight);
    VisualsBuilder builder(bufferWidth, bufferHeight);
    layerStackA->insert(new Layer(builder.Video("001.mov")));
    layerStackA->insert(new Layer(builder.Video("002.mov")));
    
    layerStackB = new LayerStack(bufferWidth, bufferHeight);
    layerStackB->insert(new Layer(builder.Video("003.mov")));
    layerStackB->insert(new Layer(builder.Video("004.mov")));
    
    mixer = new Mixer(layerStackA, layerStackB, bufferWidth, bufferHeight);
    mixer->setMix(0.5);
    
    signal = SignalsBuilder::Random(1, 1);
    
    horizontalSplitter.addColumn([&]() {
        UI::Container *container = new UI::Container();
        container->add(new UI::Button(
                                    "test Button",
                                    [](UI::Element *element) {
                                        UI::Button* button = static_cast<UI::Button*>(element);
                                        std::cout << button->title <<endl;
                                    }));
        
        container->add([&](){
            auto element = new UI::Viewer<Mixer>(mixer, "Mixer");
            element->height = 200;
            return element;
        }());
         
        return container;
    }(), 0.5);
    horizontalSplitter.addColumn([&]() {
        UI::Container *container = new UI::Container();
        container->add(new UI::Button(
                                      "test Button",
                                      [](UI::Element *element) {
                                          UI::Button* button = static_cast<UI::Button*>(element);
                                          std::cout << button->title <<endl;
                                      }));
        container->add(new UI::VSpacer());
        container->add(new UI::Slider(
                                      "test Slider",
                                      0.5,
                                      0.0,
                                      1.0,
                                      [](UI::Element *element) {
                                          UI::Slider* slider = static_cast<UI::Slider*>(element);
                                          std::cout << slider->value << std::endl;
                                      })    );
        
        container->add(new UI::VSpacer());
        container->add(new UI::Slider(
                                      "test Slider",
                                      0.5,
                                      0.0,
                                      1.0,
                                      [](UI::Element *element) {
                                          UI::Slider* slider = static_cast<UI::Slider*>(element);
                                          std::cout << slider->value << std::endl;
                                      })    );
        
        return container;
    }(), 0.5);
    
    ui.rect = ofGetWindowRect();
    ui.add(&horizontalSplitter);
    /*
    ui.add(new UI::Button(
                          "test Button",
                          [](UI::Element *element) {
                              UI::Button* button = static_cast<UI::Button*>(element);
                              std::cout << button->title <<endl;
                          }));
    ui.add(new UI::Slider(
                          "test Slider",
                          0.5,
                          0.0,
                          1.0,
                          [](UI::Element *element) {
                              UI::Slider* slider = static_cast<UI::Slider*>(element);
                              std::cout << slider->value << std::endl;
                          }));
    mixCrossfader = new UI::CrossFader("Mix");
    ui.add(mixCrossfader);
    signal.setCallback([&](float value){
        mixCrossfader->setValue((value * 2) -1);
    });
    ui.add(new UI::TextBox("Test Textbox"));
    ui.add(new UI::Label("Test Label"));
     */
   
    ui.calculate();
}

//--------------------------------------------------------------
void ofApp::update(){
    mixer->update();
    signal.update();
    ui.update(ofGetMouseX(),
                ofGetMouseY(),
                ofGetMousePressed(OF_MOUSE_BUTTON_1),
                ofGetMousePressed(OF_MOUSE_BUTTON_2)
                );
}

//--------------------------------------------------------------
void ofApp::draw(){
    mixer->setMix(signal.getValue());
    mixer->draw(ofRectangle(0.0, 0.0, ofGetWidth(), ofGetHeight()));
    
    ui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    ui.rect = ofGetWindowRect();
    ui.calculate();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

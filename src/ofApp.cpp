#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //signal = SignalsBuilder::Random(1, 1);
    //signal = SignalsBuilder::Pulse();
    signal = SignalsFactory::SineWave();
    
    VisualsFactory factory(bufferWidth, bufferHeight);
    set.addVisual(factory.Video("001.mov"));
    set.addVisual(factory.Video("002.mov"));
    set.addVisual(factory.Video("003.mov"));
    set.addVisual(factory.Video("004.mov"));
    set.addVisual(factory.Plotter(&signal));
    
    layerStackA = new LayerStack(bufferWidth, bufferHeight);
    layerStackA->insert(new Layer(set.visuals[0]));
    //layerStackA->insert(new Layer(builder.Video("002.mov")));
    
    layerStackB = new LayerStack(bufferWidth, bufferHeight);
    layerStackB->insert(new Layer(set.visuals[4]));
    //layerStackB->insert(new Layer(builder.Video("003.mov")));
    //layerStackB->insert(new Layer(builder.Video("004.mov")));
    
    mixer = new Mixer(layerStackA, layerStackB, bufferWidth, bufferHeight);
    mixer->setMix(0.5);
    
    

    horizontalSplitter.addColumn(UI::CREATE<UI::Container>({
        new UI::Button(
                       "test Button",
                       [](UI::Element *element) {
                           UI::Button* button = static_cast<UI::Button*>(element);
                           std::cout << button->title <<endl;
                       }),
        new UI::Viewer<Mixer>(mixer, "Mixer", 100)
        
    }), 0.25);
                                 
    horizontalSplitter.addColumn(UI::CREATE<UI::Container>({
        new UI::Button(
                       "test Button",
                       [](UI::Element *element) {
                           UI::Button* button = static_cast<UI::Button*>(element);
                           std::cout << button->title <<endl;
                       }),
        new UI::VSpacer(),
        new UI::Slider(
                       "test Slider",
                       0.5,
                       0.0,
                       1.0,
                       [](UI::Element *element) {
                           UI::Slider* slider = static_cast<UI::Slider*>(element);
                           std::cout << slider->value << std::endl;
                       }),
        new UI::VSpacer(),
        new UI::Slider(
                       "test Slider",
                       0.5,
                       0.0,
                       1.0,
                       [](UI::Element *element) {
                           UI::Slider* slider = static_cast<UI::Slider*>(element);
                           std::cout << slider->value << std::endl;
                       })
    }), 0.25);
    
    ui.rect = ofGetWindowRect();
    ui.add(&horizontalSplitter);
    
    
    signal.setCallback([&](float value){
        UI::Slider *slider = ((UI::Slider *) horizontalSplitter.columns[1].first->children[2]);
        slider->setValue((value + 1) / 2.0);
    });
    
    
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
   
    /*
    ui.rect = ofGetWindowRect();
    ui.add(UI::CREATE<UI::Container>({
        new UI::Viewer<Mixer>(mixer, "Mixer"),
        new UI::Button(
                       "test Button",
                       [](UI::Element *element) {
                           UI::Button* button = static_cast<UI::Button*>(element);
                           std::cout << button->title <<endl;
                       })
    }));
      */
    ui.calculate();
    
    set.save("/Users/daniel/set.json");
    ofJson data = set.encode();
    set.decode(data);
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
    mixer->setMix(signal.getValue() + 1 /2.0);
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

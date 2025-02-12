#include "ofApp.h"
#include "Transformations.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
    //signal = SignalsBuilder::Random(1, 1);
    //signal = SignalsBuilder::Pulse();
    signal1 = SignalsFactory::SineWave();
    signal2 = SignalsFactory::Random(10, 1);
    
    VisualsFactory factory(bufferWidth, bufferHeight);
    set.addVisual(factory.Video("001.mov"));
    set.addVisual(factory.Video("002.mov"));
    set.addVisual(factory.Video("003.mov"));
    set.addVisual(factory.Video("004.mov"));
    set.addVisual(factory.Plotter(&signal1));
    
    layerStackA = new LayerStack(bufferWidth, bufferHeight);
    layerStackA->insert(new Layer(set.visuals[0]));
    layerStackA->insert(new Layer());
    
    layerStackB = new LayerStack(bufferWidth, bufferHeight);
    layerStackB->insert(new Layer(set.visuals[4]));
    
    mixer = new Mixer(
                      TransformationFactory::GLSL(
                                                  layerStackA,
                                                  "FastBlur",
                                                  true,
                                                  {
                                                    {"blurH", &signal2},
                                                    {"blurV", &signal2}
                                                  }
                                                  ),
                      layerStackB,
                      bufferWidth, bufferHeight);
    mixer->setMix(0.5);
    
    

    userInterface.setup(ofGetWindowRect(), mixer, &signal1, &signal2);
    
    signal1.regist(mixer, mixer->parameters[MixerObservableParameters::MIX]);
   
    
    /*
    set.save("/Users/daniel/set.json");
    ofJson data = set.encode();
    set.decode(data);
     */
}

//--------------------------------------------------------------
void ofApp::update(){
    mixer->update();
    signal1.update();
    signal2.update();
    
    userInterface.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    //mixer->setMix(signal1.getValue() + 1 /2.0);
    mixer->draw(ofRectangle(0.0, 0.0, ofGetWidth(), ofGetHeight()));
    
    userInterface.draw();
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
    userInterface.resize(w, h);

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

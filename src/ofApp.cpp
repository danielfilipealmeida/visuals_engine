#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    layerStackA = new LayerStack(bufferWidth, bufferHeight);
    VisualsBuilder builder(bufferWidth, bufferHeight);
    layerStackA->insert(new Layer(builder.Video("001.mov")));
    layerStackA->insert(new Layer(builder.Video("002.mov")));
    /*
    layerStack->insert(new Layer(builder.VideoGrabber(0)));
     */
    
    layerStackB = new LayerStack(bufferWidth, bufferHeight);
    layerStackB->insert(new Layer(builder.Video("003.mov")));
    layerStackB->insert(new Layer(builder.Video("004.mov")));
    
    mixer = new Mixer(layerStackA, layerStackB);
    mixer->setMix(0.5);
    
    signal = SignalsBuilder::Random(1, 1);
}

//--------------------------------------------------------------
void ofApp::update(){
    mixer->update();
    signal.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    mixer->setMix(signal.getValue());
    mixer->draw(ofRectangle(0.0, 0.0, ofGetWidth(), ofGetHeight()));
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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

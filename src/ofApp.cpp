#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    layerStack = new LayerStack(640, 480);
    VisualsBuilder builder(640, 480);
    layerStack->insert(new Layer(builder.Video("001.mov")));
    layerStack->insert(new Layer(builder.Video("002.mov")));
    /*
    layerStack->insert(new Layer(builder.VideoGrabber(0)));
     */
}

//--------------------------------------------------------------
void ofApp::update(){
    layerStack->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    layerStack->draw(ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
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

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //video = new Video("001.mp4");
    layerStack = new LayerStack();
    /*
    layer->insert(new Video("001.mov"));
    layer->insert(new Video("002.mov"));
    layer->insert(new Video("003.mov"));
     */
    layerStack->insert(new Layer(new Video("001.mov"), 1, OF_BLENDMODE_ADD));
    layerStack->insert(new Layer(new Video("002.mov"), 0.5, OF_BLENDMODE_ADD));
}

//--------------------------------------------------------------
void ofApp::update(){
    layerStack->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    layerStack->draw();
/*
 
 ofEnableAlphaBlending();
 
 for (auto layer:Layers::getInstance().getList()) {
 if (layer!=NULL) {
 ofSetColor(255, 255, 255, (int) (layer->getProperties()->getAlpha() * 255.0));
 ofEnableBlendMode((ofBlendMode) layer->getProperties()->getBlendMode());
 layer->draw(
 0,
 0,
 EngineProperties::getInstance().getMixerWidth(),
 EngineProperties::getInstance().getMixerHeight()
 );
 ofDisableBlendMode();
 }
 }
 ofDisableAlphaBlending();
 */
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

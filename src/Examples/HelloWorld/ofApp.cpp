#include "ofApp.h"
#include "Transformations.hpp"
#include "FFT.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
    bufferSize = 128;
    audioInput.resize(bufferSize);
    FFT::getInstance().setup(bufferSize);
    
    //signal = SignalsBuilder::Random(1, 1);
    //signal = SignalsBuilder::Pulse();
    signal1 = SignalsFactory::SineWave();
    signal2 = SignalsFactory::Random(10, 1);
    showInterface = true;
    
    VisualsFactory factory(bufferWidth, bufferHeight);
    set.addVisual(factory.Video("001.mov"));
    set.addVisual(factory.Video("002.mov"));
    set.addVisual(factory.Video("003.mov"));
    set.addVisual(factory.Video("004.mov"));
    set.addVisual(factory.Plotter(&audioInput));
    set.addVisual(factory.Plotter(&FFT::getInstance().audioBins));

    
    layerStackA = new LayerStack(bufferWidth, bufferHeight);
    layerStackA->insert(new Layer(set.visuals[4]));
    
    layerStackB = new LayerStack(bufferWidth, bufferHeight);
    layerStackB->insert(new Layer(set.visuals[5]));
    
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
    
   
    
    ofSoundStreamSettings settings;
    
    // if you want to set the device id to be different than the default
    // auto devices = soundStream.getDeviceList();
    // settings.device = devices[4];
    
    // you can also get devices for an specific api
    // auto devices = soundStream.getDevicesByApi(ofSoundDevice::Api::PULSE);
    // settings.device = devices[0];
    
    // or get the default device for an specific api:
    // settings.api = ofSoundDevice::Api::PULSE;
    
    // or by name
    auto devices = soundStream.getMatchingDevices("default");
    
    if(!devices.empty()){
        settings.setInDevice(devices[0]);
    }
     
    settings.setInListener(this);
    settings.sampleRate = 44100;
    settings.numInputChannels = 1;
    settings.bufferSize = bufferSize;
    settings.numBuffers = 1;
    soundStream.setup(settings);
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
    
    if (!showInterface) {
        return;
    }
     
    userInterface.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    cout << ofToString(key) <<endl;
    
    switch (key) {
    case 32:
        showInterface = !showInterface;
    }
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

void ofApp::audioIn( ofSoundBuffer& buffer ) {
    float curVol = 0.0;
    float maxValue = 0;
        
    for (size_t i = 0; i < buffer.getNumFrames(); i++){
        audioInput[i] = buffer[i];
    }
    FFT::getInstance().setSignal(audioInput);
}

/*
 void ofApp::audioIn( float * input, int bufferSize, int nChannels ) {
 
 }
 */

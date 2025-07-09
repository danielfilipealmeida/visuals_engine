#include "ofApp.h"

#include "FFT.hpp"
#include "MIDI.hpp"


void ofApp::setup(){
    ofSetVerticalSync(true);
    
    state = make_shared<State>();
    
    bufferSize = 128;
    audioInput.resize(bufferSize);
    FFT::getInstance().setup(bufferSize);
    
    showInterface = true;
   
    // todo: have this read from a file or a standard demo set generated elsewhere
    VisualsFactory factory(bufferWidth, bufferHeight);
    set.addVisual(factory.Video("001.mov"));
    set.addVisual(factory.Video("002.mov"));
    set.addVisual(factory.Video("003.mov"));
    set.addVisual(factory.Video("004.mov"));


    
    state->setup(&set, bufferWidth, bufferHeight);
    
    audioPlotter = factory.Plotter(&audioInput);
    fftPlotter = factory.Plotter(&FFT::getInstance().audioBins);
    
    
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
    
    // midi setup
    MIDI::getInstance().setup(0);
    //MIDI::getInstance().debug = true;
    MIDI::getInstance().regist((MIDIAction){
        MIDI_CONTROL_CHANGE,
        1,
        112,
        0
    }, [&](ofxMidiMessage message) {
        state->blurAmount = (message.value /127.0) * 10;
    });
    
    ui.setup(
             state,
             {
             {"Audio input", audioPlotter},
             {"FFT", fftPlotter}
             });
}

void ofApp::update(){
    state->update();
    audioPlotter->update();
    fftPlotter->update();
}

void ofApp::draw(){    
    state->mixer->draw(ofRectangle(0.0, 0.0, ofGetWidth(), ofGetHeight()));
    
    if (showInterface) {
        ui.draw();
    }
}
     
    
void ofApp::keyPressed(int key){

}

void ofApp::keyReleased(int key){
    cout << ofToString(key) <<endl;
    
    switch (key) {
    case 32:
        showInterface = !showInterface;
    }
}

void ofApp::mouseMoved(int x, int y){

}

void ofApp::mouseDragged(int x, int y, int button){

}


void ofApp::mousePressed(int x, int y, int button){

}

void ofApp::mouseReleased(int x, int y, int button){

}


void ofApp::mouseEntered(int x, int y){

}

void ofApp::mouseExited(int x, int y){

}

void ofApp::windowResized(int w, int h){


}

void ofApp::gotMessage(ofMessage msg){

}

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

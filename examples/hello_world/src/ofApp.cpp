#include "ofApp.h"

#include "FFT.hpp"
#include "MIDI.hpp"
#include "Keyboard.hpp"


void ofApp::setup(){
    ofSetVerticalSync(true);
    
    state = make_shared<State>();
    
    bufferSize = 128;
    audioInput.resize(bufferSize);
    FFT::getInstance().setup(bufferSize);
    
    showInterface = true;
    
    
    
    VisualsFactory& visualsFactory = VisualsFactory::getInstance();
    
    state->setup(&set, bufferWidth, bufferHeight);
    
    try {
        state->load("data.json");
    }
    catch (const std::exception &e) {
        ofLog(OF_LOG_ERROR, e.what());
        ofLog(OF_LOG_NOTICE, "Using Defaults instead.");
        state->defaultSet();
    }
    
    // Create the Plotters, used to view signals
    audioPlotter = visualsFactory.Plotter(&audioInput);
    fftPlotter = visualsFactory.Plotter(&FFT::getInstance().audioBins);
    signal1Plotter = visualsFactory.Plotter(&(state->signal1));
    signal2Plotter = visualsFactory.Plotter(&(state->signal2));
    signal2Plotter->visual.gain = 0.1;
    
    setupAudio();
    setupMIDI(false);
    
    ui.setup(
             state,
             {
             {"Audio input", audioPlotter},
             {"FFT", fftPlotter},
             {"Signal 1", signal1Plotter},
             {"Signasl 2", signal2Plotter}
             });
    
    setupKeys();
    
    state->save(currentFilename);
}


void ofApp::setupMIDI(bool debug) {
    MIDI::getInstance().setup(0);
    //MIDI::getInstance().debug = debug;
    MIDI::getInstance().regist((MIDIAction){
        MIDI_CONTROL_CHANGE,
        1,
        112,
        0
    }, [&](ofxMidiMessage message) {
        state->blurAmount = (message.value /127.0) * 10;
    });
}

void ofApp::setupAudio() {
    ofSoundStreamSettings settings;
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

void ofApp::setupKeys() {
    Keyboard::getInstance().debug = true;
    
    // assigns the keys used to trigger visuals on the selected channel and layer
    unsigned int index = 0;
    for (unsigned int key : Keyboard::getInstance().defaultVisualsTriggerKeys) {
        Keyboard::getInstance().add(key, [this, index](int key) {
            this->state->triggerVisualAtSelectedLayer(set.getVisualAtIndex(index));
        });
        
        index++;
    }
    
    index = 0;
    for (unsigned int key : Keyboard::getInstance().defaultLayersTriggerKeys) {
        Keyboard::getInstance().add(key, [this, index](int key) {
            this->state->selectedLayer = index;
        });
        
        index++;
    }
    
    index = 0;
    for (unsigned int key : Keyboard::getInstance().defaultChannelTriggerKey) {
        Keyboard::getInstance().add(key, [this, index](int key) {
            this->state->selectedChannel = (Channel) index;
        });
        
        index++;
    }
    
}

void ofApp::update(){
    state->update();
    audioPlotter->update();
    fftPlotter->update();
    signal1Plotter->update();
    signal2Plotter->update();
}

void ofApp::draw(){
    state->decoratedMixer->draw(ofRectangle(0.0, 0.0, ofGetWidth(), ofGetHeight()));
    
    if (showInterface) {
        ui.draw();
    }
}


void ofApp::keyPressed(int key){
    // handle keys with Control Key down
    if (keyCmdOn) {
        switch (key) {
            case Key::s:
                state->save(currentFilename);
                return;
                
        };
        
        return;
    }
    
    // handle no cmd key down
    switch (key) {
        case OF_KEY_COMMAND:
            keyCmdOn = true;
            return;
            break;
    }
    
    Keyboard::getInstance().handle(key);
}

void ofApp::keyReleased(int key){
    //cout << ofToString(key) <<endl;
    
    switch (key) {
        case OF_KEY_COMMAND:
            keyCmdOn = false;
            break;
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

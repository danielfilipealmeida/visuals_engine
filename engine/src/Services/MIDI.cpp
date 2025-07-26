//
//  MIDI.cpp
//  Engine
//
//  Created by Daniel Almeida on 26/07/2025.
//

#include "MIDI.hpp"
#include "ofMain.h"


MIDI::MIDI() {
    ofLog(OF_LOG_NOTICE, "MIDI Singleton instanciated");
    //midiIn.listInPorts();
}

MIDI::~MIDI() {
    ofLog(OF_LOG_NOTICE, "MIDI Singleton destruction");
    midiIn.closePort();
}


MIDI& MIDI::getInstance() {
    static MIDI instance;
    return instance;
}



void MIDI::setup(unsigned int port) {
    midiIn.openPort(port);
    midiIn.ignoreTypes(false, false, false);
    midiIn.addListener(this);
    midiIn.setVerbose(true);
}



void MIDI::update() {
    /// queued message handling
    if(midiIn.hasWaitingMessages()) {
        ofxMidiMessage message;
        
        
        // add the latest message to the message queue
        while(midiIn.getNextMessage(message)) {
            midiMessages.push_back(message);
        }
        
        // remove any old messages if we have too many
        while(midiMessages.size() > maxMessages) {
            midiMessages.erase(midiMessages.begin());
        }
    }
}


void MIDI::newMidiMessage(ofxMidiMessage &message) {
    if (debug) {
        ofLog(OF_LOG_NOTICE, "MIDI message: " + message.toString());
    }
    
    // add the latest message to the messagie queue
    midiMessages.push_back(message);
    
    // remove any old messages if we have too many
    while(midiMessages.size() > maxMessages) {
        midiMessages.erase(midiMessages.begin());
    }
    
    notify(message);
}


void MIDI::regist(MIDIAction action, std::function<void(ofxMidiMessage)> lambda) {
    observers.push_back({action, lambda});
}


void MIDI::notify(ofxMidiMessage message) {
    for(const auto& pair: observers) {
        MIDIAction action = pair.first;
        if (message.status != action.status) {
            continue;
        }
        if (message.status != action.status) {
            continue;
        }
        if (message.control != action.control) {
            continue;
        }
        if (message.portNum != action.portNum) {
            continue;
        }
        
        pair.second(message);
    }
    
}


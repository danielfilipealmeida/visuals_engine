//
//  MIDI.hpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 30/06/2025.
//

#ifndef __MIDI_h__
#define __MIDI_h__

#include "ofxMidi.h"

/**
 Class wrapper for controlling MIDI using the singleton pattern
 */
class MIDI : public ofxMidiListener {
    ofxMidiIn midiIn;
    std::vector<ofxMidiMessage> midiMessages;
    std::size_t maxMessages = 10;
    
public:
    
    MIDI(const MIDI&) = delete;
    MIDI& operator=(const MIDI&) = delete;
    
    //! Returns the instance of the MIDI singleton
    static MIDI& getInstance() {
        static MIDI instance;
        return instance;
    }
    
    /// Setups up midi to the selected port
    /// @param {unsigned int} port - the port
    void setup(unsigned int port) {
        midiIn.openPort(port);
        midiIn.ignoreTypes(false, false, false);
        midiIn.addListener(this);
        midiIn.setVerbose(true);
    }
    
    void update() {
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

    
    /// Handles new Midi Message comming in
    /// @param {ofxMidiMessage} messate - the new midi message
    void newMidiMessage(ofxMidiMessage &message) {
        cout << "New Message in: "<<message.toString() <<endl;
        
        // add the latest message to the messagie queue
        midiMessages.push_back(message);
        
        // remove any old messages if we have too many
        while(midiMessages.size() > maxMessages) {
            midiMessages.erase(midiMessages.begin());
        }
    }
    
private:
    
    MIDI() {
        cout << "MIDI Singleton instanciated" <<endl;
        midiIn.listInPorts();
    }
};


#endif /* __MIDI_h__ */

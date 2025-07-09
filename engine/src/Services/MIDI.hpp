//
//  MIDI.hpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 30/06/2025.
//

#ifndef __MIDI_h__
#define __MIDI_h__

#include "ofxMidi.h"
#include "Observer.hpp"

struct MIDIAction {
    MidiStatus status;
    int channel;
    int control;
    int portNum;
} ;

///
/// \brief Class wrapper for controlling MIDI using the singleton pattern
class MIDI : public ofxMidiListener {
    ofxMidiIn midiIn;
    std::vector<ofxMidiMessage> midiMessages;
    std::size_t maxMessages = 10;
    
    std::vector<std::pair<MIDIAction, std::function<void(ofxMidiMessage)> >> observers;
    
public:
    bool debug = false;
    
    MIDI(const MIDI&) = delete;
    MIDI& operator=(const MIDI&) = delete;
    
    /// \brief Returns the instance of the MIDI singleton
    static MIDI& getInstance() {
        static MIDI instance;
        return instance;
    }
    
    
    /// \brief setups up midi to the selected port
    /// \param {unsigned int} port - the port
    void setup(unsigned int port) {
        midiIn.openPort(port);
        midiIn.ignoreTypes(false, false, false);
        midiIn.addListener(this);
        midiIn.setVerbose(true);
    }
    
    
    /// Handles update
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
        if (debug) {
            cout << "New Message in: "<<message.toString() <<endl;
        }
        
        // add the latest message to the messagie queue
        midiMessages.push_back(message);
        
        // remove any old messages if we have too many
        while(midiMessages.size() > maxMessages) {
            midiMessages.erase(midiMessages.begin());
        }
        
        notify(message);
    }
    
    /// \brief add a new observer to midi.
    /// \abstract everytime the action condition is meet, the lambda is executed with the message
    /// \param action - the condition fot the midi action
    /// \param lambda - the anonymous function to be executed with the midi message as argument
    void regist(MIDIAction action, std::function<void(ofxMidiMessage)> lambda) {
        observers.push_back({action, lambda});
    }
    
    /// \brief Traverse all observers and execute all anonymous functions triggered by the current message
    /// \param message - the current midi message being handled
    void notify(ofxMidiMessage message) {
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
private:
    
    MIDI() {
        cout << "MIDI Singleton instanciated" <<endl;
        midiIn.listInPorts();
    }
};


/// \brief Observer class to be used by the application
/// \abstract Because an application can have several observers, it is needed to offload that behaviour into its own class in order for the main class to have several diferent kind of observers, for different situations
/*
class MIDIObserver : Observer<ofxMidiMessage> {

public:
    MIDIObserver() {
        
    }
    
    void regist(){
        
    }
};

 */

#endif /* __MIDI_h__ */

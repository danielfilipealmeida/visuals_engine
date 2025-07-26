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
    static MIDI& getInstance();
    
    
    /// \brief setups up midi to the selected port
    ///
    /// \param {unsigned int} port - the port
    void setup(unsigned int port);
    
    
    /// \brief Handles update
    void update();

    
    /// Handles new Midi Message comming in
    /// @param {ofxMidiMessage} messate - the new midi message
    void newMidiMessage(ofxMidiMessage &message);
    
    /// \brief add a new observer to midi.
    /// \abstract everytime the action condition is meet, the lambda is executed with the message
    /// \param action - the condition fot the midi action
    /// \param lambda - the anonymous function to be executed with the midi message as argument
    void regist(MIDIAction action, std::function<void(ofxMidiMessage)> lambda);
    
    
    /// \brief Traverse all observers and execute all anonymous functions triggered by the current message
    /// \param message - the current midi message being handled
    void notify(ofxMidiMessage message);
    
private:
    
    /// \brief Constructor. Never executed directly.
    MIDI();
    
    /// \brief Destructor, cleanup all resources.
    ~MIDI();
};

#endif /* __MIDI_h__ */

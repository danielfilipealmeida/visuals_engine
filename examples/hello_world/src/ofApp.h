#pragma once

#include "ofMain.h"
#include "Layer.hpp"
#include "Visuals.hpp"
#include "Mixer.hpp"
#include "Signals.hpp"
#include "Set.hpp"
#include "MIDI.hpp"
#include "State.hpp"
#include "ui.hpp"


/// @brief Hello world main class
///
/// This is the main class of the `Hello World` example, the highest level of code for the example.
class ofApp : public ofBaseApp, public Observer<ofxMidiMessage> {
    float bufferWidth = 640;
    float bufferHeight = 480;
    
    bool showInterface;
    
    Set set;
    shared_ptr<State> state;
    
    Visual<BufferPlotter> *audioPlotter, *fftPlotter;
    
    ui ui;
    
public:
    /// \brief app setup function.
    /// \details initializes and sets up the state, midi, audio and ui
    void setup();
    
    /// \brief sets up midi
    void setupMIDI(bool debug);
    
    /// \brief sets up audio
    void setupAudio();
    
    /// \brief defines the keyboad handlers
    void setupKeys();
    
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofSoundStream soundStream;
    
    /// \brief Handles audio input and feed in the audio signal into the FFT singleton in order to calculate the FFT of the current buffer
    ///
    /// \param buffer - the current audio buffer
    void audioIn( ofSoundBuffer& buffer );
    
    
    /** todo: move to its own class */
    vector<float> volHistory;
    vector<float> audioInput;
    vector<float> fftOutput;
    int bufferSize;
};

#pragma once

#include "ofMain.h"
#include "Layer.hpp"
#include "Visuals.hpp"
#include "Mixer.hpp"
#include "Signals.hpp"
#include "UI/UI.hpp"
#include "Engine/Set.hpp"
#include "UserInterface.hpp"
#include "MIDI.hpp"
#include "State.hpp"


/// @brief Hello world main class
///
/// This is the main class of the `Hello World` example, the highest level of code for the example.
class ofApp : public ofBaseApp, public Observer<ofxMidiMessage> {
    float bufferWidth = 640;
    float bufferHeight = 480;
    
    bool showInterface;
    
    Set set;
    
    UserInterface userInterface;

    State state;
    
	public:
		void setup();
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
        void audioIn( ofSoundBuffer& buffer );
        

    /** todo: move to its own class */
    vector<float> volHistory;
    vector<float> audioInput;
    vector<float> fftOutput;
    int bufferSize;
};

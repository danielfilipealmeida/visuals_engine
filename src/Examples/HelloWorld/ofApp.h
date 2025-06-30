#pragma once

#include "ofMain.h"
#include "Layer.hpp"
#include "Visuals.hpp"
#include "Mixer.hpp"
#include "Signals.hpp"
#include "UI/UI.hpp"
#include "Engine/Set.hpp"
#include "UserInterface.hpp"


class ofApp : public ofBaseApp{
    LayerStack *layerStackA, *layerStackB;
    Mixer *mixer;
    Visual<ofVideoPlayer> *video;
    float bufferWidth = 640;
    float bufferHeight = 480;
    
    bool showInterface;
    
    Set set;
    
    Signal<float> signal1, signal2;
    
    UserInterface userInterface;
    
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
        //void audioIn( float * input, int bufferSize, int nChannels );

    /** todo: move to its own class */
    vector<float> volHistory;
    vector<float> audioInput;
    vector<float> fftOutput;
    int bufferSize;
};

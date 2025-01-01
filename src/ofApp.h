#pragma once

#include "ofMain.h"
#include "Video.hpp"
#include "Layer.hpp"
#include "Visuals.hpp"
#include "Mixer.hpp"
#include "Signals.hpp"
#include "UI/UI.hpp"

class ofApp : public ofBaseApp{
    LayerStack *layerStackA, *layerStackB;
    Mixer *mixer;
    Visual<ofVideoPlayer> *video;
    float bufferWidth = 640;
    float bufferHeight = 480;
    
    Signal<float> signal;
    
    UI::UserInterface ui;
    UI::HorizontalSplitter horizontalSplitter;
    UI::CrossFader *mixCrossfader;
    
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
};

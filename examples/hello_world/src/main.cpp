#include "ofMain.h"
#include "ofApp.h"


//========================================================================
int main( ){
	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
    ofGLFWWindowSettings settings;
	settings.setSize(1024, 768);
	settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN

	auto window = ofCreateWindow(settings);
    
    ofSetWindowShape(ofGetScreenWidth(), ofGetScreenHeight());
    window->setFullscreen(true);

	ofRunApp(window, make_shared<ofApp>());
	ofRunMainLoop();
}

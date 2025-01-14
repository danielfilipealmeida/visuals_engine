//
//  Visuals.hpp
//  emptyExample
//
//  Created by Daniel Almeida on 27/12/2024.
//

#ifndef __Visuals_hpp__
#define __Visuals_hpp__

#import "BaseClasses.hpp"
#import "ofMain.h"
#import "Signals.hpp"
#import "SignalPlotter.hpp"

template<class T>
class Visual: public VisualsInterface {
private:
    T visual;
    
public:
    Visual(T _visual, ofRectangle _rect) {
        visual = _visual;
        rect = _rect;
        play();
    }
    void update() {
        visual.update();
    }
    void draw() {
        visual.draw(rect);
    }
    void draw(ofRectangle _rect) {
        visual.draw(_rect);
    }

    void play() {
        visual.play();
    }
    void stop() {
        visual.stop();
    }
};

/** ofVideoGrabber partial specializations */
template<> inline void Visual<ofVideoGrabber>::play(){};
template<> inline void Visual<ofVideoGrabber>::stop(){};


/// Class containing a compilation of methods to work as builders of visuals
/// It needs to know in advance the dimentions of the existing rendering buffers on the application.
/// 
/// @param _width: the width of the rendering buffer
/// @param _height: the height of the rendering buffers
class VisualsBuilder {
    float width;
    float height;
public:
    VisualsBuilder(float _width, float _height) {
        width = _width;
        height = _height;
    }
    
    Visual<ofVideoPlayer>* Video(std::string path) {
        Visual<ofVideoPlayer> *visual;
        
        visual = new Visual<ofVideoPlayer>([&]{
            ofVideoPlayer player;
            player.load(path);
            return player;
        }(), ofRectangle(0, 0, width, height));
        
        return visual;
    };
    
    Visual<ofVideoGrabber> *VideoGrabber(int _deviceId) {
        Visual<ofVideoGrabber> *visual;
        
        visual = new Visual<ofVideoGrabber>([&] {
            ofVideoGrabber grabber;
            grabber.setDeviceID(_deviceId);
            grabber.initGrabber(ofGetWidth(), ofGetHeight());
            
            return grabber;
        }(), ofRectangle(0,0,width, height));
        
        return visual;
    }
    
    Visual<SignalPlotter> *Plotter(Signal<float> *signal) {
        Visual<SignalPlotter> *visual;
        
        visual = new Visual<SignalPlotter>([&](){
            SignalPlotter plotter = SignalPlotter(signal);
            return plotter;
        }(), ofRectangle(0,0,width, height));
        
        return visual;
    }
};

#endif

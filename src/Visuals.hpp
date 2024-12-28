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
};

#endif

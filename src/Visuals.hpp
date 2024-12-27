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

    void play() {
        visual.play();
    }
    void stop() {
        visual.stop();
    }
};

class VisualsBuilder {
public:
    static Visual<ofVideoPlayer>* Video(std::string path) {
        Visual<ofVideoPlayer> *visual;
        
        visual = new Visual<ofVideoPlayer>([&]{
            ofVideoPlayer player;
            player.load(path);
            return player;
        }(), ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
        
        return visual;
    };
};

#endif

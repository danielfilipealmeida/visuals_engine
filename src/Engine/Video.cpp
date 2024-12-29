//
//  Video.cpp
//  emptyExample
//
//  Created by Daniel Almeida on 07/07/2024.
//

#include "Video.hpp"

/**
 Todo:
 
 - [ ] Playmodes
 - [ ] draw to an FBO
 - [ ] shared code must be stored in the interface
 */


Video::Video(std::string name) {
    player.load(name);
    play();
    rect = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());
}

void Video::update(){
    if (!player.isPlaying()) {
        return;
    }
    
    player.update();
};

void Video::draw(){
    player.draw(this->rect);
};


void Video::play() {
    player.play();
}

void Video::stop() {
    player.stop();
}

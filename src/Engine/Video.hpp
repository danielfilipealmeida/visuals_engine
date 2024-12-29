//
//  Video.hpp
//  emptyExample
//
//  Created by Daniel Almeida on 07/07/2024.
//

#ifndef Video_hpp
#define Video_hpp

#include <stdio.h>
#include "BaseClasses.hpp"
#include "ofVideoPlayer.h"
#include "ofMain.h"

class Video :  public VisualsInterface {
    ofVideoPlayer player;
    
public:
    
    Video(std::string name);
    void update();
    void draw();
    void setRect(ofRectangle rect);
    void play();
    void stop();
};


#endif /* Video_hpp */

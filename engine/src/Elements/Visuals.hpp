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
#import "BufferPlotter.hpp"
#import "Utils.hpp"

enum VisualTypes {
    camera,
    video,
    plot
};

NLOHMANN_JSON_SERIALIZE_ENUM(
                             VisualTypes, {
                                 { VisualTypes::camera, "camera" },
                                 { VisualTypes::video, "video" },
                                 { VisualTypes::plot, "plot" }
                             }
                             );

/// \brief Visual template class
/// \details Template class that
template<class T>
class Visual: public VisualsInterface {
public:
    T visual;
    
    /// Will store needed data that cannot be accessed in the visual
    ofJson data;
    
    Visual(ofJson data) {}
    Visual(T _visual, ofRectangle _rect) {
        visual = _visual;
        rect = _rect;
    }
    ~Visual() {}
    
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
    ofJson encode() {
        return {};
    }
    void decode(ofJson json){}
    
    /// \brief Copy assignment operator
    Visual& operator=(const Visual& other) {
        if(this != &other) {
            if constexpr (std::is_same_v<T, ofVideoPlayer>) {
                const string path = other.visual.getMoviePath();
                visual.load(path);
            }
        }
      
        return *this;
    }
    
};

/**
 ofVideoGrabber partial specializations
 */
template<> inline void Visual<ofVideoGrabber>::play(){};
template<> inline void Visual<ofVideoGrabber>::stop(){};
template<> inline ofJson Visual<ofVideoGrabber>::encode(){
    return {
        {"type", VisualTypes::camera},
        {"deviceId", data["deviceId"]},
        {"width", visual.getWidth()},
        {"height", visual.getHeight()}
    };
};
template<> inline void Visual<ofVideoGrabber>::decode(ofJson json) {
    //todo
}


/**
 ofVideoPlayer partial specializations
 */
template<> inline Visual<ofVideoPlayer>::~Visual(){ visual.stop(); };
template<> inline ofJson Visual<ofVideoPlayer>::encode(){
    return {
        {"id", hashFromAddress(this)},
        {"type", VisualTypes::video},
        {"path", visual.getMoviePath()},
        {"width", visual.getWidth()},
        {"height", visual.getHeight()}
    };
};
template<> inline void Visual<ofVideoPlayer>::decode(ofJson json) {
    //todo
}

/**
 SignalPloter partial specializations
 */
template<> inline ofJson Visual<SignalPlotter>::encode() {
    return {
        {"type", VisualTypes::plot},
        {"signal", "todo"},
        {"samples", visual.nSamples},
        {"width", visual.rect.width},
        {"height", visual.rect.height}
    };
}; // no way to export a signal.
template<> inline void Visual<SignalPlotter>::decode(ofJson json) {
    //todo
}




#endif

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

enum VisualTypes {
    camera,
    loop,
    plot
};

NLOHMANN_JSON_SERIALIZE_ENUM(
                             VisualTypes, {
                                 { VisualTypes::camera, "camera" },
                                 { VisualTypes::loop, "loop" },
                                 { VisualTypes::plot, "plot" }
                             }
);


template<class T>
class Visual: public VisualsInterface {
private:
    T visual;
    
public:
    
    /// Will store needed data that cannot be accessed in the visual
    ofJson data;
    
    Visual(ofJson data) {}
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
    ofJson encode() {
        return {};
    }
};


/** ofVideoGrabber partial specializations */
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

/** ofVideoPlayer partial specializations */
template<> inline ofJson Visual<ofVideoPlayer>::encode(){
    return {
        {"type", VisualTypes::loop},
        {"path", visual.getMoviePath()},
        {"width", visual.getWidth()},
        {"height", visual.getHeight()}
    };
};

/** SignalPloter partial specializations */
template<> inline ofJson Visual<SignalPlotter>::encode() {
    return {
        {"type", VisualTypes::plot},
        {"signal", "todo"},
        {"samples", visual.nSamples},
        {"width", visual.rect.width},
        {"height", visual.rect.height}
    };
}; // no way to export a signal. 




/// Class containing a compilation of methods to work as builders of visuals
/// It needs to know in advance the dimentions of the existing rendering buffers on the application.
/// 
/// @param _width: the width of the rendering buffer
/// @param _height: the height of the rendering buffers
class VisualsFactory {
    float width;
    float height;
public:
    VisualsFactory(float _width, float _height) {
        width = _width;
        height = _height;
    }
    
    /// Returns a configured video loop visual
    /// \param path
    Visual<ofVideoPlayer>* Video(std::string path) {
        Visual<ofVideoPlayer> *visual;
        
        visual = new Visual<ofVideoPlayer>([&]{
            ofVideoPlayer player;
            player.load(path);
            return player;
        }(), ofRectangle(0, 0, width, height));
        
        return visual;
    };
    
    /// Returns a configured camera visual
    /// \param deviceId
    Visual<ofVideoGrabber> *VideoGrabber(int _deviceId) {
        Visual<ofVideoGrabber> *visual;
        
        visual = new Visual<ofVideoGrabber>([&] {
            ofVideoGrabber grabber;
            grabber.setDeviceID(_deviceId);
            grabber.initGrabber(ofGetWidth(), ofGetHeight());
            
            return grabber;
        }(), ofRectangle(0,0,width, height));
        
        // manually add the device id to the json variable because this isn't accessible on ofVideoGrabber
        visual->data["deviceId"];
        
        return visual;
    }
    
    /// Returns a signal plotter visual
    /// \param *signal 
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

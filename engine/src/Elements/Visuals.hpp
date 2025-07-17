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
    ~Visual() {
        visual.close();
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




/// \brief Class containing a compilation of methods to work as builders of visuals
/// It needs to know in advance the dimentions of the existing rendering buffers on the application.
class VisualsFactory {
    float width;
    float height;
public:
    
    /// \brief Factory constructor, used to set the default of width and height to be used when seting up new visuals
    ///
    /// @param _width: the width of the rendering buffer
    /// @param _height: the height of the rendering buffers
    VisualsFactory(float _width, float _height) {
        width = _width;
        height = _height;
    }
    
    /// \brief Returns a configured video loop visual
    ///
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
    
    /// \brief Returns a configured camera visual
    /// 
    /// \param deviceId  - the identification of what camera to use
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
    
    //! @abstract Returns a signal plotter visual
    //!
    //! @param signal -  the actual signal to be printed.
    Visual<SignalPlotter> *Plotter(Signal<float> *signal) {
        Visual<SignalPlotter> *visual;
        
        visual = new Visual<SignalPlotter>([&](){
            SignalPlotter plotter = SignalPlotter(signal);
            return plotter;
        }(), ofRectangle(0,0,width, height));
        
        return visual;
    }
    
    //! @abstract Creates a Visual of type bufferPlotter and returns it configured
    //!
    //! @param buffer - the buffer to draw
    Visual<BufferPlotter> *Plotter(vector<float> *buffer) {
        Visual<BufferPlotter> *visual;
        
        visual = new Visual<BufferPlotter>([&](){
            BufferPlotter plotter = BufferPlotter(buffer);
            
            return plotter;
        }(), ofRectangle(0,0,width,height));
        
        return visual;
    }
};

#endif

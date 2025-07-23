//
//  VisualsFactory.hpp
//  Engine
//
//  Created by Daniel Almeida on 23/07/2025.
//

#ifndef VisualsFactory_hpp
#define VisualsFactory_hpp

#import "BaseClasses.hpp"
#import "ofMain.h"
#import "Signals.hpp"
#import "SignalPlotter.hpp"
#import "BufferPlotter.hpp"
#import "Visuals.hpp"

#define VISUAL_FACTORY_DEFAULT_WIDTH 640
#define VISUAL_FACTORY_DEFAYLT_HEIGHT 480

/// \brief Class containing a compilation of methods to work as builders of visuals
/// It needs to know in advance the dimentions of the existing rendering buffers on the application.
/// todo: turn this into a singleton in order to be used everywhere.
class VisualsFactory {

public:
    float width = VISUAL_FACTORY_DEFAULT_WIDTH;
    float height = VISUAL_FACTORY_DEFAYLT_HEIGHT;
    
    
    VisualsFactory(const VisualsFactory&) = delete;
    VisualsFactory& operator=(const VisualsFactory&) = delete;
    
    
    /// Returns the instance of the VisualsFactory singleton. Creates it if needed
    static VisualsFactory& getInstance() {
        static VisualsFactory instance;
        return instance;
    }
    
    /// \brief Returns a configured video loop visual
    ///
    /// \param path  - the path in the bin folder
    Visual<ofVideoPlayer>* Video(std::string path);
    
    /// \brief Returns a configured camera visual
    ///
    /// \param _deviceId  - the identification of what camera to use
    Visual<ofVideoGrabber> *VideoGrabber(int _deviceId);
    
    //! @abstract Returns a signal plotter visual
    //!
    //! @param signal -  the actual signal to be printed.
    Visual<SignalPlotter> *Plotter(Signal<float> *signal);
    
    //! @abstract Creates a Visual of type bufferPlotter and returns it configured
    //!
    //! @param buffer - the buffer to draw
    Visual<BufferPlotter> *Plotter(vector<float> *buffer);
    
    /// \brief Returns the visual from the provided json
    ///
    /// \param json - the json object that specifies the visual instance
    VisualsInterface*  VisualFromJson(ofJson json);
    
private:
    VisualsFactory() {
        cout<<"VisualsFactory Singleton instanciated"<<endl;
    }
};

#endif /* VisualsFactory_hpp */

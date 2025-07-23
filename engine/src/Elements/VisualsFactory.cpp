//
//  VisualsFactory.cpp
//  Engine
//
//  Created by Daniel Almeida on 23/07/2025.
//

#include "VisualsFactory.hpp"



Visual<ofVideoPlayer>* VisualsFactory::Video(std::string path) {
    Visual<ofVideoPlayer> *visual;
    
    visual = new Visual<ofVideoPlayer>([&]{
        ofVideoPlayer player;
        player.load(path);
        return player;
    }(), ofRectangle(0, 0, width, height));
    
    return visual;
};


Visual<ofVideoGrabber>* VisualsFactory::VideoGrabber(int _deviceId) {
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


Visual<SignalPlotter>* VisualsFactory::Plotter(Signal<float> *signal) {
    Visual<SignalPlotter> *visual;
    
    visual = new Visual<SignalPlotter>([&](){
        SignalPlotter plotter = SignalPlotter(signal);
        return plotter;
    }(), ofRectangle(0,0,width, height));
    
    return visual;
}


Visual<BufferPlotter>* VisualsFactory::Plotter(vector<float> *buffer) {
    Visual<BufferPlotter> *visual;
    
    visual = new Visual<BufferPlotter>([&](){
        BufferPlotter plotter = BufferPlotter(buffer);
        
        return plotter;
    }(), ofRectangle(0,0,width,height));
    
    return visual;
}


VisualsInterface* VisualsFactory::VisualFromJson(ofJson json) {
    if (!json.contains("type")) {
        throw std::runtime_error("Type not set in json.");
    }
    
    switch (json["type"].get<VisualTypes>()){
        case VisualTypes::camera:
            return VideoGrabber(json["deviceId"]);
            
        case VisualTypes::video:
            return Video(json["path"].get<string>());
            
        case VisualTypes::plot:
            return NULL;
            //addVisual(builder->Plotter(<#Signal<float> *signal#>))
            break;
            
        
    }
    
    /*
    if (json["type"] == "video") {
        return Video(json["path"]);
    }*/
    
    return NULL;
}

//
//  Set.cpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 23/01/2025.
//

//
//  Set.hpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 13/01/2025.
//
#include "Set.hpp"

void Set::addVisual(VisualsInterface* visual) {
    visuals.push_back(visual);
};


ofJson Set::encode() {
    ofJson visualsJson;
    
    for (VisualsInterface *visual : visuals) {
        visualsJson.push_back(visual->encode());
    }
    
    ofJson result = {
        {"visuals", visualsJson}
    };
    
    
    return result;
};

void Set::decode(ofJson data){
    visuals.empty();
    
    for(auto visual : data["visuals"]) {
        VisualsBuilder *builder;
        switch (visual["type"].get<VisualTypes>()){
            case VisualTypes::camera:
                 builder = new VisualsBuilder(visual["width"].get<float>(), visual["height"].get<float>());
                addVisual(builder->VideoGrabber(visual["deviceId"]));
                delete builder;
                break;
                
            case VisualTypes::loop:
                builder = new VisualsBuilder(visual["width"].get<float>(), visual["height"].get<float>());
                addVisual(builder->Video(visual["path"].get<string>()));
                delete builder;
                break;
                
            case VisualTypes::plot:
                //addVisual(builder->Plotter(<#Signal<float> *signal#>))
                break;
                
            default:
                break;
        }
        
    }
}

void Set::save(std::string path) {
    ofJson data = encode();
    
    ofSaveJson(path, data);
}

void Set::load(std::string path) {
    ofJson data = ofLoadJson(path);
    
    decode(data);
}


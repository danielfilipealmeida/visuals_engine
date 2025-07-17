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
        VisualsFactory *factory;
        switch (visual["type"].get<VisualTypes>()){
            case VisualTypes::camera:
                 factory = new VisualsFactory(visual["width"].get<float>(), visual["height"].get<float>());
                addVisual(factory->VideoGrabber(visual["deviceId"]));
                delete factory;
                break;
                
            case VisualTypes::loop:
                factory = new VisualsFactory(visual["width"].get<float>(), visual["height"].get<float>());
                addVisual(factory->Video(visual["path"].get<string>()));
                delete factory;
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


VisualsInterface* Set::getVisualAtIndex(unsigned int index) {
    if (index >= visuals.size()) {
        return NULL;
    }
    
    return visuals[index];
}

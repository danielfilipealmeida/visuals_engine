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
#include "VisualsFactory.hpp"

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
    
    VisualsFactory& factory = VisualsFactory::getInstance();
    
    for(auto visual : data["visuals"]) {
        addVisual(factory.VisualFromJson(visual));
        /*
        switch (visual["type"].get<VisualTypes>()){
            case VisualTypes::camera:
                factory.width = visual["width"].get<float>();
                factory.height = visual["height"].get<float>();
                addVisual(factory.VideoGrabber(visual["deviceId"]));
              
                break;
                
            case VisualTypes::video:
                factory.width = visual["width"].get<float>();
                factory.height = visual["height"].get<float>();
                addVisual(factory.Video(visual["path"].get<string>()));
              
                break;
                
            case VisualTypes::plot:
                //addVisual(builder->Plotter(<#Signal<float> *signal#>))
                break;
                
            default:
                break;
        }
        */
        
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

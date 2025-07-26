//
//  State.cpp
//  Hello World
//
//  Created by Daniel Almeida on 25/07/2025.
//

#include "State.hpp"
#include "Mixer.hpp"



State::~State(){
    ofLog(OF_LOG_NOTICE, "Destroying State");
    /*
    for(auto layer : layerStackA->layers) {
        delete layer;
    }
    free(layerStackA);
    
    for(auto layer : layerStackB->layers) {
        delete layer;
    }
    free(layerStackB);
     */
}

void State::setup(
                  Set* set,
                  float bufferWidth,
                  float bufferHeight
                  ) {
    
    this->set = set;
    this->bufferWidth = bufferWidth;
    this->bufferHeight = bufferHeight;
    
    signal1 = SignalsFactory::SineWave();
    signal2 = SignalsFactory::Random(10, 1);
    
    layerStackA = new LayerStack(bufferWidth, bufferHeight);
    layerStackA->insert(new Layer(bufferWidth, bufferHeight));
    layerStackA->insert(new Layer(bufferWidth, bufferHeight));
    
    layerStackB = new LayerStack(bufferWidth, bufferHeight);
    layerStackB->insert(new Layer(bufferWidth, bufferHeight));
    layerStackB->insert(new Layer(bufferWidth, bufferHeight));
    
    contrast = 1;
    saturation = 1;
    brightness = 1;
    
    redTint = 1;
    blueTint= 1;
    greenTint = 1;
    
    mixer = new Mixer(layerStackA,
                      layerStackB,
                      bufferWidth, bufferHeight);
    decoratedMixer = TransformationFactory::GLSL((VisualsInterface *) mixer,
                                                 { "ContrastBrightnessSaturation", "FastBlur", "RGBTint"},
                                                 {
        {
        {"contrast", &contrast},
        {"saturation", &saturation},
        {"brightness", &brightness}
        
        },
        {
        {"blurH", &blurAmount},
        {"blurV", &blurAmount}
        },
    
        {
        
        {"redTint", &redTint},
        {"greenTint", &greenTint},
        {"blueTint", &blueTint}
        
        }
    
    });
    
    mixer->setMix(0.5);
    
    signal1.regist(mixer, mixer->parameters[MixerObservableParameters::MIX]);
    
}


void State::update() {
    decoratedMixer->update();
    signal1.update();
    signal2.update();
}


void State::triggerVisualAtSelectedLayer(VisualsInterface *visual) {
    if (visual == NULL) {
        return;
    }
    
    LayerStack *layerStack = selectedChannel == Channel::A ? layerStackA : layerStackB;
    layerStack->setVisualForLayer(selectedLayer, visual);
};


void State::save(of::filesystem::path filename) {
    ofJson json = {};
    
    json["mixer"] = mixer->encode();
    json["width"] = bufferWidth;
    json["height"] = bufferHeight;
    json["state"] = {
        {"blur", blurAmount},
        {"contrast", contrast},
        {"saturation", saturation},
        {"brightness", brightness},
        {"redTint", redTint},
        {"blueTint", blueTint},
        {"greenTint", greenTint}
    };
    json["set"] = set->encode();
    
    ofSavePrettyJson(filename, json);
}


void State::load(of::filesystem::path filename) {
    ofJson json = ofLoadJson(filename);
    
    if (json.is_null()) {
        throw std::runtime_error("Error loading json file");
    }
    
    bufferWidth = json["width"];
    bufferHeight = json["height"];
    blurAmount = json["state"]["blur"];
    contrast = json["state"]["contrast"];
    saturation = json["state"]["saturation"];
    brightness = json["state"]["brightness"];
    redTint = json["state"]["redTint"];
    blueTint = json["state"]["blueTint"];
    greenTint = json["state"]["greenTint"];
    mixer->decode(json["mixer"]);
    set->decode(json["set"]);
    
    layerStackA = (LayerStack*) mixer->a;
    layerStackB = (LayerStack*) mixer->b;
    
    setPlayingVisualsInChannel((LayerStack *) mixer->a, json["mixer"]["a"]["layers"]);
    setPlayingVisualsInChannel((LayerStack *) mixer->b, json["mixer"]["b"]["layers"]);
}

void State::setPlayingVisualsInChannel(LayerStack *channel, ofJson layersJson) {
    int count = 0;
    for (Layer *layer: channel->layers) {
        std::string id = layersJson[count]["visualId"];
        VisualsInterface* visual = set->getVisualById(id);
        if(visual) {
            layer->visual = visual;
            visual->play();
        }
        
        count++;
    }
}



void State::defaultSet() {
    VisualsFactory& visualsFactory = VisualsFactory::getInstance();
    
    set->addVisual(visualsFactory.Video("001.mov"));
    set->addVisual(visualsFactory.Video("002.mov"));
    set->addVisual(visualsFactory.Video("003.mov"));
    set->addVisual(visualsFactory.Video("004.mov"));
}

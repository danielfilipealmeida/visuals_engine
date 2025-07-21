#include "ofMain.h"
#include "ofAppNoWindow.h"
#include "ofxUnitTests.h"
#include "Layer.hpp"
#include "LayerStack.hpp"
#include "Mixer.hpp"

class ofApp : public ofxUnitTestsApp {
    
public:
    
    /// \brief tests Layer::encode()
    /// \details Tests that the encode method of the
    void testLayerCanEncode() {
        // start with testing default values
        Layer layer = Layer(640, 480);
    
        ofJson encodedLayer = layer.encode();
        
        ofxTestEq(encodedLayer["type"], "layer", "Layer type should be layer");
        ofxTestEq(encodedLayer["width"], 640, "encoded layer width is 640");
        ofxTestEq(encodedLayer["height"], 480, "encoded layer width is 640");
        ofxTestEq(encodedLayer["alpha"], 1, "encoded layer alpha is 1");
        ofxTestEq(encodedLayer["blendMode"], "add", "encoded layer blend mode is add");
     
        // update some values and confirm they are correct
        layer.blendMode = OF_BLENDMODE_ALPHA;
        layer.alpha = 0.5;
        encodedLayer = layer.encode();
        
        ofxTestEq(encodedLayer["alpha"], 0.5, "updated encoded layer alpha is 0.5");
        ofxTestEq(encodedLayer["blendMode"], "alpha", "updated encoded layer blend mode is alpha");
    }
    
    void testLayerStackCanEncode() {
        LayerStack layerStack = LayerStack(320, 200);
    
        ofJson encoded = layerStack.encode();
        
        ofxTestEq(encoded["type"], "layerstack", "LayerStack type should be layerstack");
        ofxTestEq(encoded["width"], 320, "LayerStack width should be 300");
        ofxTestEq(encoded["height"], 200, "LayerStack height should be 200");
        ofxTestEq(encoded["layers"].size(), 0, "layers in LayerStack should be 0");
        
        // add a layer
        Layer layer1 = Layer(320, 200);
        layerStack.insert(&layer1);
        
        encoded = layerStack.encode();
        ofxTestEq(encoded["layers"].size(), 1, "layers in LayerStack should be 1");
        ofxTestEq(encoded["layers"][0]["width"], 320, "first layer width should be 320");
        ofxTestEq(encoded["layers"][0]["height"], 200, "first layer height should be 200");
        
        // add another layer
        Layer layer2 = Layer(640, 480);
        layer2.blendMode = OF_BLENDMODE_MULTIPLY;
        layer2.alpha = 0.25;
        layerStack.insert(&layer2);
        
        encoded = layerStack.encode();
        ofxTestEq(encoded["layers"].size(), 2, "layers in LayerStack should be 1");
        ofxTestEq(encoded["layers"][1]["width"], 640, "second layer width should be 640");
        ofxTestEq(encoded["layers"][1]["height"], 480, "second layer width should be 480");
        ofxTestEq(encoded["layers"][1]["alpha"], 0.25, "second layer alpha should be 0.25");
        ofxTestEq(encoded["layers"][1]["blendMode"], "multiply", "second layer blendMode should be multiply");

    }
    
    void testMixerCanEncode() {
        Layer channelA = Layer(320, 200);
        Layer channelB = Layer(640, 480);
        Mixer mixer = Mixer(&channelA, &channelB, 320, 200);
        
        ofJson encoded = mixer.encode();
        ofxTestEq(encoded["width"], 320, "Mixer width should be 300");
        ofxTestEq(encoded["height"], 200, "Mixer height should be 200");
        ofxTestEq(encoded["mix"], 0.5, "Mixer default mix value is 0.5");
        ofxTestEq(encoded["mix"]["a"]["type"], "layer", "");
    }
    
    void run(){
        testLayerCanEncode();
        testLayerStackCanEncode();
        testMixerCanEncode();
    }
};

int main( ){
    ofInit();
    auto window = std::make_shared<ofAppNoWindow>();
    auto app = std::make_shared<ofApp>();
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(window, app);
    return ofRunMainLoop();
}

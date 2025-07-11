//
//  Layer.hpp
//  emptyExample
//
//  Created by Daniel Almeida on 26/12/2024.
//

#ifndef Layer_hpp
#define Layer_hpp

#include "BaseClasses.hpp"
#include <vector>

//! @class Layer
//! @abstract Inplements a Layer, which is the combination of a visual an alpha value and a blend mode.
//! @discussion Layers can be stacked
class Layer: public VisualsInterface {
    
    //! @var alpha
    //! @abstract the transparency value, from 0.0 to 1.0
    float alpha;
    
    //! @var visual
    //! @abstract pointer to the visual
    VisualsInterface* visual;
    
    //! @var blendMode
    //! @abstract defines which blend mode used to draw the visual in the layer
    ofBlendMode blendMode;
    
public:
    
    //! @brief Constructor
    //! @param _visual the visual to display on the layer
    //! @param alpha the transparency of the layer
    //! @param blendMode which blend mode used to draw the layer
    Layer(
          VisualsInterface* _visual = NULL,
          float _alpha = 1,
          ofBlendMode _blendMode = OF_BLENDMODE_ADD
        );
    
    //! @brief updates the visual
    //! @discussion will return if visual is null
    void update();
    
    //! @brief draws the visual with the blend mode and transparency
    //! @discussion will leave if visual is null
    void draw();
    
    //! @brief draws the visual in a specified rectangular area
    //! @param rect the rectangle
    void draw(ofRectangle rect);
    
    //! brief returns a JSON with the information of the Layer
    ofJson encode();
};

//! @class LayerStack
//! @abstract Implements a stack of layers
class LayerStack: public VisualsInterface {
    

    //! @var buffer
    //! @abstract an FBO to render the layer stack
    ofFbo buffer;
    
    //! @var width
    //! @abstract the width in pixels of the FBO
    float width;
    
    //! @var height
    //! @abstract the height in pixels of the FBO
    float height;
    
public:
    
    //! @var layers
    //! @abstract a vector with all layers in the stack
    std::vector<Layer *> layers;
    
    
    //! @brief Constructor
    //! @param _width the width of the FBO
    //! @param _height the height of the FBO
    LayerStack(float _width, float _height);
    
    //! @brief update the layer stack by rendering to the FBO
    void update();
    
    //! @brief update the layer stack by rendering to the FBO
    void draw();
    
    //! @brief draw the FBO in the specified rect
    //! @param rect
    void draw(ofRectangle rect);
    
    //! @brief add a new layer to the stack
    //! @param visual a pointer to a layer
    void insert(Layer* layer);
    
    //! @brief encode the data of the Layer stack into a JSON
    ofJson encode();
};
#endif

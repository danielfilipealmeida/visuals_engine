//
//  LayerStack.hpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 14/07/2025.
//

#ifndef LayerStack_h
#define LayerStack_h

#include "Layer.hpp"



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
    //! @param rect - the rectangle where to draw
    void draw(ofRectangle rect);
    
    
    //! @brief add a new layer to the stack
    //!
    //! @param layer -  a pointer to a layer
    void insert(Layer* layer);
    
    /// \brief Set the visual running on a layer
    void setVisualForLayer(unsigned int layerNumber, VisualsInterface *visual);
    
    //! @brief encode the data of the Layer stack into a JSON
    ofJson encode();
    
    void play() {};
    void stop() {};
};


#endif /* LayerStack_h */

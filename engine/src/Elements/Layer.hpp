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
public:
    
    //! @var alpha
    //! @abstract the transparency value, from 0.0 to 1.0
    float alpha;
    
    //! @var visual
    //! @abstract pointer to the visual
    VisualsInterface* visual;
    
    //! @var blendMode
    //! @abstract defines which blend mode used to draw the visual in the layer
    ofBlendMode blendMode;
    

    
    //! @brief Layer constructor.
    //!
    //! @param bufferWidth - the width
    //! @param bufferHeight - the height
    //! @param _visual -  the visual to display on the layer
    //! @param _alpha - the transparency of the layer
    //! @param _blendMode - which blend mode used to draw the layer
    Layer(
          float bufferWidth,
          float bufferHeight,
          VisualsInterface* _visual = NULL,
          float _alpha = 1,
          ofBlendMode _blendMode = OF_BLENDMODE_ADD
          );
    
    /// \brief Layer Destructor
    ~Layer();
    
    /// \brief create a new layer from a json
    ///
    /// \param json  - the json data
    static Layer* FromJson(ofJson json);
    
    //! @brief updates the visual
    //! @discussion will return if visual is null
    void update();
    
    //! @brief draws the visual with the blend mode and transparency
    //! @discussion will leave if visual is null
    void draw();

    
    //! @brief draws the visual in a specified rectangular area
    //! @param rect the rectangle
    void draw(ofRectangle rect);

    
    /// \brief returns a json containing the serialized information of the Layer
    ///
    /// \returns a json representation
    ofJson encode();
    
    
    /// \brief sets the running visual
    ///
    /// \param _visual - the visual that will be running on the the layer
    void set(VisualsInterface* _visual);
    
    void play() {};
    void stop() {};
};

#endif

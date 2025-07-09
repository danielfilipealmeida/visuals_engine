//
//  BaseClasses.hpp
//  emptyExample
//
//  Created by Daniel Almeida on 26/12/2024.
//

#ifndef BaseClasses_hpp
#define BaseClasses_hpp

#include "ofMain.h"


/// @brief base-class/interface for all classes that will be drawed on-screen
///
/// All classes that will be drawn should inherit from Drawable and implement all the virtual virtual methods
class Drawable {
public:
    ofRectangle rect;
    
    /// @brief Executed on every frame, before drawing.
    ///
    /// All major processing should be done here, while the draw function should just draw the frame that generated here
    ///
    /// @note This virtual method must be implemented on the class that inherits this class
    virtual void update() = 0;
    
    /// @brief Draws the object
    ///
    /// This method for drawing the has no rectangle parameters, so it will use de stored rectangle in `this.rect`.
    ///
    /// @note This virtual method must be implemented on the class that inherits this class
    virtual void draw() = 0;
    
    /// @brief Draws the object
    ///
    /// The Draw function should be executed on every frame and will draw the content of the drawable object. This is executed on the main application `draw()`
    /// function. This `draw` method has the rectangle as a parameter and will use this instead of the internal `this.rect`.
    ///
    /// @param _rect - the rectangular area where to draw into
    ///
    /// @note This virtual method must be implemented on the class that inherits this class
    virtual void draw(ofRectangle _rect) = 0;
    
#pragma mark Drawable - methods that are shared across all classes
    
    /// @brief Sets internal rectangle definition
    ///
    /// Sets the internal `this.rect` variable, that is used with `this.draw()`.
    ///
    /// @param _rect - the rectangular area where to draw into
    ///
    /// @note This virtual method must be implemented on the class that inherits this class
    void setRect(ofRectangle _rect) {
        this->rect = _rect;
    }
};


/// @brief Interface that defines a method for returning the information of the object on a JSON
class Encodable {
public:
    /// @brief Generate an `ofJson` with the contents of the object that inherented this class
    /// @note This virtual method must be implemented on the class that inherits this class
    virtual ofJson encode() = 0;
};


/// @brief gathers all interfaces needed for a Visual
/// 
/// all visuals (video-player, mixer. layers, generators) should inherit this class
class VisualsInterface: public Drawable, public Encodable {
};





#endif

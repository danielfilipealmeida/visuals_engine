//
//  BaseClasses.hpp
//  emptyExample
//
//  Created by Daniel Almeida on 26/12/2024.
//

#ifndef BaseClasses_hpp
#define BaseClasses_hpp

#include "ofMain.h"

class Drawable {
public:
    ofRectangle rect;
    
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void draw(ofRectangle _rect) = 0;
    
    // methods that are shared across all classes
    void setRect(ofRectangle rect) {
        this->rect = rect;
    }
};

/// \brief Interface that defines a method for returning the information of the object on a JSON
class Encodable {
public:
    virtual ofJson encode() = 0;
};

class VisualsInterface: public Drawable, public Encodable {
};





#endif

//
//  Elements.hpp
//  emptyExample
//
//  Created by Daniel Almeida on 29/12/2024.
//

#ifndef __ui_elements_hpp__
#define __ui_elements_hpp__

#include "ofMain.h"
#include "vector"

namespace UI {

#define DEFAULT_UI_ELEMENT_HEIGHT 28
#define DEFAULT_UI_PADDING 2
 
enum class ElementTypes {
    Container,
    Button,
    Slider,
    Label,
    TextBox
};

struct Element {
    ElementTypes type;
    ofRectangle rect;
    float padding = DEFAULT_UI_PADDING;
    float height = DEFAULT_UI_ELEMENT_HEIGHT;
    
    virtual ~Element() = default;
};




struct Container: Element {
    std::vector<Element*> children;
    
    void calculate() {
        float currentY = rect.y;
        for(Element *element : children) {
            currentY = currentY + element->padding;
            
            element->rect = ofRectangle(
                                       rect.x + element->padding,
                                       rect.y + currentY,
                                       rect.width - (element->padding * 2),
                                       element->height
                                       );
            currentY = currentY + element->height + element->padding;
        }
    };
    
    void add(Element* element) {
        children.push_back(element);
    }
};

struct Button: Element {
    string title;
};

struct ElementBuilder {
public:
    static Button* Button(string title) {
        struct Button *newButton;
        newButton = new Button();
        newButton->title = title;
        
        return newButton;
    }
};

}


#endif

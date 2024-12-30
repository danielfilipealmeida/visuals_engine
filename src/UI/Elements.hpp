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
#include "Primitives.hpp"

namespace UI {
    
#define DEFAULT_UI_ELEMENT_HEIGHT 28
#define DEFAULT_UI_PADDING 4
    
    /// \brief Defines the possible states of UI elements
    enum class ElementState {
        Idle,
        Hover,
        Clicked,
        InUse
    };
    
    /// \brief the Base class for UI Elements. Gathers all common variables
    class Element {
    public:
        ElementState state;
        ofRectangle rect;
        float padding = DEFAULT_UI_PADDING;
        float height = DEFAULT_UI_ELEMENT_HEIGHT;
        
        virtual ~Element() = default;
        virtual void draw(Primitives primitives) {};
    };
    
    /// \brief An UI Element that Contains other Elements
    class Container: public Element {
    public:
        std::vector<Element*> children;
        
        void calculate() {
            float currentY = rect.y;
            for(Element* element : children) {
                const float padding = element->padding;
                currentY = currentY + element->padding;
                const float height = element->height;
                
                element->rect = ofRectangle(
                                            rect.x + padding,
                                            rect.y + currentY,
                                            rect.width - (padding * 2),
                                            height
                                            );
                currentY = currentY + height + padding;
            }
        };
        
        void add(Element* element) {
            children.push_back(element);
        }
        
        void draw(Primitives primitives) {
            for(Element* element: children) {
                element->draw(primitives);
            }
        }
    };
    
    class Button: public Element {
    public:
        string title;
        
        Button(string _title) {
            title = _title;
        }
        void draw(Primitives primitives) {
            primitives.button(rect, title);
        }
    };
    
    class Slider: public Element {
    public:
        string caption;
        float value, max, min;
        
        Slider(string _caption, float _value, float _min=0.0, float _max=1.0) {
            caption = _caption;
            min = _min;
            max = _max;
            setValue(_value);
        }
        void setValue(float _value) {
            value = ofClamp(_value, min, max);
        }
        void draw(Primitives primitives) {
            primitives.slider(rect, caption, value, min, max);
        }
    };
    
    class TextBox: public Element {
    public:
        string value;
        TextBox(string _value){
            value = _value;
        }
        void draw(Primitives primitives) {
            primitives.textBox(rect, value);
        }
    };
    
    class Label: public Element {
    public:
        string caption;
        Label(string _caption){
            caption = _caption;
        }
        void draw(Primitives primitives) {
            primitives.label(rect, caption);
        }
    };
    
    
}


#endif

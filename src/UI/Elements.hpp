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

#define DEFAULT_UI_ELEMENT_HEIGHT 24
#define DEFAULT_UI_PADDING 4

/// \brief Defines the possible states of UI elements
enum class ElementState {
    Idle,
    Hover,
    MouseDown,
    Clicked,
    Dragged,
    InUse
};

/// \brief the Base class for UI Elements. Gathers all common variables
class Element {
public:
    ElementState state;
    ofRectangle rect;
    float padding = DEFAULT_UI_PADDING;
    float height = DEFAULT_UI_ELEMENT_HEIGHT;
    int previousMouseX, previousMouseY;
    bool previousButton1 = false, previousButton2 = false;
    std::function<void(Element*)> callback;
    bool expandY = false;
    
    virtual ~Element() = default;
    virtual void draw(Primitives primitives) {};
    virtual void update(int mouseX, int mouseY, bool button1, bool button2);
    ofColor getBackgroundColorForState(Primitives primitives, ElementState state);
};

/// \brief An UI Element that Contains other Elements
class Container: public Element {
public:
    std::vector<Element*> children;
    void calculate();
    void add(Element* element);
    void draw(Primitives primitives);
    void update(int mouseX, int mouseY, bool button1, bool button2);
};


/// \brief Implement a mechanism to divide horizontally the screen and have several columns of widgets
class HorizontalSplitter: public Container {
    std::vector<std::pair<Container*, float>> columns;
public:
    HorizontalSplitter();
    void addColumn(Container* container, float size);
    void calculate();
    void draw(Primitives primitives);
    void update(int mouseX, int mouseY, bool button1, bool button2);
};


/// \brief Template function to return a container already populated with its children
template<typename T>
T *CREATE(std::vector<Element*> children) {
    T *container = new T();
    
    for(auto child : children) {
        container->add(child);
    }
    
    return container;
};

/*

template<>
HorizontalSplitter *CREATE<HorizontalSplitter>(std::vector<Element*> children) {
    HorizontalSplitter *container = new HorizontalSplitter();
    
    for(auto child : children) {
        container->addColumn(static_cast<Container*>(child), 1.0 / (float) children.size());
    }
    
    return container;
}
 */


/// \brief Implements all the logic needed to draw and handle a button
class Button: public Element {
   
    
public:
    string title;
    
    Button(string _title, std::function<void(Element*)> _callback);
    void draw(Primitives primitives);
    void update(int mouseX, int mouseY, bool button1, bool button2);
};

/// \brief Implements all the logic needed to draw and handle a slider
class Slider: public Element {
public:
    string caption;
    float value, max, min;
    
    Slider(string _caption, float _value,  float _min=0.0, float _max=1.0,  std::function<void(Element*)> _callback = 0
           );
    void setValue(float _value);
    void draw(Primitives primitives);
    void update(int mouseX, int mouseY, bool button1, bool button2);
};

/// \brief Implements all the logic needed to draw and handle a cross fader, which is a special case of a slider
class CrossFader : public Slider {
public:
    CrossFader(string _caption,
               std::function<void(Element*)> _callback = 0
               ) : Slider(_caption, 0.0, -1.0, 1.0, _callback) {}
    void draw(Primitives primitives);
};

/// \brief Implements all the logic needed to draw and handle a text box
class TextBox: public Element {
public:
    string value;
    TextBox(string _value);
    void draw(Primitives primitives);
};

/// \brief Implements all the logic needed to draw and handle a label
class Label: public Element {
public:
    string caption;
    Label(string _caption);
    void draw(Primitives primitives);
};

class VSpacer: public Element {
public:
    VSpacer() {
        expandY = true;
    }
};

/// \brief A Template to be able to draw any object with a `draw` method and a `rect` inside an `ofRectangle` without changing the aspect Ratio
template<typename T>
void DrawInsideRect(T *obj, ofRectangle rect) {
    float objAspectRatio = obj->rect.width / obj->rect.height;
    float rectAspectRatio = rect.width / rect.height;
    
    float drawWidth, drawHeight;
    
    if (objAspectRatio > rectAspectRatio) {
        // FBO is wider than the rect
        drawWidth = rect.getWidth();
        drawHeight = drawWidth / objAspectRatio;
    } else {
        // FBO is taller or the same aspect ratio as the rect
        drawHeight = rect.getHeight();
        drawWidth = drawHeight * objAspectRatio;
    }
    
    // Calculate position to center the FBO inside the rectangle
    float x = rect.getX() + (rect.getWidth() - drawWidth) / 2.0f;
    float y = rect.getY() + (rect.getHeight() - drawHeight) / 2.0f;
    
    // Draw the FBO
    obj->draw(ofRectangle(x, y, drawWidth, drawHeight));
}

/// \brief Template to create a UI Element to draw any OpenFrameworks object that has a `draw` method
template <class T>
class Viewer : public Element {
public:
    T *obj;
    string title;
    
    Viewer(T *_obj, string _title="", float _height = NULL) {
        obj =  _obj;
        title = _title;
        if (height) {
            height = _height;
        }
    };
    void draw(Primitives primitives) {
        ofSetColor(0,0,0);
        ofDrawRectangle(rect);
        ofSetColor(255,255,255);
        DrawInsideRect(obj, rect);
        ofSetColor(255.255, 255);
        primitives.alignedText(primitives.shrinkRectangle(rect, 2), title, HorizontalAlign::Left, VerticalAlign::Top);
    };
    
};




}
#endif

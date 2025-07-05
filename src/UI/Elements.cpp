//
//  Elements.cpp
//  emptyExample
//
//  Created by Daniel Almeida on 01/01/2025.
//

#include "Elements.hpp"

using namespace UI;



// *****************************************
// Element
// *****************************************

void Element::update(int mouseX, int mouseY, bool button1, bool button2) {
    if (!rect.inside(mouseX, mouseY)) {
        state = ElementState::Idle;
        
    } else if (!button1) {
        state = previousButton1 ?  ElementState::Clicked : ElementState::Hover;
    }
    else {
        state = previousButton1 ? ElementState::Dragged : ElementState::MouseDown;
    }
    
    // last thing to do
    previousMouseX = mouseX;
    previousMouseY = mouseY;
    previousButton1 = button1;
    previousButton2 = button2;
}

ofColor Element::getBackgroundColorForState(Primitives primitives, ElementState state) {
    if (state == ElementState::Hover || state == ElementState::MouseDown || state == ElementState::Dragged) {
        return primitives.uiTemplate[TemplateField::HighlightedPrimaryColor];
    } else if (state == ElementState::Clicked) {
        return primitives.uiTemplate[TemplateField::DarkenPrimaryColor];
    }
    
    return primitives.uiTemplate[TemplateField::PrimaryColor];
}


// *****************************************
// Button
// *****************************************

Button::Button(string _title, std::function<void(Element*)> _callback = 0) {
    title = _title;
    callback = _callback;
}

void Button::draw(Primitives primitives) {
    ofColor bgColor = getBackgroundColorForState(primitives, state);
    primitives.button(rect, title, bgColor);
}

void Button::update(int mouseX, int mouseY, bool button1, bool button2) {
    Element::update(mouseX, mouseY, button1, button2);
    if (state == ElementState::Clicked && callback) {
        callback(this);
    }
}


// *****************************************
// Slider
// *****************************************

Slider::Slider(
               string _caption,
               float _value,
               float _min,
               float _max,
               std::function<void(Element*)> _callback
               ) {
    caption = _caption;
    min = _min;
    max = _max;
    observedValue = nullptr;
    setValue(_value);
    callback = _callback;
}

Slider::Slider(
       string _caption,
       float *value,
       float _min,
       float _max
       ) {
    caption = _caption;
    observedValue = value;
    setValue(*observedValue);
    max = _max;
    min = _min;
}

void Slider::setValue(float _value) {
    value = ofClamp(_value, min, max);
}

void Slider::draw(Primitives primitives) {
    ofColor bgColor = getBackgroundColorForState(primitives, state);
    
    /// Updates the slider''s value if it is set to be used in observer mode
    if(observedValue) {
        value = *observedValue;
    }
    
    primitives.slider(rect, caption, value, min, max, bgColor);
}

void Slider::update(int mouseX, int mouseY, bool button1, bool button2) {
    Element::update(mouseX, mouseY, button1, button2);
    if (state == ElementState::Idle || state == ElementState::Hover) {
        return;
    }
    
    const float percent = (mouseX - rect.x) / (rect.width);
    value = min + (max - min) * percent;
    
    if (state == ElementState::Clicked && callback) {
        callback(this);
    }
    
    if (observedValue) {
        *observedValue = value;
    }
}


// *****************************************
// Cross Fader
// *****************************************

void CrossFader::draw(Primitives primitives) {
    ofColor bgColor = getBackgroundColorForState(primitives, state);
    primitives.crossFader(rect, caption, value, bgColor);
}


// *****************************************
// Text Box
// *****************************************

TextBox::TextBox(string _value){
    value = _value;
}
void TextBox::draw(Primitives primitives) {
    primitives.textBox(rect, value);
}


// *****************************************
// Label
// *****************************************

Label::Label(string _caption){
    caption = _caption;
}
void Label::draw(Primitives primitives) {
    primitives.label(rect, caption);
}



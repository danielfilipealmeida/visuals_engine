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
// Container
// *****************************************

void Container::calculate() {
    std::vector<Element *>expandable;
    
    // get all expandables
    for(Element* element : children) {
        if (element->expandY) {
            expandable.push_back(element);
        }
    }
    
    std::function<float()> calculateChildrenRectsAndGetOccupiedHeight = [&](){
        float currentY = rect.y;
        
        int count = 0;
        for(auto element : children) {
            const float padding = element->padding;
            currentY = currentY + padding;
            const float height = element->height;
            
            element->rect = ofRectangle(rect.x + padding,rect.y + currentY, rect.width - (padding * 2), height);
            
            currentY = currentY + height + padding;
            
            count++;
            if (count == children.size()) {
                currentY = currentY - height;
            }
        }
        return currentY;
    };
    
    // do a first pass to get the fully ocupied height, without the elements that need to expand
    float occupiedHeight = calculateChildrenRectsAndGetOccupiedHeight();
    
    if (expandable.size() == 0 ) return;
    
    // calculate the height of the expandables
    float expandableHeight = (rect.height - occupiedHeight) / expandable.size();
    
    // exits if the height is negative. not space to expand
    if (expandableHeight < 0) {
        return;
    }
    
    for(Element* element : expandable) {
        element->height = expandableHeight;
    }
    
    // recalculate everything
    calculateChildrenRectsAndGetOccupiedHeight();
    
    // calculate all child that are also containers
    for(auto element : children) {
        
        HorizontalSplitter* hSplitter = dynamic_cast<HorizontalSplitter*>(element);
        if (hSplitter) {
            hSplitter->calculate();
            continue;
        }

        /* todo: add other specialized containers here */
    }
};

void Container::add(Element* element) {
    children.push_back(element);
}

void Container::draw(Primitives primitives) {
    for(Element* element: children) {
        element->draw(primitives);
    }
}

void Container::update(int mouseX, int mouseY, bool button1, bool button2) {
    for(Element* element: children) {
        element->update(mouseX, mouseY, button1, button2);
    }
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
    setValue(_value);
    callback = _callback;
}
void Slider::setValue(float _value) {
    value = ofClamp(_value, min, max);
}
void Slider::draw(Primitives primitives) {
    ofColor bgColor = getBackgroundColorForState(primitives, state);
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

// *****************************************
// Horizontal Splitter
// *****************************************

HorizontalSplitter::HorizontalSplitter() {
    padding = 0;
    expandY = true;
}
void HorizontalSplitter::addColumn(Container* container, float size) {
    columns.push_back({container, size});
}
void HorizontalSplitter::calculate() {
    float x = rect.x;
    for(auto column : columns) {
        float width = rect.width * column.second;
        column.first->rect = ofRectangle(x, rect.y, width, rect.height);
        x = x + width;
        column.first->calculate();
    }
}
void HorizontalSplitter::draw(Primitives primitives) {
    for(auto column : columns) {
        column.first->draw(primitives);
    }
}
void HorizontalSplitter::update(int mouseX, int mouseY, bool button1, bool button2) {
    for(auto column : columns) {
        column.first->update(mouseX, mouseY, button1, button2);
    }
}



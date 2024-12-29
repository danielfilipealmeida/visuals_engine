//
//  UI.cpp
//  emptyExample
//
//  Created by Daniel Almeida on 29/12/2024.
//

#include "UI.hpp"

using namespace UI;



void UserInterface::draw() {
    for(Element *element : children) {
        switch (element->type) {
            case ElementTypes::Container:
                
                break;
            case ElementTypes::Button:
                Button *button = dynamic_cast<Button*>(element);
                primitives.button(button->rect, button->title);
                break;
                /*
            case ElementTypes::Slider:
                
                break;
            case ElementTypes::Label:
                
                break;
            case ElementTypes::TextBox:
                
                break;
                 */
        }
    }
    
};

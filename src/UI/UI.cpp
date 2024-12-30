//
//  UI.cpp
//  emptyExample
//
//  Created by Daniel Almeida on 29/12/2024.
//

#include "UI.hpp"

using namespace UI;



void UserInterface::draw() {
    for(Element* element : children) {
        element->draw(primitives);
    }
    
};

//
//  Container.hpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 02/01/2025.
//

#ifndef __CONTAINERS_HPP__
#define __CONTAINERS_HPP__

#include "Elements.hpp"

namespace UI {

enum class ElementPackingDirection {
    Vertical,
    Horizontal
};

/// \brief An UI Element that Contains other Elements
class Container: public Element {
public:
    ElementPackingDirection packingDirection = ElementPackingDirection::Vertical;
    std::vector<Element*> children;
    
    void calculate();
    void add(Element* element);
    void draw(Primitives primitives);
    void update(int mouseX, int mouseY, bool button1, bool button2);
};


/// \brief Implement a mechanism to divide horizontally the screen and have several columns of widgets
class HorizontalSplitter: public Container {
public:
    std::vector<std::pair<Container*, float>> columns;
    
    HorizontalSplitter();
    void addColumn(Container* container, float size);
    void calculate();
    void draw(Primitives primitives);
    void update(int mouseX, int mouseY, bool button1, bool button2);
};


}


#endif


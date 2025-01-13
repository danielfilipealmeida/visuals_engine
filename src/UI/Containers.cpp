
#include "Containers.hpp"

using namespace UI;



// *****************************************
// Container
// *****************************************

float calculateChildrenRectsAndGetOccupiedHeight(
                                                 ofRectangle rect,
                                                 std::vector<Element *> children
                                                 ) {
    float currentY = rect.y;
    
    int count = 0;
    for(auto element : children) {
        const float padding = element->padding;
        currentY = currentY + padding;
        const float height = element->height;
        
        element->rect = ofRectangle(rect.x + padding,
                                    rect.y + currentY,
                                    rect
                                    .width - (padding * 2),
                                    height);
        
        currentY = currentY + height + padding;
        
        count++;
        if (count == children.size()) {
            currentY = currentY - height;
        }
    }
    return currentY;
};

void Container::calculate() {
    std::vector<Element *>expandable;
    
    // get all expandables
    for(Element* element : children) {
        if (element->expandY) {
            expandable.push_back(element);
        }
    }
    
    /*
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
     */
    
    // do a first pass to get the fully ocupied height, without the elements that need to expand
    float occupiedHeight = calculateChildrenRectsAndGetOccupiedHeight(rect, children);
    
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
    calculateChildrenRectsAndGetOccupiedHeight(rect, children);
    
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



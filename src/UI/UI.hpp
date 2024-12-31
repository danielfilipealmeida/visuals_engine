//
//  UI.hpp
//  emptyExample
//
//  Created by Daniel Almeida on 29/12/2024.
//

#ifndef __ui_ui_hpp__
#define __ui_ui_hpp__


#include "Elements.hpp"
#include "Primitives.hpp"
#include <vector>

namespace UI {

struct UserInterface: Container {
    Primitives primitives;
    
    void draw();

};


}


#endif

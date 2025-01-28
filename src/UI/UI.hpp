//
//  UI.hpp
//  emptyExample
//
//  Created by Daniel Almeida on 29/12/2024.
//

#ifndef __ui_ui_hpp__
#define __ui_ui_hpp__


#include "Elements.hpp"
#include "Containers.hpp"
#include "Primitives.hpp"
#include <vector>

namespace UI {

/// \brief The main class used to implement a User Inteface.
struct UserInterface: public Container {
    Primitives primitives;
    
    /// Draws the User Interface
    void draw();
};


}


#endif

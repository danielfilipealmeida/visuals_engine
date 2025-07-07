//
//  UserInterface.hpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 02/02/2025.
//



#ifndef __USER_INTERFACE_H__
#define __USER_INTERFACE_H__

#include "UI/UI.hpp"
#include "Mixer.hpp"
#include "Engine/Elements/Signals.hpp"
#include "State.hpp"

//! @brief Implements the User interface of the applicatication<D-s>
class UserInterface {
    
    //! @var ui
    //! @abstract the UserInterface object that is used to implement the UI
    UI::UserInterface ui;
    
    
    UI::HorizontalSplitter horizontalSplitter;
    UI::CrossFader *mixCrossfader;
    
    State *state;
public:
    
    /// Sets up the User Interface of the application
    void setup(
               ofRectangle rect,
               State *state
               );

    void setupPreviews();
    
    //! @brief Draws the user interface
    void draw();

    //! @brief Updated the user interface
    void update();

    //! @brief Resizes the user interface
    //! @param width the new width of the UI
    //! @param height the new height of the UI
    void resize(int width, int height);
    
};

#endif

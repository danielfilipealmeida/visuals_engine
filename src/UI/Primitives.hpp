//
//  Elements.hpp
//  emptyExample
//
//  Created by Daniel Almeida on 28/12/2024.
//


#ifndef __ui_primitives_hpp__
#define __ui_primitives_hpp__

#include "ofMain.h"

namespace UI {
    
#define DEFAULT_FONT_SIZE 11


enum class HorizontalAlign {
    Left, Center, Right
};

enum class VerticalAlign {
    Top, Center, Bottom
};

enum class TemplateField {
    PrimaryColor,
    BackgroundColor,
    SecundaryColor,
    HighlightedPrimaryColor,
    DarkenPrimaryColor,
    TextColor
};

class Primitives {
    ofTrueTypeFont font;
        
public:
    
    std::map<TemplateField, ofColor> uiTemplate;
    
    Primitives();
    
    // Drawing helpers
    
    /// \brief Draws a string in the middle of a rect.
    ///
    /// \param rect
    /// \param text
    void centeredText(ofRectangle rect, string text);
    
    /// \brief Writes text aligned vertically and horizontally
    ///
    /// \param rect
    /// \param text
    /// \param hAlign
    /// \param vAlign
    void alignedText(ofRectangle rect, string text, HorizontalAlign hAlign, VerticalAlign vAlign);
    
    /// \brief Shrinks a rectangle from the center by the amount of pixels specified
    ///
    ///  \param rect
    ///  \param pixels
    ofRectangle shrinkRectangle(ofRectangle rect, float pixels);
    
    // Widgets
    
    /// \brief Draws a button
    ///
    /// \param rect
    /// \param title
    /// \param bgColor
    void button(ofRectangle rect, string title, ofColor bgColor);
    
    
    /// \brief draws a silder
    ///
    /// \param rect
    /// \param title
    /// \param value
    /// \param min
    /// \param max
    void slider(ofRectangle rect, string title, float value, float min, float max, ofColor bgColor);
    
    /// \brief draws a crossfader, with values from -1 to 1
    ///
    /// \param rect
    /// \param title
    /// \param value
    /// \param min
    /// \param max
    void crossFader(ofRectangle rect, string title, float value, ofColor bgColor);
    
    /// \brief Draw a text box
    ///
    /// \param rect
    /// \param text
    void textBox(ofRectangle rect, string text);
    
    
    /// \brief Draw a label
    ///
    /// \param rect
    /// \param text
    /// \param align
    void label(ofRectangle rect,
                           string text,
               HorizontalAlign align = HorizontalAlign::Left);
    
    // other methods
    
    /// \brief sets the default colors to the UI
    void setDefaultTemplate();
    
    /// \brief Calculate the template and updates it
    ///
    /// \param primaryColor
    /// \param secundaryColor
    /// \param textColor
    /// \param backgroundColor
    /// \param contrast
    void generateTemplate(ofColor primaryColor,
                          ofColor secundaryColor,
                          ofColor textColor,
                          ofColor backgroundColor,
                          float contrast
                          );
    
};

}

#endif

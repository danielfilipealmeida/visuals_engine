//
//  Elements.cpp
//  emptyExample
//
//  Created by Daniel Almeida on 28/12/2024.
//


#include "Primitives.hpp"

using namespace UI;

Primitives::Primitives() {
    ofTrueTypeFont::setGlobalDpi(72);
    font.load("OpenSans-Regular.ttf", DEFAULT_FONT_SIZE, true, false, false);
    setDefaultTemplate();
    font.setLetterSpacing(1.037);
    font.setLineHeight(DEFAULT_FONT_SIZE+4);
};


void Primitives::centeredText(ofRectangle rect, string text) {
    ofRectangle stringRect = font.getStringBoundingBox(text, 0,0);
    float x, y;
    
    x = (rect.width - stringRect.width) / 2.0 + rect.x;
    y = (rect.height - stringRect.height ) / 2.0 + rect.y + (font.getLineHeight() / 2);
    
    font.drawString(text,x, y);
}

ofRectangle Primitives::shrinkRectangle(ofRectangle rect, float pixels) {
   
    ofRectangle result;
    
    result.setWidth(rect.getWidth() - 2 * pixels);
    result.setHeight(rect.getHeight() - 2 * pixels);
    
    // Adjust the position to maintain the center
    result.setX(rect.getX() + pixels);
    result.setY(rect.getY() + pixels);
    
    return result;
}

void Primitives::alignedText(ofRectangle rect, string text, HorizontalAlign hAlign, VerticalAlign vAlign)
{
    ofRectangle stringRect = font.getStringBoundingBox(text, 0,0);
    float x, y;
    
    switch (hAlign) {
        case HorizontalAlign::Left:
            x = rect.x;
            break;
            
        case HorizontalAlign::Center:
            x = (rect.width - stringRect.width) / 2.0 + rect.x;
            break;
            
        case HorizontalAlign::Right:
            x = rect.x + rect.width - stringRect.width;
            break;
    }
    
    switch (vAlign) {
        case VerticalAlign::Top:
            y = rect.y + font.getLineHeight();
            break;
            
        case VerticalAlign::Center:
            y = (rect.height - stringRect.height ) / 2.0 + rect.y + (font.getLineHeight() / 2);
            break;
            
        case VerticalAlign::Bottom:
            y = rect.y + rect.height;
            break;
    }
    
    font.drawString(text,x, y);
}




void Primitives::button(
                        ofRectangle rect,
                        string title,
                        ofColor bgColor
                        ) {
    ofSetColor(bgColor);
    ofDrawRectangle(rect);
    ofSetColor(uiTemplate[TemplateField::TextColor]);
    centeredText(rect, title);
}

void Primitives::slider(ofRectangle rect, string title, float value, float min, float max, ofColor bgColor) {
    const float amount = value / (max - min) ;
    const float valueX = rect.width * amount;
    
    ofSetColor(bgColor);
    ofDrawRectangle(rect.x, rect.y, valueX, rect.height);
    
    ofSetColor(uiTemplate[TemplateField::BackgroundColor]);
    ofDrawRectangle(rect.x + valueX, rect.y, rect.width - valueX, rect.height);
    
    ofSetColor(uiTemplate[TemplateField::TextColor]);
    alignedText(shrinkRectangle(rect, 4),
                title,
                HorizontalAlign::Left,
                VerticalAlign::Center);
}

void Primitives::crossFader(ofRectangle rect, string title, float value, ofColor bgColor) {
    const float amount = (value + 1) / 2.0 ;
    const float valueX = (rect.width -2) * amount;
    
    ofSetColor(uiTemplate[TemplateField::BackgroundColor]);
    ofDrawRectangle(rect);
    
    ofSetColor(bgColor);
    ofDrawRectangle(rect.x + valueX
                     + 1, rect.y, 3, rect.height);
    
    ofSetColor(uiTemplate[TemplateField::TextColor]);
    alignedText(rect, title, HorizontalAlign::Center, VerticalAlign::Center);
}


void Primitives::textBox(ofRectangle rect, string text) {
    ofSetColor(uiTemplate[TemplateField::BackgroundColor]);
    ofDrawRectangle(rect);
    ofSetColor(uiTemplate[TemplateField::TextColor]);
    
    alignedText(shrinkRectangle(rect, 4),
                text,
                HorizontalAlign::Left,
                VerticalAlign::Center);
}

void Primitives::label(ofRectangle rect,
                       string text,
                       HorizontalAlign align) {
    ofSetColor(uiTemplate[TemplateField::TextColor]);
    alignedText(rect, text, align, VerticalAlign::Center);
}


void Primitives::setDefaultTemplate() {
    const ofColor primaryColor = ofColor::darkSlateBlue;
    const ofColor secundaryColor = ofColor::saddleBrown;
    const ofColor backgroundColor = ofColor::black;
    const ofColor textColor = ofColor::white;
    const float brightness = 50;
    
    generateTemplate(primaryColor,
                     secundaryColor,
                     textColor,
                     backgroundColor,
                     brightness);
}

void Primitives::generateTemplate(ofColor primaryColor,
                      ofColor secundaryColor,
                      ofColor textColor,
                      ofColor backgroundColor,
                      float brightness
                      ) {
    uiTemplate[TemplateField::PrimaryColor] = primaryColor;
    uiTemplate[TemplateField::SecundaryColor] = secundaryColor;
    uiTemplate[TemplateField::BackgroundColor] = backgroundColor;
    uiTemplate[TemplateField::HighlightedPrimaryColor] = primaryColor + brightness;
    uiTemplate[TemplateField::DarkenPrimaryColor] = primaryColor - brightness;
    uiTemplate[TemplateField::TextColor] = textColor;
}



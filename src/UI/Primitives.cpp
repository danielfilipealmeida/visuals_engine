//
//  Elements.cpp
//  emptyExample
//
//  Created by Daniel Almeida on 28/12/2024.
//


#include "Primitives.hpp"

using namespace UI;

Primitives::Primitives() {
    font.load("OpenSans-Regular.ttf", 10);
    setDefaultTemplate();
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




void Primitives::button(ofRectangle rect, string title) {
    ofSetColor(uiTemplate[TemplateField::PrimaryColor]);
    ofDrawRectangle(rect);
    ofSetColor(uiTemplate[TemplateField::TextColor]);
    centeredText(rect, title);
}

void Primitives::slider(ofRectangle rect, string title, float value, float min, float max) {
    const float amount = value / (max - min) ;
    const float valueX = rect.width * amount;
    
    ofSetColor(uiTemplate[TemplateField::PrimaryColor]);
    ofDrawRectangle(rect.x, rect.y, valueX, rect.height);
    
    ofSetColor(uiTemplate[TemplateField::BackgroundColor]);
    ofDrawRectangle(rect.x + valueX, rect.y, rect.width - valueX, rect.height);
    
    ofSetColor(uiTemplate[TemplateField::TextColor]);
    alignedText(rect, title, HorizontalAlign::Center, VerticalAlign::Center);
}

void Primitives::textBox(ofRectangle rect, string text) {
    ofSetColor(uiTemplate[TemplateField::BackgroundColor]);
    ofDrawRectangle(rect);
    ofSetColor(uiTemplate[TemplateField::TextColor]);
    
    alignedText(shrinkRectangle(rect, 2),
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
    const ofColor primaryColor = ofColor::orange;
    const ofColor secundaryColor = ofColor::saddleBrown;
    const ofColor backgroundColor = ofColor::black;
    const ofColor textColor = ofColor::white;
    const float contrastFactor = 0.3;
    
    generateTemplate(primaryColor,
                     secundaryColor,
                     textColor,
                     backgroundColor,
                     contrastFactor);
}

void Primitives::generateTemplate(ofColor primaryColor,
                      ofColor secundaryColor,
                      ofColor textColor,
                      ofColor backgroundColor,
                      float contrast
                      ) {
    uiTemplate[TemplateField::PrimaryColor] = primaryColor;
    uiTemplate[TemplateField::SecundaryColor] = secundaryColor;
    uiTemplate[TemplateField::BackgroundColor] = backgroundColor;
    uiTemplate[TemplateField::HighlightedPrimaryColor] = primaryColor * contrast;
    uiTemplate[TemplateField::HighlightedPrimaryColor] = primaryColor / contrast;
    uiTemplate[TemplateField::TextColor] = textColor;
}

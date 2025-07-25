//
//  ofxGuiBuffer.hpp
//  Hello World
//
//  Created by Daniel Almeida on 09/07/2025.
//

#ifndef ofxGuiBuffer_h
#define ofxGuiBuffer_h

#include "ofxBaseGui.h"

template<typename T>
class DrawableGuiElement : public ofxBaseGui {
    T element;
    string caption;
    ofParameter<string> param;
    ofVboMesh textMesh;
public:
    DrawableGuiElement(){}
    DrawableGuiElement(T _element, string caption, float width = defaultWidth, float height = defaultWidth * 2.0 / 3.0) {
        setup(_element, caption, width, height);
    }
    
    DrawableGuiElement* setup(T _element, string _caption, float width = defaultWidth, float height = defaultHeight) {
        element = _element;
        caption = _caption;
        b.width = width;
        b.height = height;
        setNeedsRedraw();
        
        return this;
    }
    
    // Abstract methods we must implement, but have no need for!
    bool mouseMoved(ofMouseEventArgs & args){return false;}
    bool mousePressed(ofMouseEventArgs & args){return false;}
    bool mouseDragged(ofMouseEventArgs & args){return false;}
    bool mouseReleased(ofMouseEventArgs & args){return false;}
    bool mouseScrolled(ofMouseEventArgs & args){return false;}
    bool setValue(float mx, float my, bool bCheckBounds){return false;}
    void generateDraw(){}
    
    ofRectangle scaleFromCenterPixes(ofRectangle rect, int pixels){
        ofRectangle result = rect;
        result.x-=pixels;
        result.y-=pixels;
        result.width+=2*pixels;
        result.height+=2*pixels;
        
        return result;
    }
    
    void render() {
        if (element) {
            ofDisableAlphaBlending();
            ofSetColor(255,255,255,0);
            element->draw(b);
        }
        
        
        // draw the caption
        ofRectangle captionBoundingBox = getTextBoundingBox(caption, b.x + textPadding, b.y);
        captionBoundingBox.y += textPadding + captionBoundingBox.getHeight();
        ofSetColor(thisBackgroundColor);
        ofDrawRectangle(scaleFromCenterPixes(captionBoundingBox, 2));
        ofSetColor(thisTextColor);
        textMesh = getTextMesh(caption, b.x + textPadding, b.y + textPadding + captionBoundingBox.getHeight());
        bindFontTexture();
        textMesh.draw();
        unbindFontTexture();
    }
    
    ofAbstractParameter & getParameter(){
        return param;
    }
    
    void valueChanged(string & value){
        setNeedsRedraw();
    }
};

#endif /* ofxGuiBuffer_h */

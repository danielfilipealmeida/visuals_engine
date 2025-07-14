//
//  Keyboard.h
//  VisualsEngine
//
//  Created by Daniel Almeida on 14/07/2025.
//

#ifndef Keyboard_h
#define Keyboard_h

class Keyboard {
public:
    bool debug = false;
    
    std::map<int, std::function<void((int))>> keyHandlers;
    
    Keyboard(const MIDI&) = delete;
    Keyboard& operator=(const Keyboard&) = delete;
    
    /// \brief Returns the instance of the MIDI singleton
    static Keyboard& getInstance() {
        static Keyboard instance;
        return instance;
    }
    
    
    /// \brief adds a new callback assigned to a key
    ///
    /// \param key - an integer refering the key that will trigger the lambda
    /// \param lambra - an anonymous function that is executed when the key is press. will have the key value as input
    void add(int key, std::function<void((int))> handler) {
        keyHandlers[key] = handler;
    }
    
    
    /// \brief removes the handler from the map
    ///
    /// \param key - the key to be removed
    void remove(int key) {
        keyHandlers.erase(key);
    }
    
    
    /// \brief handles the key press by executing the assigned lambda
    ///
    /// \param key - the key that is set to be handled
    void handle(int key) {
        if (debug) {
            ofLog(OF_LOG_NOTICE, "Key: " + std::to_string(key));
        }
        
        if (keyHandlers.find(key) == keyHandlers.end()) {
            return;
        }
        
        std::function<void((int))> handler = keyHandlers[key];
        handler(key);
    }
    
private:
    
    Keyboard() {
        ofLog(OF_LOG_NOTICE, "Keyboard Singleton instantiated");
    }
};

#endif /* Keyboard_h */

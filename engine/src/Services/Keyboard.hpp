//
//  Keyboard.h
//  VisualsEngine
//
//  Created by Daniel Almeida on 14/07/2025.
//

#ifndef Keyboard_h
#define Keyboard_h

enum Key {
    a = 97,
    b = 98,
    c = 99,
    d = 100,
    e = 101,
    f = 102,
    g = 103,
    h = 104,
    i = 105,
    j = 106,
    k = 107,
    l = 108,
    m = 109,
    n = 110,
    o = 111,
    p = 112,
    q = 113,
    r = 114,
    s = 115,
    t = 116,
    u = 117,
    v = 118,
    w = 119,
    x = 120,
    y = 121,
    z = 122,
    
    _0 = 48,
    _1 = 49,
    _2 = 50,
    _3 = 51,
    _4 = 52,
    _5 = 53,
    _6 = 54,
    _7 = 55,
    _8 = 56,
    _9 = 57
};


/// \brief Singleton class to handle keyboard globally on an application
class Keyboard {
public:
    bool debug = false;
    
    std::map<int, std::function<void((int))>> keyHandlers;
    
    /// \brief The default keys used to trigger visuals
    /// todo: create an enum with the keys
    const std::vector<unsigned int> defaultVisualsTriggerKeys = {Key::q, Key::w, Key::e, Key::r};
    const std::vector<unsigned int> defaultLayersTriggerKeys = {Key::_1, Key::_2, Key::_3};
    const std::vector<unsigned int> defaultChannelTriggerKey = {Key::z, Key::x};
    Keyboard(const Keyboard&) = delete;
    Keyboard& operator=(const Keyboard&) = delete;
    
    
    
    /// \brief Returns the instance of the Keyboad singleton
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

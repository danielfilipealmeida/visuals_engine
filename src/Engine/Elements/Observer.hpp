//
//  Observer.hpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 02/02/2025.
//

#ifndef __OBSERVER_H__
#define __OBSERVER_H__


template<class T>
class Observer {
public:
    virtual void update(T val, std::string key) {}
};

// todo: add third element to the vector, which is the transform.
// this is a lambda that can be used to operate on the value.
// if no lambda is set, use the value directly
template<class T>
class Subject {
    std::vector<std::pair<Observer<T> *, std::string>> observers;
    
public:
    void regist(Observer<T> *observer, std::string key) {
        observers.push_back({observer, key});
    };
    
    void notify(T val) {
        for(const auto& pair: observers) {
            pair.first->update(val, pair.second);
        }
    };    
};

#endif

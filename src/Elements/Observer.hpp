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
    virtual void update(T val) {}
};

template<class T>
class Subject {
    std::vector<Observer<T> *> observers;
    
public:
    void regist(Observer<T> *observer) {
        observers.push_back(observer);
    };
    
    void notify(T val) {
        for(Observer<T>* observer : observers) {
            observer->update(val);
        }
    };
    
};



#endif

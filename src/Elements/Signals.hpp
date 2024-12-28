//
//  Signals.hpp
//  emptyExample
//
//  Created by Daniel Almeida on 28/12/2024.
//

#ifndef __Signals_hpp__
#define __Signals_hpp__

#include <cmath>

template<class T>
class Signal {
private:
    T value;
    std::function<T()> calculator;
public:
    void setCalculator(std::function<T()> _calculator) {
        calculator = _calculator;
    }
    void update() {
        value = calculator();
    }
    T getValue() {
        return value;
    }
};



class SignalsBuilder {
    
public:
    static Signal<float> SineWave(float freq = 1, float amplitude = 1, float phase=0){
        Signal<float> signal;
        signal.setCalculator(SignalsBuilder::getSineWaveCalculator(freq, amplitude, phase));
        
        return signal;
    }
    
    static Signal<float> SquareWave(float freq = 1, float amplitude = 1, float phase=0){
        Signal<float> signal;
        signal.setCalculator(SignalsBuilder::getSquareWaveCalculator(freq, amplitude, phase));
        
        return signal;
    }
    
    
    /// \brief Returns a lambda configured to produce a sinewave
    ///
    /// This is a wrapper around the std::sin function.
    ///
    /// \param freq The frequency of the sinewave
    /// \param amplitude The amplitude of the sinewave
    /// \param phase The false of the sinewave
    ///
    /// \returns a lambda already configured
    static std::function<float()> getSineWaveCalculator(float freq = 1, float amplitude = 1, float phase=0) {
        return [&](float freq = 1, float amplitude = 1, float phase=0) {
            float time = ((float) ofGetElapsedTimef());
            float result = amplitude * std::sin(2.0 * M_PI * freq * time + phase);
            
            return result;
        };
    }
    
    /// \brief Returns a lambda configured to produce a squarewave
    ///
    /// This uses std::sin function.
    ///
    /// \param freq The frequency of the sinewave
    /// \param amplitude The amplitude of the sinewave
    /// \param phase The false of the sinewave
    ///
    /// \returns a lambda already configured
    static std::function<float()> getSquareWaveCalculator(float freq = 1, float amplitude = 1, float phase=0) {
        return [&](float freq = 1, float amplitude = 1, float phase=0) {
            float time = ((float) ofGetElapsedTimef());
            float sine = amplitude * std::sin(1.0 * M_PI * freq * time + phase);
            float result = amplitude * (sine>0 ? 1 : -1);
            
            return result;
        };
        
    }
};

#endif

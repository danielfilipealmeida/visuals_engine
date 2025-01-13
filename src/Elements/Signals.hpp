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
    std::function<void(T)> callback;
public:
    void setCalculator(std::function<T()> _calculator) {
        calculator = _calculator;
    }
    void update() {
        value = calculator();
        if (callback) {
            callback(value);
        }
    }
    T getValue() {
        return value;
    }
    void setCallback(std::function<void(T)> _callback) {
        callback = _callback;
    }
};



class SignalsBuilder {
    
public:
    
    /// \brief Creates a sine wave signal
    ///
    /// \param freq
    /// \param amplitude
    /// \param phase
    ///
    /// \return the configured signal
    static Signal<float> SineWave(float freq = 1, float amplitude = 1, float phase=0){
        Signal<float> signal;
        signal.setCalculator(SignalsBuilder::getSineWaveCalculator(freq, amplitude, phase));
        
        return signal;
    }
    
    /// \brief Creates a square wave signal
    ///
    /// \param freq
    /// \param amplitude
    /// \param phase
    ///
    /// \return the configured signal
    static Signal<float> SquareWave(float freq = 1, float amplitude = 1, float phase=0){
        Signal<float> signal;
        signal.setCalculator(SignalsBuilder::getSquareWaveCalculator(freq, amplitude, phase));
        
        return signal;
    }
    
    /// \brief Creates a Random signal
    ///
    /// \param amplitude the amplitude of the signal, starting from 0 to amplitude
    /// \param sampleDuration the amount of seconds a random number is set
    ///
    /// \return the configured signal
    static Signal<float> Random(float amplitude = 1, float sampleDuration=0){
        Signal<float> signal;
        signal
            .setCalculator(SignalsBuilder::getRandomCalculator(amplitude, sampleDuration));
        
        return signal;
    }
    
    static Signal<float> Pulse(float freq = 1, float amplitude = 1, float dutyCycle = 0.1) {
        Signal<float> signal;
        signal.setCalculator(SignalsBuilder::getPulseCalculator(freq, amplitude, dutyCycle));
        
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
        return [freq, amplitude, phase]() {
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
        return [freq, amplitude, phase]() {
            float time = ((float) ofGetElapsedTimef());
            float sine = amplitude * std::sin(M_PI * freq * time + phase);
            float result = amplitude * (sine>0 ? 1 : -1);
            
            return result;
        };
    }
    
    /// \brief Returns a lambda that generates random numbers. This generator has a "sample-and-hold" functionality
    ///
    /// \param amplitude The amplitude of the noise, will return random numbers from 0 to amplitude
    /// \param sampleDuration the time a value will be hold by the calculator. in seconds
    ///
    /// \returns a lambda configured to produce a noise value
    static std::function<float()> getRandomCalculator(float amplitude=1, float sampleDuration=0) {
        return [amplitude, sampleDuration]() {
            static float lastTime;
            static float result;
            float diff = ofGetElapsedTimef() - lastTime;
            if (diff < sampleDuration) {
                return result;
            }
            
            result = ofRandom(amplitude);
            
            lastTime = ofGetElapsedTimef();
            return result;
        };
    }
    
    static std::function<float()> getPulseCalculator(float freq, float amplitude, float dutyCycle) {
        return [freq, amplitude, dutyCycle]() {
            float time = ((float) ofGetElapsedTimef());
            double period = 1.0 / freq;
            double modTime = fmod(time, period);
            return (modTime < dutyCycle * period) ? amplitude : 0.0;
        };
    }
};

#endif

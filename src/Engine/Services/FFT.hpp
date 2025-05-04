//
//  FFT.hpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 13/03/2025.
//

#ifndef __fft__
#define __fft__

#include "ofxFft.h"


/**!
 Class wrapper for ofxFft using a Singleton pattern
 */
class FFT {
    ofxFft* fft;
    int bufferSize;
    
    ofMutex soundMutex;
    vector<float> drawBins, middleBins, audioBins;
public:
    
    FFT(const FFT&) = delete;
    FFT& operator=(const FFT&) = delete;
    
    static FFT& getInstance() {
        static FFT instance;
        return instance;
    }
    
    void setup(int bufferSize) {
        this->bufferSize = bufferSize;
        
        fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_HAMMING);
        audioBins.resize(bufferSize);
        middleBins.resize(bufferSize);
        
    }
    
    void setSignal(vector<float> signal) {
        fft->setSignal(signal);
        
        float maxValue = 0;
        float* curFft = fft->getAmplitude();
        memcpy(&audioBins[0], curFft, sizeof(float) * fft->getBinSize());
        
        for(int i = 0; i < fft->getBinSize(); i++) {
            if(abs(audioBins[i]) > maxValue) {
                maxValue = abs(audioBins[i]);
            }
        }
        for(int i = 0; i < fft->getBinSize(); i++) {
            audioBins[i] /= maxValue;
        }
        
        soundMutex.lock();
        middleBins = audioBins;
        soundMutex.unlock();
    }
    
private:
    FFT() {
        cout<<"FFT Singleton instanciated"<<endl;
    }
};

#endif

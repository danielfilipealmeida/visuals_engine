//
//  FFT.hpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 13/03/2025.
//

#ifndef __fft__
#define __fft__

#include "ofxFft.h"
#include <format>

/**
 !
 Class wrapper for ofxFft using a Singleton pattern
 */
class FFT {
    ofxFft* fft;
    int bufferSize;
    
    ofMutex soundMutex;
    
    std::deque<float> energyHistory;
    const int historySize = 50;
    
    //! @var hanningWindow
    //! @abstract a vector storing the shape of a computed Hanning window. This needs to be calculated before being used and recalculated if the size is changed.
    std::vector<float> hanningWindow;
    
public:
    //! @var sensitivity
    //! @abstract the
    float sensitivity = 2.5f;
    
    //! @var beatDetectionBin
    //! @abstract the bin where the Hanning window is centered
    int beatDetectionBin = 5;
    
    //! @var windowSize
    //! @abstract the dimention of the hanning filter window
    int windowSize = 7;
    
    //! @var totalBeatCount
    //! @abstract the total ammount of beats detected since the instatiation of the object
    unsigned long int totalBeatCount = 0;
    
    //! @var minBeatEnergy
    //! @abstract the minimum energy needed for the beat detection algorithm to be executed
    float minBeatEnergy = 0.00005;

    //! @var offBeatFactor
    //! @abstract factor applied to the beat threshold in order to allow for the current beat detected to stop. smalller the value, the nearest to silence
    float offBeatFactor = 0.10;
    
    //! @var maximumEnergyMeasured
    //! @abstract stores the maximum energy already felt by the beat detector
    float maximumEnergyMeasured;

    
    //! @var beatOn
    //! @abstract mark when a beat is happening
    float beatOn;
    
    vector<float> audioBins;
    
    FFT(const FFT&) = delete;
    FFT& operator=(const FFT&) = delete;
    
    
    /// Returns the instance of the FFT singleton. Creates it if needed
    static FFT& getInstance() {
        static FFT instance;
        return instance;
    }
    
    
    /// Basic setup to the FFT
    /// - Parameter bufferSize: the size of buffers
    void setup(int bufferSize) {
        this->bufferSize = bufferSize;
        
        fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_HAMMING);
        audioBins.resize(fft->getBinSize());
        
        hanningWindow = FFT::buildHanningWindow(windowSize);
        energyHistory.resize(historySize);
        
        beatOn = false;
        maximumEnergyMeasured = 0;
    }
    
    /// Receives the Audio Buffer, calculates the FFT, Filters, around a bin, calculates the energy and triggers a beat if it is detected
    /// - Parameter signal: a vector containing the audio signal.
    void setSignal(vector<float> signal) {
        fft->setSignal(signal);
        
        
        //float maxValue = 0;
        float* curFft = fft->getAmplitude();
        memcpy(&audioBins[0], curFft, sizeof(float) * fft->getBinSize());
        
        float currentEnergy = FFT::calculateEnergyWithHanningWindow(audioBins, beatDetectionBin, hanningWindow);
        energyHistory.push_back(currentEnergy);
        if (energyHistory.size() > historySize) energyHistory.pop_front();
        if (currentEnergy > maximumEnergyMeasured) {
            maximumEnergyMeasured = currentEnergy;
        }
        
        // check if it is a beat
        // todo: using pubsub warn subscribers of beat
        float average = std::accumulate(energyHistory.begin(), energyHistory.end(), 0.0f) / energyHistory.size();
        
        // checks it a beat that was previously detected has stopped.
        if (beatOn) {
            // check if the energy is still above the threshold
            if (currentEnergy > average * sensitivity * offBeatFactor) {
                return;
            }
            
            // the energy as fallon below the threshold. we can considere it has finished
            beatOn = false;
        }

        // only continues detecting the beat if the energy us bigger or equal to than the threshold
        if (currentEnergy < minBeatEnergy) {
            return;
        }

        
        // Check if a beat has been detected
        if (currentEnergy > (average * sensitivity)) {
            beatOn = true;
            
            totalBeatCount++;
            // warn all subscribers
            cout << "beat: " << totalBeatCount << ", " << currentEnergy << " / " << maximumEnergyMeasured << endl;
            
            //cout << std::format("Beat: {}, {} / {}", totalBeatCount, currentEnergy, maximumEnergyMeasured);
        }
        
    }
    
    
    /// Static function that builds a vector with the shape of an hanning window with the desired window size
    /// - Parameter windowSize: the number of bins occupied by the window
    static std::vector<float> buildHanningWindow(int _windowSize) {
        std::vector<float> window(_windowSize);
        
        for(int n = 0; n < _windowSize; ++n) {
            window[n] = 0.5 * (1.0f - cosf((2.0f * M_PI * n) / (_windowSize -1 )));
        }
        
        return window;
    }
    
    /// Applies the Hanning window to the data and calculates the energy of the filtered signal. the original data isn't changed
    /// - Parameters:
    ///   - in: the FFT bins
    ///   - centerBin: the bin where the window is centered at
    ///   - hanningWindow: the vector containing the pre calculated shape of the hanning window
    static float calculateEnergyWithHanningWindow(
                                                  std::vector<float> in,
                                                  int centerBin,
                                                  std::vector<float> _hanningWindow
                                                  ) {
        float energy = 0.0f;
        int halfWindow = _hanningWindow.size() / 2;
        for (int n = 0; n < _hanningWindow.size(); ++n) {
            int bin = centerBin - halfWindow + n;
            if (bin >= 0 && bin < in.size()) {
                energy += in[bin] * in[bin] * _hanningWindow[n];
            }
        }
        
        return energy;
    }
    
    
private:
    FFT() {
        cout<<"FFT Singleton instanciated"<<endl;
    }
};

#endif

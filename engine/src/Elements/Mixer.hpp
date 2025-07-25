//
//  Mixer.hpp
//  emptyExample
//
//  Created by Daniel Almeida on 27/12/2024.
//

#ifndef __Mixer_hpp__
#define __Mixer_hpp__

#include "Layer.hpp"
#include "Observer.hpp"

//! @brief an enum defining all parameters of the Mixer that can be observed
enum class MixerObservableParameters {
    MIX
};

//! @class Mixer
//! @abstract Implements a simple two channel mixer.
//! @discussion This mixer mixes two VisualInterfaces (channel A and B).
class Mixer: public Drawable, public Observer<float>, public Encodable {
public:
    
    //! @var mix
    //! @abstract a float value from 0.0 to 1.0, representing the percentage of the mix of channel B, over channel A.
    //! @discussion 0.0 is just channel A, 0.5 is channel A with 0.5 channel B and 1.0 is just channel B
    float mix;
    
    
    ofFbo *buffer;
    
    //! @var a
    //! @abstract the A channel as VisualInterface
    VisualsInterface *a;
    
    //! @var b
    //! @abstract the B channel as VisualInterface
    VisualsInterface *b;
    
    //! @var parameters the parameters of this Drawable that can be observed
    std::map<MixerObservableParameters, std::string> parameters = {
        {MixerObservableParameters::MIX, "mix"}
    };
    
    /// \brief The constructor of the mixer--.
    ///
    /// \param _A - ihe chanel A visual interface
    /// \param _B _the channel B visual interface
    /// \param _bufferWidth - the width dimention of the fbo that will store the mix
    /// \param _bufferHeight - the height dimention of the fbo that will store the mix
    Mixer(VisualsInterface* _A, VisualsInterface* _B, float _bufferWidth, float _bufferHeight);
    
    /// \brief The destructor of the Mixer
    ~Mixer();
    
    //! @brief update the layer stack by rendering to the FBO
    void update() override;
    
    //! @brief update the layer stack by rendering to the FBO
    void draw() override;
    
    //! @brief draw the FBO in the specified rect
    //!
    //! @param rect
    void draw(ofRectangle rect)  override;
    
    //! @brief sets the value of the mix of the mixer
    //!
    //! @param _mix the value from 0.0 to 1.0 (channel A <-> channel B)
    void setMix(float _mix);
    
    //! @brief updates a value
    //!
    //! @param val the value to update
    //! @param key the key of the value to update
    void update(float val, std::string key) override;
    
    /// \brief get a JSON representation of the mixer
    ///
    /// \returns a ofJson object
    ofJson encode();
    
    /// @brief Sets the set data from the json
    ///
    /// @param data json data
    void decode(ofJson data);
};

#endif

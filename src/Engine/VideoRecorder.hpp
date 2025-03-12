//
//  VideoRecorder.hpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 10/03/2025.
//

#ifndef __video_recorder_hpp__
#define __video_recorder_hpp__

#include "ofxVideoRecorder.h"

class VideoRecorder {
    ofxVideoRecorder recorder;
    std::string fileName;
    std::string fileExt;
    unsigned int sampleRate;
    unsigned short channels;
public:
    
    VideoRecorder();
    ~VideoRecorder();
    
    void update(ofPixels pixels);
    void recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args);
    
};

#endif

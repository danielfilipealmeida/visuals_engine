//
//  VideoRecorder.cpp
//  VisualsEngine
//
//  Created by Daniel Almeida on 10/03/2025.
//

#include "VideoRecorder.hpp"


VideoRecorder::VideoRecorder()
{
    fileName = "testMovie";
    fileExt = ".mov"; 
    recorder.setVideoCodec("mpeg4");
    recorder.setVideoBitrate("800k");
    recorder.setAudioCodec("mp3");
    recorder.setAudioBitrate("192k");
    
    ofAddListener(recorder.outputFileCompleteEvent, this, &VideoRecorder::recordingComplete);
    
    sampleRate = 44100;
    channels = 2;
    
    recorder.setup(fileName+ofGetTimestampString()+fileExt, 640,480, 30, sampleRate, channels);
    recorder.start();
}

void VideoRecorder::recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args)
{
    cout << "The recoded video file is now complete." << endl;
}

VideoRecorder::~VideoRecorder() {
    recorder.close();
}

void VideoRecorder::update(ofPixels pixels) {
    bool success = recorder.addFrame(pixels);
    if (!success) {
        ofLogWarning("This frame was not added!");
    }
    if (recorder.hasVideoError()) {
        ofLogWarning("The video recorder failed to write some frames!");
    }
    
    if (recorder.hasAudioError()) {
        ofLogWarning("The video recorder failed to write some audio samples!");
    }
}

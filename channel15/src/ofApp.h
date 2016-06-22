#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxFFTLive.h"
#include "ofxSyphon.h"
#include "v01.h"
#include "v02.h"
#include "v03.h"
#include "v04.h"
#include "v05.h"
#include "v06.h"
#include "v07.h"
#include "v08.h"

class v01;
class v02;
class v03;
class v04;
class v05;
class v06;
class v07;
class v08;

#define PORT 8888

//parameters
extern float    a01, a02, a03, a04, a05, a06, a07, a08, a09, a10,
b01, b02, b03, b04, b05, b06, b07, b08, b09, b10,
c01, c02, c03, c04, c05, c06, c07, c08, c09, c10;
extern float    audioLevel01,
audioLevel02;

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void drawTargetFreq(string targetName, int freq, ofColor &rgb); 
    
    //OSC
    ofxOscReceiver receiver;
    float value;
    vector <string> items;
    char address;
    int visual = 1;
    
    //fft
    ofxFFTLive fft;
    float   audioThreshold,
    audioPeakDecay,
    audioMaxDecay,
    dbMin, kbbMin,
    dbMax, kbbMax;
    int     targetFreq01, targetFreq02,
    guiWidth = 150;
    const int fftW = OFX_FFT_WIDTH,
    fftH = OFX_FFT_HEIGHT,
    fftX = (ofGetWidth() - fftW) / 2,
    fftY = ofGetHeight() - fftH - 10,
    guiW = 174,
    guiH = 150;
    ofColor col01, col02;
    
    //visuals
    v01* v01_;
    v02* v02_;
    v03* v03_;
    v04* v04_;
    v05* v05_;
    v06* v06_;
    v07* v07_;
    v08* v08_;
    
    string title;
    
    //Syphon
    ofxSyphonServer mainOutputSyphonServer;
};

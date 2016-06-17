#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxFFTLive.h"
#include "v01.h"
#include "v02.h"
#include "v03.h"
#include "v04.h"
#include "v05.h"
#include "v06.h"
#include "v07.h"
#include "v08.h"

#define PORT 12345

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
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
    bool    audioReactiveDB, audioReactiveKBB;
    int     dbTargetFreq, kbbTargetFreq,
    guiWidth = 150;
    const int fftW = OFX_FFT_WIDTH,
    fftH = OFX_FFT_HEIGHT,
    fftX = (ofGetWidth() - fftW) / 2,
    fftY = ofGetHeight() - fftH - 10,
    guiW = 174,
    guiH = 150;
    
    //visuals
    v01* v01_;
    v02* v02_;
    v03* v03_;
    v04* v04_;
    v05* v05_;
    v06* v06_;
    v07* v07_;
    v08* v08_;
    //parameters
    float   a01, a02, a03, a04, a05, a06, a07, a08, a09, a10,
            b01, b02, b03, b04, b05, b06, b07, b08, b09, b10,
            c01, c02, c03, c04, c05, c06, c07, c08, c09, c10;
};

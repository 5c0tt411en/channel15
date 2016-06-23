//
//  v03.h
//  channel15
//
//  Created by scott on 6/15/16.
//
//

#ifndef __channel15__v03__
#define __channel15__v03__

#define WIDTH 20
#define HEIGHT 20
#define PARS 4
#define NUM_MIST WIDTH * HEIGHT

#include <stdio.h>
#include "ofMain.h"
#include "ofApp.h"

class v03 {
public:
    v03();
    void setup();
    void update();
    void draw();
    void rateDetermination();
    void modeTF(int modeSelect);
    
    ofVbo Vbo;
    ofVec3f Verts[NUM_MIST];
    ofFloatColor Color[NUM_MIST];
    
    float xNoise, yNoise, zNoise;
    float pixDisX, pixDisY;
    
    vector<ofVec3f> points;
    ofVec3f rbPt;
    int     r             = 300,
    lineWidth     = 100;
    float speed       = 50,
    rotateRate  = 1,
    noiseRateX  = 1,
    noiseRateY  = 1.2,
    noiseSpeedX = 0.6,
    noiseSpeedY = 0.75;
    float transZ;
    
    ofCamera cam;
    ofVec3f pointToView;
    ofNode node;
    
    bool b[20], bVolume = false, cVolume = false;
    int modeSelect, drawMode;
    float rate[20];
    float x[20], y[20], z[20];
    ofVec3f pt, ptAll;
    float pmRate = 0.4;
    float pitch, volume, val, val1;
};
#endif /* defined(__channel15__v03__) */

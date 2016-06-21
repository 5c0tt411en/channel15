//
//  v01.h
//  channel15
//
//  Created by scott on 6/15/16.
//
//

#ifndef __channel15__v01__
#define __channel15__v01__

#include <stdio.h>
#include "ofMain.h"
#include "ofApp.h"


class v01 {
public:
    v01();
    void setup();
    void update();
    void draw();
    void reset();
    
    ofShader shader;
    bool doShader;
    vector<ofVec3f> points;
    ofVec3f rbPt;
    int pointSize     = 500,
        r             = 300,
        lineWidth     = 100;
    float speed       = 50,
          rotateRate  = 1,
          noiseRateX  = 1,
          noiseRateY  = 1.2,
          noiseSpeedX = 0.6,
          noiseSpeedY = 0.75;
    
    ofCamera cam;
    ofVec3f pointToView;
    ofNode node;
};

#endif /* defined(__channel15__v01__) */

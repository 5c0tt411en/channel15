//
//  v05.h
//  channel15
//
//  Created by scott on 6/15/16.
//
//

#ifndef __channel15__v05__
#define __channel15__v05__

#include <stdio.h>
#include "ofMain.h"
#include "ofApp.h"

#define POINT_SIZE 100

class v05 {
public:
    v05();
    void setup();
    void update();
    void draw();
    
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
    
    ofImage sparkImg;
    int     width, height;
    int     imgWidth, imgHeight;
    int     numParticles;
    int     textureRes;
    
    ofVbo vbo;
    ofVec3f verts[POINT_SIZE];
    ofFloatColor color[POINT_SIZE];
};
#endif /* defined(__channel15__v05__) */

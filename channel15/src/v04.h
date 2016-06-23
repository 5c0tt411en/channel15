//
//  v04.h
//  channel15
//
//  Created by scott on 6/15/16.
//
//

#ifndef __channel15__v04__
#define __channel15__v04__

#include <stdio.h>
#include "ofMain.h"
#include "ofApp.h"

#define POINT_SIZE 500

class v04 {
public:
    v04();
    void setup();
    void update();
    void draw();
    
    ofShader shader;
    bool doShader;
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
#endif /* defined(__channel15__v04__) */

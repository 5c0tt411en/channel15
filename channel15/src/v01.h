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
class ofApp;
class v01 {
public:
    v01();
    void setup();
    void update();
    void draw();
    
    ofShader shader;
    bool doShader;
    vector<ofVec3f> points;
    ofVec3f rbPt;
    int pointSize = 500,
        r         = 300;
    ofApp* ofapp_;
};

#endif /* defined(__channel15__v01__) */

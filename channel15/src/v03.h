//
//  v03.h
//  channel15
//
//  Created by scott on 6/15/16.
//
//

#ifndef __channel15__v03__
#define __channel15__v03__

#define WIDTH 70
#define HEIGHT 70
#define PARS 8
#define NUM_MIST WIDTH * HEIGHT

#include <stdio.h>
#include "ofMain.h"
class v03 {
public:
    v03();
    void setup();
    void update();
    void draw();
    
    ofVbo Vbo;
    ofVec3f Verts[NUM_MIST];
    ofFloatColor Color[NUM_MIST];
    float x_01, y_01, z_01;
    
    float xNoise, yNoise, zNoise;
    float pixDisX, pixDisY;
};
#endif /* defined(__channel15__v03__) */

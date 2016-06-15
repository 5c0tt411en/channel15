//
//  v02.h
//  channel15
//
//  Created by scott on 6/15/16.
//
//

#ifndef __channel15__v02__
#define __channel15__v02__

#include <stdio.h>
#include "ofMain.h"
class v02 {
public:
    v02();
    void setup();
    void update();
    void draw();
    void rotateToNormal(ofVec3f normal);
    
    ofVec3f previous, current;
    ofCamera cam;
    
    deque<ofVec3f> pathVertices;
    ofMesh pathLines;
};
#endif /* defined(__channel15__v02__) */

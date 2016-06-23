//
//  v06.h
//  channel15
//
//  Created by scott on 6/15/16.
//
//

#ifndef __channel15__v06__
#define __channel15__v06__

#include <stdio.h>
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
class v06 {
public:
    v06();
    void setup();
    void update();
    void draw();
    
    ofxAssimpModelLoader model;
    ofLight light;
};
#endif /* defined(__channel15__v06__) */

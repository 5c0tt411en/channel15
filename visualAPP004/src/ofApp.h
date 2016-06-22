#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"
#include "ofxPostProcessing.h"

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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    //__________Syphon__________//
    ofxSyphonClient client;
    
    //__________Post Processing__________//
    // scene stuff
    ofxPostProcessing post;
    //    ofEasyCam cam;
    //    ofLight light;
};

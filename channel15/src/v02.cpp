//
//  v02.cpp
//  channel15
//
//  Created by scott on 6/15/16.
//
//

#include "v02.h"

v02::v02(){
    
}

void v02::rotateToNormal(ofVec3f normal){
    normal.normalize();
    
    float rotationAmount;
    ofVec3f rotationAngle;
    ofQuaternion rotation;
    
    ofVec3f axis(0, 0, 1);
    rotation.makeRotate(axis, normal);
    rotation.getRotate(rotationAmount, rotationAngle);
    ofRotate(rotationAmount, rotationAngle.x, rotationAngle.y, rotationAngle.z);
}

void v02::setup(){
    pathLines.setMode(OF_PRIMITIVE_LINE_STRIP);
}

void v02::update(){
    previous = current;
    
    // generate a noisy 3d position over time
    float t = (2 + ofGetElapsedTimef()) * .3;
    current.x = ofSignedNoise(t, 0, 0);
    current.y = ofSignedNoise(0, t, 0);
    current.z = ofSignedNoise(0, 0, t);
    current *= 400; // scale from -1,+1 range to -400,+400
    
    // add the current position to the pathVertices deque
    pathVertices.push_back(current);
    // if we have too many vertices in the deque, get rid of the oldest ones
    while(pathVertices.size() > 3000) {
        pathVertices.pop_front();
    }
    
    // clear the pathLines ofMesh from any old vertices
    pathLines.clear();
    // add all the vertices from pathVertices
    for(unsigned int i = 0; i < pathVertices.size(); i++) {
        pathLines.addVertex(pathVertices[i]);
    }
}

void v02::draw(){
    ofColor cyan = ofColor::fromHex(0x00abec);
    ofColor magenta = ofColor::fromHex(0xec008c);
    ofColor yellow = ofColor::fromHex(0xffee00);
    
    ofNoFill();
    
    cam.begin();
    ofRotateX(15);
    
    ofSetColor(0);
    ofDrawGrid(500, 10, false, false, true, false);
    
    // draw the path of the box
    ofSetLineWidth(1);
    ofSetColor(cyan);
    pathLines.draw();
    
    // draw a line connecting the box to the grid
    ofSetColor(yellow);
    ofDrawLine(current.x, current.y, current.z, current.x, 0, current.z);
    
    // translate and rotate to the current position and orientation
    ofTranslate(current.x, current.y, current.z);
    if( (current - previous ).length() > 0.0 ){
        rotateToNormal(current - previous);
    }
    ofSetColor(255);
    ofDrawBox(32);
    ofDrawAxis(32);
    
    cam.end();
}
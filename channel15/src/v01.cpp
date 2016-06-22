//
//  v01.cpp
//  channel15
//
//  Created by scott on 6/15/16.
//
//

#include "v01.h"

v01::v01(){
    
}

void v01::setup(){
    ofSetSmoothLighting(true);
    cam.setPosition(ofGetWidth() / 2, ofGetHeight() / 2, 100);
    pointToView = ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2, 0);
    ofSetLogLevel(OF_LOG_VERBOSE);
    shader.setGeometryInputType(GL_LINES);
    shader.setGeometryOutputType(GL_POLYGON);
    shader.setGeometryOutputCount(4);
    shader.load("shaders/vert.glsl", "shaders/frag.glsl", "shaders/geom.glsl");

    for(int i = 0; i < pointSize; i++) {
        rbPt.x = ofNoise(i * noiseSpeedX) * noiseRateX;
        rbPt.y = ofNoise(i * noiseSpeedY) * noiseRateY;
        rbPt.z = -i * speed * (0.1 + (a04 + c04 * audioLevel01)) + pointSize / 20;
        rbPt.x = ofMap(rbPt.x, 0, 1, ofGetWidth() / 2 + r * 0.1 * sin(i * rotateRate), ofGetWidth() / 2 + r * sin(i * rotateRate));
        rbPt.y = ofMap(rbPt.y, 0, 1, ofGetHeight() / 2 + r * 0.1 * cos(i * rotateRate), ofGetHeight() / 2 + r * cos(i * rotateRate));
        points.push_back(rbPt);
    }
    
    doShader = true;
    ofEnableDepthTest();
}

void v01::update(){
//    light.lookAt(ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2, 0));
//    light.setPosition(ofVec3f(ofGetWidth() / 2 -100, ofGetHeight() / 2 - 100, 0));
    
    pointToView.x = ofGetWidth() / 2 + 100 * sin(ofGetElapsedTimef() * 0.5);
    pointToView.y = ofGetHeight() / 2 + 100 * sin(ofGetElapsedTimef() * 0.35);
    pointToView.z = 100 * sin(ofGetElapsedTimef() * 0.4);
    
    node.setPosition(pointToView);
    node.setOrientation(ofVec3f(ofGetWidth() / 2 + 100, ofGetHeight() / 2, -100));
    
    points.erase(points.begin());
    for(int i = pointSize - 1; i < pointSize; i++) {
        rbPt.x = ofNoise(noiseSpeedX * (i + ofGetFrameNum())) * noiseRateX;
        rbPt.y = ofNoise(noiseSpeedY * (i + ofGetFrameNum())) * noiseRateY;
        rbPt.z = -speed * (0.1 + (a04 + c04 * audioLevel01)) * (i + ofGetFrameNum());
        rbPt.x = ofMap(rbPt.x, 0, 1, ofGetWidth() / 2 + r * 0.1 * sin(rotateRate * (i + ofGetFrameNum())), ofGetWidth() / 2 + r * sin(rotateRate * (i + ofGetFrameNum())) * (1 + (a01 + c01 * audioLevel01)));
        rbPt.y = ofMap(rbPt.y, 0, 1, ofGetHeight() / 2 + r * 0.1 * cos(rotateRate * (i + ofGetFrameNum())), ofGetHeight() / 2 + r * cos(rotateRate * (i + ofGetFrameNum())) * (1 + (a02 + c02 * audioLevel01)));
        points.push_back(rbPt);
    }
}

void v01::draw(){
    cam.lookAt(node.getPosition());
    cam.begin();
    ofDrawAxis(100);
    ofSetColor(0, 255, 0);
    node.draw();
    ofSetColor(0, 255, 255);
    ofDrawLine(cam.getPosition(),node.getPosition());
    
//    ofNoFill();
    ofSetColor(100, 160, 120);
    ofPushMatrix();
    if(doShader) {
        shader.begin();
        // set thickness of ribbons
        shader.setUniform1f("thickness", 1 + lineWidth * (a03 + c03 * audioLevel01));
        
        // make light direction slowly rotate
        shader.setUniform3f("lightDir", sin(ofGetElapsedTimef()/10), cos(ofGetElapsedTimef()/10), 0.5 * cos(ofGetElapsedTimef()/10)/*ofGetWidth() / 2, ofGetHeight() / 2, -1000*/);
    }
    ofTranslate(0, 0, ofGetFrameNum() * speed * (0.1 + (a04 + c04 * audioLevel01)) + pointSize);
    for(unsigned int i=1; i<points.size(); i++) {
        ofDrawLine(points[i-1], points[i]);
        if (i > 5) ofDrawLine(points[i-5], points[i]);
        if (i > 7) ofDrawLine(points[i-7], points[i]);
    }
    if(doShader) shader.end();
    ofPopMatrix();
    
    // restore view to previous state (default openFrameworks view)
    cam.end();
}
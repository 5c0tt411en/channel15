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
    ofapp_ = new ofApp();
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    shader.setGeometryInputType(GL_LINES);
    shader.setGeometryOutputType(GL_QUAD_STRIP);
    shader.setGeometryOutputCount(4);
    shader.load("shaders/vert.glsl", "shaders/frag.glsl", "shaders/geom.glsl");

    for(int i = 0; i < pointSize; i++) {
        rbPt.x = ofNoise(i*0.6);
        rbPt.y = ofNoise(i*0.75);
        rbPt.z = -i*0.1 + pointSize / 20;
        rbPt.x = ofMap(rbPt.x, 0, 1, ofGetWidth() / 2 + r * 0.8 * sin(i * 0.1), ofGetWidth() / 2 + r * sin(i * 0.1));
        rbPt.y = ofMap(rbPt.y, 0, 1, ofGetHeight() / 2 + r * 0.8 * cos(i * 0.1), ofGetHeight() / 2 + r * cos(i * 0.1));
        points.push_back(rbPt);
    }
    
    doShader = true;
    ofEnableDepthTest();
}

void v01::update(){
    points.erase(points.begin());
    for(int i = pointSize - 1; i < pointSize; i++) {
        rbPt.x = ofNoise(0.6 * (i + ofGetFrameNum()));
        rbPt.y = ofNoise(0.75 * (i + ofGetFrameNum()));
        rbPt.z = -0.1 * (i + ofGetFrameNum()) + pointSize / 20;
        rbPt.x = ofMap(rbPt.x, 0, 1, ofGetWidth() / 2 + r * 0.8 * sin(0.1 * (i + ofGetFrameNum())), ofGetWidth() / 2 + r * sin(0.1 * (i + ofGetFrameNum())) * (1 + ofapp_->audioLevel01));
        rbPt.y = ofMap(rbPt.y, 0, 1, ofGetHeight() / 2 + r * 0.8 * cos(0.1 * (i + ofGetFrameNum())), ofGetHeight() / 2 + r * cos(0.1 * (i + ofGetFrameNum())) * (1 + ofapp_->audioLevel01));
        points.push_back(rbPt);
    }
//    cout << ofapp_->audioLevel01 << '\n';
}

void v01::draw(){
    ofSetColor(100, 160, 120);
    ofPushMatrix();
    if(doShader) {
        shader.begin();
        
        // set thickness of ribbons
        shader.setUniform1f("thickness", 1);
        
        // make light direction slowly rotate
        shader.setUniform3f("lightDir", sin(ofGetElapsedTimef()/10), cos(ofGetElapsedTimef()/10), 0);
    }

//    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, 0);
    ofRotateX(ofGetMouseX());
    ofRotateY(ofGetMouseY());
    for(unsigned int i=1; i<points.size(); i++) {
        ofDrawLine(points[i-1], points[i]);
    }
    if(doShader) shader.end();
    ofPopMatrix();
}

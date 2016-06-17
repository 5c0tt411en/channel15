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
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    shader.setGeometryInputType(GL_LINES);
    shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
    shader.setGeometryOutputCount(4);
    shader.load("shaders/vert.glsl", "shaders/frag.glsl", "shaders/geom.glsl");
        // create a bunch of random points
    float r = ofGetHeight()/2;
    for(int i=0; i<5000; i++) {
        points.push_back(ofPoint(ofRandomf() * r, ofRandomf() * r, ofRandomf() * r));
    }
    
    doShader = true;
    ofEnableDepthTest();
}

void v01::update(){
    
}

void v01::draw(){
    ofSetColor(100, 160, 120);
    ofPushMatrix();
    if(doShader) {
        shader.begin();
        
        // set thickness of ribbons
        shader.setUniform1f("thickness", 20);
        
        // make light direction slowly rotate
        shader.setUniform3f("lightDir", sin(ofGetElapsedTimef()/10), cos(ofGetElapsedTimef()/10), 0);
    }

    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, 0);
    ofRotateX(ofGetMouseX());
    ofRotateY(ofGetMouseY());
    for(unsigned int i=1; i<points.size(); i++) {
        ofDrawLine(points[i-1], points[i]);
    }
    if(doShader) shader.end();
    ofPopMatrix();
}

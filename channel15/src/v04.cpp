//
//  v04.cpp
//  channel15
//
//  Created by scott on 6/15/16.
//
//

#include "v04.h"

v04::v04(){
    
}

void v04::setup(){
    ofSetSmoothLighting(true);
    cam.setPosition(ofGetWidth() / 2, ofGetHeight() / 2, 100);
    pointToView = ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2, 0);
//    ofSetLogLevel(OF_LOG_VERBOSE);
//    shader.setGeometryInputType(GL_LINES);
//    shader.setGeometryOutputType(GL_POINTS);
//    shader.setGeometryOutputCount(4);
//    shader.load("shaders/vert.glsl", "shaders/frag.glsl", "shaders/geom.glsl");
    
    for(int i = 0; i < POINT_SIZE; i++) {
//        rbPt.x = ofNoise(i * noiseSpeedX) * noiseRateX;
//        rbPt.y = ofNoise(i * noiseSpeedY) * noiseRateY;
        rbPt.x = ofRandom(-r, r) + ofGetWidth() / 2;
        rbPt.y = ofRandom(-r, r) + ofGetHeight() / 2;
        rbPt.z = -i * speed * (0.1 + (a04 + c04 * audioLevel01)) + POINT_SIZE / 20;
//        rbPt.x = ofMap(rbPt.x, 0, 1, ofGetWidth() / 2 + r * 0.1 * sin(i * rotateRate), ofGetWidth() / 2 + r * sin(i * rotateRate));
//        rbPt.y = ofMap(rbPt.y, 0, 1, ofGetHeight() / 2 + r * 0.1 * cos(i * rotateRate), ofGetHeight() / 2 + r * cos(i * rotateRate));
//        rbPt.z = ofMap(rbPt.z, -1500, 1500, -120, 120);
        points.push_back(rbPt);
        verts[i].set(rbPt);
        color[i].set(1.0, 1.0, 1.0, 1.0);
    }
    vbo.setVertexData(verts, POINT_SIZE, GL_DYNAMIC_DRAW);
    vbo.setColorData(color, POINT_SIZE, GL_DYNAMIC_DRAW);
    
//    doShader = true;
    ofEnableDepthTest();
    
    ofDisableArbTex();
    sparkImg.load("spark.png");
}

void v04::update(){
    pointToView.x = ofGetWidth() / 2 + 100 * sin(ofGetElapsedTimef() * 0.5);
    pointToView.y = ofGetHeight() / 2 + 100 * sin(ofGetElapsedTimef() * 0.35);
    pointToView.z = 100 * sin(ofGetElapsedTimef() * 0.4);
    
    node.setPosition(pointToView);
    node.setOrientation(ofVec3f(ofGetWidth() / 2 + 100, ofGetHeight() / 2, -100));
    
    points.erase(points.begin());
    for(int i = POINT_SIZE - 1; i < POINT_SIZE; i++) {
//        rbPt.x = ofNoise(noiseSpeedX * (i + ofGetFrameNum())) * noiseRateX;
//        rbPt.y = ofNoise(noiseSpeedY * (i + ofGetFrameNum())) * noiseRateY;
        rbPt.x = ofRandom(-r, r) + ofGetWidth() / 2;
        rbPt.y = ofRandom(-r, r) + ofGetHeight() / 2;
        rbPt.z = -speed * (0.1 + (a04 + c04 * audioLevel01)) * (i + ofGetFrameNum());
//        rbPt.x = ofMap(rbPt.x, 0, 1, ofGetWidth() / 2 + r * 0.1 * sin(rotateRate * (i + ofGetFrameNum())), ofGetWidth() / 2 + r * sin(rotateRate * (i + ofGetFrameNum())) * (1 + (a01 + c01 * audioLevel01)));
//        rbPt.y = ofMap(rbPt.y, 0, 1, ofGetHeight() / 2 + r * 0.1 * cos(rotateRate * (i + ofGetFrameNum())), ofGetHeight() / 2 + r * cos(rotateRate * (i + ofGetFrameNum())) * (1 + (a02 + c02 * audioLevel01)));
//        rbPt.z = ofMap(rbPt.z, -1500, 1500, -120, 120);
        points.push_back(rbPt);
    }
    for (int i = 0; i < POINT_SIZE; i++) {
        verts[i].set(points[i]);
        color[i].set(1.0, 1.0, 1.0, 1.0);
    }
    vbo.updateVertexData(verts, POINT_SIZE);
    vbo.updateColorData(color, POINT_SIZE);
}

void v04::draw(){
    cam.lookAt(node.getPosition());
    cam.begin();
    
    glDepthMask(GL_FALSE);
    ofEnablePointSprites();
    sparkImg.getTextureReference().bind();
    static GLfloat distance[] = { 0.0, 0.0, 1.0 };
    glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, distance);
    ofPushMatrix();
    transZ = ofGetFrameNum() * speed * (0.1 + (a04 + c04 * audioLevel01)) + POINT_SIZE;
//    transZ = ofMap(rbPt.z, -1500, 1500, -120, 120);
    ofTranslate(0, 0, transZ);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    glPointSize(100000);
    vbo.draw(GL_POINTS, 0, POINT_SIZE);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    sparkImg.getTextureReference().unbind();
    ofDisablePointSprites();
    glDepthMask(GL_TRUE);
    ofPopMatrix();
    //    ofSetColor(0, 255, 0);
    //    node.draw();
    
    //    ofNoFill();
//    ofPushMatrix();
//    if(doShader) {
//        shader.begin();
//        // set thickness of ribbons
//        shader.setUniform1f("thickness", 1 + lineWidth * (a03 + c03 * audioLevel01));
//        
//        // make light direction slowly rotate
//        shader.setUniform3f("lightDir", sin(ofGetElapsedTimef()/10), cos(ofGetElapsedTimef()/10), 0.5 * cos(ofGetElapsedTimef()/10)/*ofGetWidth() / 2, ofGetHeight() / 2, -1000*/);
//    }
//    ofTranslate(0, 0, ofGetFrameNum() * speed * (0.1 + (a04 + c04 * audioLevel01)) + POINT_SIZE);
//    ofEnableBlendMode(OF_BLENDMODE_ADD);
//    for(unsigned int i=1; i<points.size(); i++) {
//            ofSetColor(255, 255, 255/*, 255 * (i)*/);
//        glPointSize(5);
//        ofDrawLine(points[i-1], points[i]);
        
//    }
//    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//    if(doShader) shader.end();
//    ofPopMatrix();
    
    // restore view to previous state (default openFrameworks view)
    cam.end();
}
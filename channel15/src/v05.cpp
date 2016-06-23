//
//  v05.cpp
//  channel15
//
//  Created by scott on 6/15/16.
//
//

#include "v05.h"

v05::v05(){
    
}

void v05::setup(){
    ofSetSmoothLighting(true);
    cam.setPosition(ofGetWidth() / 2, ofGetHeight() / 2, 100);
    pointToView = ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2, 0);
    
    for(int i = 0; i < POINT_SIZE; i++) {
        rbPt.x = ofRandom(-r, r) + ofGetWidth() / 2;
        rbPt.y = ofRandom(-r, r) + ofGetHeight() / 2;
        rbPt.z = -i * speed * (0.1 + (a04 + c04 * audioLevel01)) + POINT_SIZE / 20;
        points.push_back(rbPt);
        verts[i].set(rbPt);
        color[i].set(1.0, 0.0, 1.0, 1.0 * b07);
    }
    vbo.setVertexData(verts, POINT_SIZE, GL_DYNAMIC_DRAW);
    vbo.setColorData(color, POINT_SIZE, GL_DYNAMIC_DRAW);
    
    //    doShader = true;
    ofEnableDepthTest();
    
    ofDisableArbTex();
    sparkImg.load("spark.png");
}

void v05::update(){
    pointToView.x = ofGetWidth() / 2 + 100 * sin(ofGetElapsedTimef() * 0.5);
    pointToView.y = ofGetHeight() / 2 + 100 * sin(ofGetElapsedTimef() * 0.35);
    pointToView.z = 100 * sin(ofGetElapsedTimef() * 0.4);
    
    node.setPosition(pointToView);
    node.setOrientation(ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2, -100));
    
    points.erase(points.begin());
    for(int i = POINT_SIZE - 1; i < POINT_SIZE; i++) {
        rbPt.x = ofRandom(-50, 50) + pointToView.x;
        rbPt.y = ofRandom(-50, 50) + pointToView.y;
        rbPt.z = -speed * (0.1 + (a04 + c04 * audioLevel01)) * (i + ofGetFrameNum());
        points.push_back(rbPt);
    }
    for (int i = 0; i < POINT_SIZE; i++) {
        verts[i].set(points[i]);
        color[i].set(1.0, 0.0, 1.0, 1.0 * b07);
    }
    vbo.updateVertexData(verts, POINT_SIZE);
    vbo.updateColorData(color, POINT_SIZE);
}

void v05::draw(){
    cam.lookAt(node.getPosition());
    cam.begin();
    glDepthMask(GL_FALSE);
    ofEnablePointSprites();
    sparkImg.getTextureReference().bind();
    static GLfloat distance[] = { 0.0, 0.0, 1.0 };
    glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, distance);
    ofPushMatrix();
    transZ = ofGetFrameNum() * speed * (0.1 + (a04 + c04 * audioLevel01)) + abs(points[POINT_SIZE - 1].z - points[0].z) + pointToView.z;
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
    cam.end();
}
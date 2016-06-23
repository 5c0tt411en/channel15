//
//  v03.cpp
//  channel15
//
//  Created by scott on 6/15/16.
//
//

#include "v03.h"

v03::v03(){

}

void v03::setup(){
    for (int i = 0; i < sizeof(b) / sizeof(b[0]); i++) {
        rate[i] = 0;
        b[i] = 0;
        x[i] = 0;
        y[i] = 0;
        z[i] = 0;
    }
    ptAll = ofVec3f(0, 0, 0);
    pt = ofVec3f(0, 0, 0);
    
    rate[0] = 1;
    ofSetSmoothLighting(true);
    cam.setPosition(ofGetWidth() / 2, ofGetHeight() / 2, 100);
    pointToView = ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2, 0);
    
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            Verts[j * WIDTH + i].set(0, 01, 0);
            Color[j * WIDTH + i].set(0.6, 0.5, 1.0, 0.0);
        }
    }
    Vbo.setVertexData(Verts, NUM_MIST, GL_DYNAMIC_DRAW);
    Vbo.setColorData(Color, NUM_MIST, GL_DYNAMIC_DRAW);
}

void v03::update(){
    rateDetermination();
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            xNoise = ofNoise(i * 0.03 + ofGetElapsedTimef() / 5) * 50.0;
            yNoise = ofNoise(j * 0.05 + ofGetElapsedTimef() / 10) * 50.0;
            zNoise = xNoise + yNoise;
            
            pixDisX = i / PARS + xNoise;
            pixDisY = j / PARS + yNoise;
            if (rate[0] > 0) {
                x[0] = rate[0] * cos(pixDisX) * cos(pixDisY) * 60 * (a01 + c01 * audioLevel01);
                y[0] = rate[0] * cos(pixDisX) * sin(pixDisY) * 60 * (a01 + c01 * audioLevel01);
                z[0] = rate[0] * sin(pixDisX) * zNoise / (a01 + c01 * audioLevel01);
            }
            if (rate[1] > 0) {
                x[1] = rate[1] * ((50 * (a01 + c01 * audioLevel01) + 20 * cos(pixDisX)) * cos(pixDisY) * (a02 + c02 * audioLevel01));
                y[1] = rate[1] * ((50 * (a03 + c03 * audioLevel01) + 20 * cos(pixDisX) * (a04 + c04 * audioLevel01)) * sin(pixDisY));
                z[1] = rate[1] * sin(pixDisX) * zNoise * 2 * (a05 + c05 * audioLevel01);
            }
            if (rate[2] > 0) {
                x[2] = rate[2] * (50 * (a01 + c01 * audioLevel01) + 10 * cos(pixDisX) * (a02 + c02 * audioLevel01)) * cos(pixDisY);
                y[2] = rate[2] * (50 * (a03 + c03 * audioLevel01) + 10 * cos(pixDisX) * (a04 + c04 * audioLevel01)) * sin(pixDisY);
                z[2] = rate[2] * ((sin(pixDisX) * (a05 + c05 * audioLevel01) * zNoise + 2 * pixDisY) * a06 - 70);
            }
            if (rate[3] > 0) {
                x[3] = rate[3] * (10 * (a01 + c01 * audioLevel01) + pixDisY * cos(pixDisX / 2) * (a02 + c02 * audioLevel01)) * cos(pixDisX);
                y[3] = rate[3] * (10 * (a03 + c03 * audioLevel01) + pixDisY * cos(pixDisX / 2) * (a04 + c04 * audioLevel01)) * sin(pixDisX);
                z[3] = rate[3] * pixDisY * sin(pixDisX / 2) * zNoise / 4 * (a05 + c05 * audioLevel01);
            }
            if (rate[4] > 0) {
                x[4] = rate[4] * (15 * cos(pixDisX) * (cos(pixDisX / 2) * cos(pixDisY) * (a01 + c01 * audioLevel01) + sin(pixDisX / 2) * sin(2 * pixDisY) + 3) * (a02 + c02 * audioLevel01) - 10);
                y[4] = - rate[4] * (15 * sin(pixDisX) * (cos(pixDisX / 2) * cos(pixDisY) * (a03 + c03 * audioLevel01) + sin(pixDisX / 2) * sin(2 * pixDisY) + 3) * (a04 + c04 * audioLevel01));
                z[4] = rate[4] * (40 * (-sin(pixDisX / 2) * cos(pixDisY) * (a05 + c05 * audioLevel01) + cos(pixDisX / 2) * cos(2 * pixDisY)) * (a06 + c06 * audioLevel01));
            }
            if (rate[5] > 0) {
                x[5] = rate[5] * sin(pixDisX) * 50 * (a01 + c01 * audioLevel01);
                y[5] = rate[5] * cos(pixDisX) * cos(pixDisY) * 50 * (a02 + c02 * audioLevel01);
                z[5] = rate[5] * cos(pixDisY) * 3 * zNoise * (a03 + c03 * audioLevel01);
            }
            if (rate[6] > 0) {
                x[6] = rate[6] * tan(pixDisX) * cos(pixDisY) * 50 * (a01 + c01 * audioLevel01);
                y[6] = rate[6] * cos(pixDisX) * sin(pixDisY) * 50 * (a02 + c02 * audioLevel01);
                z[6] = rate[6] * sin(pixDisX) * zNoise * 4 * (a03 + c03 * audioLevel01);
            }
            if (rate[7] > 0) {
                x[7] = rate[7] * tan(pixDisX) * tan(pixDisY) * 5 * (a01 + c01 * audioLevel01);
                y[7] = rate[7] * sin(pixDisY) * 10 * (a02 + c02 * audioLevel01);
                z[7] = rate[7] * cos(pixDisX) * zNoise * 4 * (a03 + c03 * audioLevel01);
            }
            if (rate[8] > 0) {
                x[8] = rate[8] * cos(pixDisY * pixDisX) * 20 * (a01 + c01 * audioLevel01);
                y[8] = rate[8] * sin(pixDisY) * sin(pixDisX) * 20 * (a02 + c02 * audioLevel01);
                z[8] = rate[8] * tan(pixDisX) * zNoise * 4 * (a03 + c03 * audioLevel01);
            }
            if (rate[9] > 0) {
                x[9] = rate[9] * sin(pixDisY) * 30 * (a01 + c01 * audioLevel01);
                y[9] = rate[9] * cos(pixDisX) * 20 * (a02 + c02 * audioLevel01);
                z[9] = rate[9] * cos(pixDisY) * zNoise * 5 * (a03 + c03 * audioLevel01);
                
            }
            if (rate[10] > 0) {
                x[10] = rate[10] * (xNoise - 5) * 10 * (a01 + c01 * audioLevel01);
                y[10] = rate[10] * (pixDisY * (a02 + c02 * audioLevel01) - HEIGHT / (2 * PARS) * (a03 + c03 * audioLevel01));
                z[10] = rate[10] * sin(pixDisX) * zNoise * 4 * (a04 + c04 * audioLevel01);
            }
            if (rate[11] > 0) {
                x[11] = rate[11] * (pixDisX * pixDisX / 70 * (a01 + c01 * audioLevel01) - 80 * (a02 + c02 * audioLevel01));
                y[11] = rate[11] * (50 * (a03 + c03 * audioLevel01) + 20 * cos(pixDisX) * (a04 + c04 * audioLevel01)) * sin(pixDisY);
                z[11] = rate[11] * sin(pixDisX) * zNoise * 2 * (a05 + c05 * audioLevel01);
            }
            if (rate[12] > 0) {
                x[12] = rate[12] * cos(pixDisX) * 30 * (a01 + c01 * audioLevel01);
                y[12] = rate[12] * ((pixDisY * (a02 + c02 * audioLevel01) - 5 * (a03 + c03 * audioLevel01)) * 3 - 100);
                z[12] = rate[12] * ((sin(pixDisX) * zNoise * 5 * tan(pixDisY) * (a04 + c04 * audioLevel01) + 2 * pixDisY * (a05 + c05 * audioLevel01)) - 70);
            }
            if (rate[13] > 0) {
                x[13] = rate[13] * (10 * (a01 + c01 * audioLevel01) + (a02 + c02 * audioLevel01) * pixDisY * cos(pixDisX / 2)) * cos(pixDisX) * sin(pixDisY);
                y[13] = rate[13] * (10 * (a03 + c03 * audioLevel01) + (a04 + c04 * audioLevel01) * pixDisY * cos(pixDisX / 2));
                z[13] = rate[13] * pixDisY * sin(pixDisX / 2) * zNoise / 4 * (a05 + c05 * audioLevel01);
            }
            if (rate[14] > 0) {
                x[14] = rate[14] * (10 * (cos(pixDisY / 2) * sin(pixDisY) + sin(pixDisX / 2) * sin(2 * pixDisY) + 3) - 10);
                y[14] = rate[14] * 15 * (cos(pixDisX / 2) * cos(pixDisY) + sin(pixDisX) * sin(2 * pixDisY) + 3);
                z[14] = rate[14] * 5 * (-sin(pixDisX / 2) * cos(pixDisY) + cos(pixDisX / 2) * zNoise);
            }
            pt = ofVec3f(0, 0, 0);
            for (int i = 0; i < sizeof(x) / sizeof(x[0]); i++) {
                pt.x += x[i];
                pt.y += y[i];
                pt.z += z[i];
            }
            ptAll = pt;
            Verts[j * WIDTH + i].set(ofVec3f(ptAll));
            Color[j * WIDTH + i].set(1.0, 1.0, 1.0, 0.5 * b05);
        }
    }
    Vbo.updateVertexData(Verts, NUM_MIST);
    Vbo.updateColorData(Color, NUM_MIST);
    
    pointToView.x = ofGetWidth() / 2 + 100 * sin(ofGetElapsedTimef() * 0.5);
    pointToView.y = ofGetHeight() / 2 + 100 * sin(ofGetElapsedTimef() * 0.35);
    pointToView.z = 100 * sin(ofGetElapsedTimef() * 0.4);
    
    node.setPosition(pointToView);
    node.setOrientation(ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2, -100));
}

void v03::draw(){
    cam.lookAt(node.getPosition());
    cam.begin();
    
    ofPushMatrix();
    ofTranslate(node.getPosition());
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    switch (drawMode) {
        case 1:
            Vbo.draw(GL_TRIANGLE_STRIP, 0, NUM_MIST);
            break;
        case 2:
            Vbo.draw(GL_LINE_STRIP, 0, NUM_MIST);
            break;
        case 3:
            Vbo.draw(GL_LINES, 0, NUM_MIST);
            break;
        case 4:
            Vbo.draw(GL_QUAD_STRIP, 0, NUM_MIST);
            break;
        default:
            break;
    }
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofPopMatrix();
    
    cam.end();
}

void v03::modeTF(int modeSelect) {
    //true or false judgement
    for (int i = 0; i < sizeof(b) / sizeof(b[0]); i++) {
        if (i != modeSelect - 1) b[i] = false;
    }
    b[modeSelect - 1] = true;
}

void v03::rateDetermination() {
    volume = audioLevel01;
    pitch = ofNoise(ofGetElapsedTimef()) * 100.0;
    if (volume > 1.25 * b03 && bVolume == false) {
        pmRate = 0.4;
        bVolume = true;
        modeSelect = ofRandom(1 + b01 * 14, 1 + b02 * 15);
        modeTF(modeSelect);
    }
    else if (volume <= 1.25 * b03) bVolume = false;
    
    // function rate calculation
    for (int i = 0; i < sizeof(rate) / sizeof(rate[0]); i++) {
        if (rate[i] > 0 && i != modeSelect - 1) rate[i] -= pmRate * pmRate;
    }
    if (rate[modeSelect - 1] < 1) rate[modeSelect - 1] += pmRate * pmRate;
    pmRate > 0 ? pmRate -= 0.0232 : pmRate = 0;
    
}
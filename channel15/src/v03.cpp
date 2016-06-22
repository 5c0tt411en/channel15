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
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            Verts[j * WIDTH + i].set(i - WIDTH/2, j - HEIGHT/2, 0);
            Color[j * WIDTH + i].set(0.6, 0.5, 1.0, 1.0);
        }
    }
    Vbo.setVertexData(Verts, NUM_MIST, GL_DYNAMIC_DRAW);
    Vbo.setColorData(Color, NUM_MIST, GL_DYNAMIC_DRAW);
}

void v03::update(){
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            xNoise = ofNoise(i * 0.03 + ofGetElapsedTimef() / 5) * 200.0;
            yNoise = ofNoise(j * 0.05 + ofGetElapsedTimef() / 10) * 200.0;
            zNoise = xNoise + yNoise;
            
            pixDisX = i / PARS + xNoise;
            pixDisY = j / PARS + yNoise;
            x_01 = /*cButton **/ cos(pixDisX) * cos(pixDisY) * 50;
            y_01 = /*dButton **/ cos(pixDisX) * sin(pixDisY) * 50;
            z_01 = /*bButton **/ sin(pixDisX) * zNoise * 4;
            Verts[j * WIDTH + i] = ofVec3f(x_01, y_01, z_01);
            Color[j * WIDTH + i].set(1.0, 1.0, 1.0, 0.5);
        }
    }
    Vbo.updateVertexData(Verts, NUM_MIST);
    Vbo.updateColorData(Color, NUM_MIST);
}

void v03::draw(){
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    glPointSize(3);
    Vbo.draw(GL_POINTS, 0, NUM_MIST);
    ofPopMatrix();
}
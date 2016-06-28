//
//  v06.cpp
//  channel15
//
//  Created by scott on 6/15/16.
//
//

#include "v06.h"

v06::v06(){
    
}

void v06::setup(){
    model.loadModel("scott.stl");
    model.setPosition(ofGetWidth()*.5, ofGetHeight() * 0.5, 0);
}

void v06::update(){
    
}

void v06::draw(){
    ofSetColor(255, 255, 255, b08);
    //get the model attributes we need
    ofVec3f scale = model.getScale();
    ofVec3f position = model.getPosition();
    float normalizedScale = model.getNormalizedScale();
    ofVboMesh mesh = model.getMesh(0);
    ofTexture texture;
    ofxAssimpMeshHelper& meshHelper = model.getMeshHelper( 0 );
    bool bHasTexture = meshHelper.hasTexture();
    if( bHasTexture ) {
        texture = model.getTextureForMesh(0);
    }
    
    ofMaterial material = model.getMaterialForMesh(0);
    
    ofPushMatrix();
    
    //translate and scale based on the positioning.
    ofTranslate(position);
//    ofRotate(-ofGetMouseX(), 0, 1, 0);
    ofRotate(90,1,0,0);
    
    
    ofScale(normalizedScale, normalizedScale, normalizedScale);
    ofScale(scale.x,scale.y,scale.z);
    
    //modify mesh with some noise
    float liquidness = 5;
    float amplitude = 0;
    float speedDampen = 5;
    vector<ofVec3f>& verts = mesh.getVertices();
    for(unsigned int i = 0; i < verts.size(); i++){
        verts[i].x += ofSignedNoise(verts[i].x/liquidness, verts[i].y/liquidness,verts[i].z/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
        verts[i].y += ofSignedNoise(verts[i].z/liquidness, verts[i].x/liquidness,verts[i].y/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
        verts[i].z += ofSignedNoise(verts[i].y/liquidness, verts[i].z/liquidness,verts[i].x/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
    }
    
    glPointSize(10);
    
    //draw the model manually
    if(bHasTexture) texture.bind();
    material.begin();
    //mesh.drawWireframe(); //you can draw wireframe too
    switch (drawMode) {
        case 1:
            mesh.drawWireframe();
            break;
        case 2:
            mesh.drawFaces();
            break;
        case 3:
            mesh.drawVertices();
            break;
        case 4:
            mesh.drawWireframe();
            mesh.drawVertices();
            break;
        default:
            break;
    }
    material.end();
    if(bHasTexture) texture.unbind();
    
    ofPopMatrix();
}

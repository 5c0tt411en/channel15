#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(2400, 600);
    //__________Syphon__________//
    client.setup();
    
    //__________Post Processing__________//
    //    ofBackground(0);
    
    ofSetCoordHandedness(OF_RIGHT_HANDED);
    
    // Setup post-processing chain
    post.init(ofGetWidth(), ofGetHeight());
    post.createPass<FxaaPass>()->setEnabled(false);
    post.createPass<BloomPass>()->setEnabled(false);
    post.createPass<DofPass>()->setEnabled(false);
    post.createPass<KaleidoscopePass>()->setEnabled(false);
    post.createPass<NoiseWarpPass>()->setEnabled(false);
    post.createPass<PixelatePass>()->setEnabled(false);
    post.createPass<EdgePass>()->setEnabled(false);
    post.createPass<VerticalTiltShifPass>()->setEnabled(false);
    post.createPass<GodRaysPass>()->setEnabled(false);
    
    // Setup light
    //    light.setPosition(1000, 1000, -2000);
}

//--------------------------------------------------------------
void ofApp::update(){
    //__________Post Processing__________//
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    //__________Post Processing__________//
    // copy enable part of gl state
    glPushAttrib(GL_ENABLE_BIT);
    
    // setup gl state
    glEnable(GL_DEPTH_TEST);
    //    light.enable();
    
    // begin scene to post process
    post.begin();
    
    //    ofDrawAxis(100);
    ofPushMatrix();
    //__________Syphon__________//
    ofSetColor(255);
    client.draw(0, 0);
    ofPopMatrix();
    // end scene and draw
    post.end();
    
    
    // set gl state back to original
    glPopAttrib();
    
    // draw help
    ofSetColor(0, 255, 255);
    //    ofDrawBitmapString("Number keys toggle effects, mouse rotates scene", 10, 20);
    for (unsigned i = 0; i < post.size(); ++i)
    {
        if (post[i]->getEnabled()) ofSetColor(0, 255, 255);
        else ofSetColor(255, 0, 0);
        ostringstream oss;
        oss << i << ": " << post[i]->getName() << (post[i]->getEnabled()?" (on)":" (off)");
        //        ofDrawBitmapString(oss.str(), 10, 20 * (i + 2));
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    unsigned idx = key - '0';
    if (idx < post.size()) post[idx]->setEnabled(!post[idx]->getEnabled());
    if (key == 'u') {
        ofSetWindowPosition(-1000, 0);
        ofSetFullscreen(true);
        //        ofSetWindowShape(2880, 900);
        //        ofSetWindowPosition(0, 0);
    }
    if (key == 't') {
        ofSetFullscreen(false);
        ofSetWindowPosition(0, 0);
    }
    if (key == 'm') {
        ofSetWindowPosition(-1280, 0);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}

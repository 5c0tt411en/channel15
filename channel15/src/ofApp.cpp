#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofBackground(0);
    ofSetVerticalSync(true);
    
    //OSC
    receiver.setup(PORT);
    
    //ofxFFT
    fft.setup();
    
    //visuals
    v01_ = new v01();
    v01_->setup();
    v02_ = new v02();
    v02_->setup();
    v03_ = new v03();
    v03_->setup();
    v04_ = new v04();
    v04_->setup();
    v05_ = new v05();
    v05_->setup();
    v06_ = new v06();
    v06_->setup();
    v07_ = new v07();
    v07_->setup();
    v08_ = new v08();
    v08_->setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    //ofxFFT
    fft.setThreshold(audioThreshold);
    fft.setPeakDecay(audioPeakDecay);
    fft.setMaxDecay(audioMaxDecay);
    fft.update();
    int num = 22000;
    float * audioData = new float[num];
    fft.getFftPeakData(audioData, num);
    for (int i = 0; i < num; i++) float audioValue = audioData[i];
    if (audioReactiveDB) {
//        dbLevel = audioData[dbTargetFreq];
//        dbLevel = ofMap(dbLevel, 0.0, 1.0, dbMin, dbMax);
//        while (dbLevel > dbMax) dbLevel = dbMax;
    }
    if (audioReactiveKBB) {
//        kbbLevel = audioData[kbbTargetFreq];
//        kbbLevel = ofMap(kbbLevel, 0.0, 1.0, kbbMin, kbbMax);
//        while (kbbLevel > kbbMax) kbbLevel = kbbMax;
    }
    delete[] audioData;
    
    ///OSC
    while (receiver.hasWaitingMessages()) {
        ofxOscMessage message;
        receiver.getNextMessage(&message);
        value = message.getArgAsFloat(0);
        items = ofSplitString(message.getAddress(), "/");
        address = ofToChar(items.back());
        cout << address << '\n';
        switch (address) {
            case 'a' : value = a01; break;
            case 'b' : value = a02; break;
            case 'c' : value = a03; break;
            case 'd' : value = a04; break;
            case 'e' : value = a05; break;
            case 'f' : value = a06; break;
            case 'g' : value = a07; break;
            case 'h' : value = a08; break;
            case 'i' : value = a09; break;
            case 'j' : value = a10; break;
            case 'k' : value = b01; break;
            case 'l' : value = b02; break;
            case 'm' : value = b03; break;
            case 'n' : value = b04; break;
            case 'o' : value = b05; break;
            case 'p' : value = b06; break;
            case 'q' : value = b07; break;
            case 'r' : value = b08; break;
            case 's' : value = b09; break;
            case 't' : value = b10; break;
            case 'u' : value = c01; break;
            case 'v' : value = c02; break;
            case 'w' : value = c03; break;
            case 'x' : value = c04; break;
            case 'y' : value = c05; break;
            case 'z' : value = c06; break;
            case '[' : value = c07; break;
            case ']' : value = c08; break;
            case '_' : value = c09; break;
            case '^' : value = c10; break;
            case '1' : visual = 1; break;
            case '2' : visual = 2; break;
            case '3' : visual = 3; break;
            case '4' : visual = 4; break;
            case '5' : visual = 5; break;
            case '6' : visual = 6; break;
            case '7' : visual = 7; break;
            case '8' : visual = 8; break;
        }
    }
    switch (visual) {
        case 1: v01_->update(); break;
        case 2: v02_->update(); break;
        case 3: v03_->update(); break;
        case 4: v04_->update(); break;
        case 5: v05_->update(); break;
        case 6: v06_->update(); break;
        case 7: v07_->update(); break;
        case 8: v08_->update(); break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapString("fps: " + ofToString((int)ofGetFrameRate()), 20, 20);
    //ofxFFT
    ofSetColor(255);
    fft.draw(fftX, fftY, fftW, fftH);
    
    switch (visual) {
        case 1: v01_->draw(); break;
        case 2: v02_->draw(); break;
        case 3: v03_->draw(); break;
        case 4: v04_->draw(); break;
        case 5: v05_->draw(); break;
        case 6: v06_->draw(); break;
        case 7: v07_->draw(); break;
        case 8: v08_->draw(); break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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

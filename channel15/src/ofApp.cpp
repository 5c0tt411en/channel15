#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255
                 );
    ofSetVerticalSync(true);
    
    //OSC
    receiver.setup(PORT);
    
    //ofxFFT
    fft.setup();
    col01.r = 251;
    col01.g = 89;
    col01.b = 101;
    col02.r = 39;
    col02.g = 108;
    col02.b = 185;
    audioThreshold = 0.92;
    audioPeakDecay = 0.96;
    audioMaxDecay = 0.97;
    targetFreq01 = 500;
    
    //visuals
    v01_ = new v01();
    v02_ = new v02();
    v03_ = new v03();
    v04_ = new v04();
    v05_ = new v05();
    v06_ = new v06();
    v07_ = new v07();
    v08_ = new v08();
    v01_->setup();
    v02_->setup();
    v03_->setup();
    v04_->setup();
    v05_->setup();
    v06_->setup();
    v07_->setup();
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
        audioLevel01 = audioData[targetFreq01];
        while (audioLevel01 > dbMax) audioLevel01 = 1.0;
    }
//    if (audioReactiveKBB) {
//        kbbLevel = audioData[kbbTargetFreq];
//        kbbLevel = ofMap(kbbLevel, 0.0, 1.0, kbbMin, kbbMax);
//        while (kbbLevel > kbbMax) kbbLevel = kbbMax;
//    }
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
    cout << audioLevel01 << '\n';
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapString("fps: " + ofToString((int)ofGetFrameRate()), 20, 20);
    
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
    //ofxFFT
//    ofSetColor(255);
//    fft.draw(fftX, fftY, fftW, fftH);
//    drawTargetFreq("01", targetFreq01, col01);
//    drawTargetFreq("02", targetFreq02, col02);
}

//--------------------------------------------------------------
void ofApp::drawTargetFreq(string targetName, int freq, ofColor &rgb){
    ofSetColor(rgb);
    ofDrawLine(fftX + (float)freq / 42.96825, fftY, fftX + (float)freq / 42.96825, fftY + fftH);
    targetName += '\n' + ofToString(freq) + "Hz";
    ofDrawBitmapString(targetName, fftX + (float)freq / (22000 / 512) + 5, fftY + fftH / 2);
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

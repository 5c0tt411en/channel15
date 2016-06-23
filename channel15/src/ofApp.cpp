#include "ofApp.h"

//parameters
float   a01, a02, a03, a04, a05, a06, a07, a08, a09, a10,
b01, b02, b03, b04, b05, b06, b07, b08, b09, b10,
c01, c02, c03, c04, c05, c06, c07, c08, c09, c10;
float    audioLevel01,
audioLevel02;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    //OSC
    receiver.setup(PORT);
    
    //Syphon
    mainOutputSyphonServer.setName("channel15");
    
    //ofxFFT
    fft.setup();
    col01.r = 251;
    col01.g = 89;
    col01.b = 101;
    col02.r = 39;
    col02.g = 108;
    col02.b = 185;
    audioThreshold = 0.90;
    audioPeakDecay = 0.97;
    audioMaxDecay = 0.99;
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
    audioLevel01 = audioData[targetFreq01];
    //    while (audioLevel01 > dbMax) audioLevel01 = 1.0;
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
            case 'a' : a01 = value; break;
            case 'b' : a02 = value; break;
            case 'c' : a03 = value; break;
            case 'd' : a04 = value; break;
            case 'e' : a05 = value; break;
            case 'f' : a06 = value; break;
            case 'g' : a07 = value; break;
            case 'h' : a08 = value; break;
            case 'i' : a09 = value; break;
            case 'j' : a10 = value; break;
            case 'k' : b01 = value; break;
            case 'l' : b02 = value; break;
            case 'm' : b03 = value; break;
            case 'n' : b04 = value; break;
            case 'o' : b05 = value; break;
            case 'p' : b06 = value; break;
            case 'q' : b07 = value; break;
            case 'r' : b08 = value; break;
            case 's' : b09 = value; break;
            case 't' : b10 = value; break;
            case 'u' : c01 = value; break;
            case 'v' : c02 = value; break;
            case 'w' : c03 = value; break;
            case 'x' : c04 = value; break;
            case 'y' : c05 = value; break;
            case 'z' : c06 = value; break;
            case '[' : c07 = value; break;
            case ']' : c08 = value; break;
            case '_' : c09 = value; break;
            case '^' : c10 = value; break;
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
        case 1: v01_->update(); v03_->update(); v04_->update(); v05_->update(); break;
        case 2: v01_->update(); v03_->update(); v04_->update(); v05_->update(); break;
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
    ofColor col01 = ofColor(90, 224, 189);
    ofColor col02 = ofColor(0, 127, 60);
    ofBackgroundGradient(col01, col02, OF_GRADIENT_CIRCULAR);
    title = "fps : " + ofToString(ofGetFrameRate(),1) + " fps";
    ofSetWindowTitle(title);
    
    switch (visual) {
        case 1: v01_->draw(); v03_->draw(); v04_->draw(); v05_->draw(); break;
        case 2: v01_->draw(); v03_->draw(); v04_->draw(); v05_->draw();
                if (audioLevel01 > b03) v03_->drawMode = ofRandom(1 + b01 * 3, 1 + b02 * 4); break;
        case 3: v03_->draw(); break;
        case 4: v04_->draw(); break;
        case 5: v05_->draw(); break;
        case 6: v06_->draw(); break;
        case 7: v07_->draw(); break;
        case 8: v08_->draw(); break;
        default:
            break;
    }
    //Syphon
    mainOutputSyphonServer.publishScreen();
    string debugString = "audio01: " + ofToString(audioLevel01) + '\n';
           debugString += "pmRate : " + ofToString(v03_->pmRate) + '\n';
           debugString += "mode    : " + ofToString(v03_->modeSelect) + '\n';
    debugString += "tfJudge   : ";
    for (int i = 0; i < 20; i++) {
        i != 19 ? debugString += ofToString(v03_->b[i]) + ", " : debugString += ofToString(v03_->b[i]) + '\n';
    }
    debugString += "rate      : ";
    for (int i = 0; i < 20; i++) {
        i != 19 ? debugString += ofToString(v03_->rate[i]) + ", " : debugString += ofToString(v03_->rate[i]) + '\n';
    }
           debugString += "ptAll   : " + ofToString(v03_->ptAll) + '\n';
    for (int i = 0; i < 20; i++) {
           debugString += "pt[" + ofToString(i) + "]   : " + ofToString(v03_->x[i]) + ", " + ofToString(v03_->y[i]) + ", " + ofToString(v03_->z[i]) + '\n';
    }
    ofDrawBitmapStringHighlight(debugString, 20, 20);
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

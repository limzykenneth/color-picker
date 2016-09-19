#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    grabSizeX = 100;
    grabSizeY = 100;
    sampleSize = 10;
    grabber.setup(grabSizeX, grabSizeY);

    font.load("InconsolataGo-Regular.ttf", 15);

    hexCode.setup();
    hexCode.bounds.x = 10;
    hexCode.bounds.y = 20;
    hexCode.bounds.width = 150;
    hexCode.bounds.height = 30;

    redValue.setup();
    redValue.bounds.x = 10;
    redValue.bounds.y = hexCode.bounds.y + hexCode.bounds.height;
    redValue.bounds.width = 80;
    redValue.bounds.height = 30;

    greenValue.setup();
    greenValue.bounds.x = 10;
    greenValue.bounds.y = redValue.bounds.y + redValue.bounds.height;
    greenValue.bounds.width = 80;
    greenValue.bounds.height = 30;

    blueValue.setup();
    blueValue.bounds.x = 10;
    blueValue.bounds.y = greenValue.bounds.y + greenValue.bounds.height;
    blueValue.bounds.width = 80;
    blueValue.bounds.height = 30;

    hexCode.setFont(font);
    redValue.setFont(font);
    greenValue.setFont(font);
    blueValue.setFont(font);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofPixels pixels;
    float finalX, finalY;
    float posX = ofGetWindowPositionX();
    float posY = ofGetWindowPositionY();

    finalX = ofGetMouseX() + posX - grabSizeX/2;
    finalY = ofGetMouseY() + posY - grabSizeY/2;
    grabber.grabScreen(finalX, finalY);

    tex = grabber.getTextureReference();
    tex.readToPixels(pixels);

    pixels.crop(grabSizeX/2 - 5, grabSizeY/2 - 5, sampleSize, sampleSize);

    grabColor = averageColor(&pixels);
}

//--------------------------------------------------------------
void ofApp::draw(){
    tex.draw(0, 0, ofGetWidth(), ofGetHeight());

    ofPushStyle();
        int hex = grabColor.getHex();
        ofSetColor(255);
        ofDrawRectangle(hexCode.bounds.x, hexCode.bounds.y, hexCode.bounds.width, hexCode.bounds.height);
        ofDrawRectangle(redValue.bounds.x, redValue.bounds.y, redValue.bounds.width, redValue.bounds.height);
        ofDrawRectangle(greenValue.bounds.x, greenValue.bounds.y, greenValue.bounds.width, greenValue.bounds.height);
        ofDrawRectangle(blueValue.bounds.x, blueValue.bounds.y, blueValue.bounds.width, blueValue.bounds.height);

        ofSetColor(0);
        hexCode.text = ofToHex(hex).replace(0, 2, " #");
        hexCode.draw();

        int rStr = grabColor.r;
        redValue.text = " r: " + ofToString(rStr);
        redValue.draw();

        int gStr = grabColor.g;
        greenValue.text = " g: " + ofToString(gStr);
        greenValue.draw();

        int bStr = grabColor.b;
        blueValue.text = " b: " + ofToString(bStr);
        blueValue.draw();
    ofPopStyle();

    ofPushStyle();
        ofNoFill();
        ofSetColor(0, 0, 0, 120);
        ofDrawRectangle(ofGetWidth()/2-5, ofGetHeight()/2-5, 10, 10);
    ofPopStyle();
}

//--------------------------------------------------------------
ofColor ofApp::averageColor(const ofPixels* pix){
    ofColor avgColor;
    int rSum = 0;
    int gSum = 0;
    int bSum = 0;

    for(int x = 0; x < sampleSize; x++) {
        for(int y = 0; y < sampleSize; y++) {
            ofColor pixelColor = pix->getColor(x, y);
            rSum += pixelColor.r;
            gSum += pixelColor.g;
            bSum += pixelColor.b;
        }
    }

    int samples = sampleSize * sampleSize;
    avgColor.r = rSum / samples;
    avgColor.b = bSum / samples;
    avgColor.g = gSum / samples;

    return avgColor;
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

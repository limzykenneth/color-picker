#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Color Picker #");
    
    grabSizeX = 100;
    grabSizeY = 100;
    sampleSize = 5;
    grabber.setup(grabSizeX, grabSizeY, retina);

    font.load("InconsolataGo-Regular.ttf", 15);

    pauseSampling = false;
    
    copyButton.addListener(this, &ofApp::copyButtonPressed);
    gui.setup();
    gui.add(copyButton.setup("Copy Hex"));
    gui.add(color.setup("RGB", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    hsb.add(hue.set("Hue", 0, 0, 255));
    hsb.add(saturation.set("Saturation", 0, 0, 255));
    hsb.add(brightness.set("Brightness", 0, 0, 255));
    hsb.setName("HSB");
    gui.add(hsb);
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

    if(retina){
        pixels.crop(grabSizeX - 3, grabSizeY - 3, sampleSize, sampleSize);
    }else{
        pixels.crop(grabSizeX/2 - 5, grabSizeY/2 - 5, sampleSize, sampleSize);
    }

    if(!pauseSampling) {
        grabColor = averageColor(&pixels);
        color = grabColor;
        hue = grabColor.getHue();
        saturation = grabColor.getSaturation();
        brightness = grabColor.getBrightness();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    tex.draw(0, 0, ofGetWidth(), ofGetHeight());
    gui.setPosition(1, 1);
    gui.setSize(150, gui.getHeight());
    gui.setWidthElements(150);
    gui.setDefaultHeight(gui.getHeight());
    gui.draw();
    
    int hex = grabColor.getHex();
    int fontY = gui.getHeight() + 30;
    
    ofPushStyle();
        if(pauseSampling) ofSetColor(120, 255, 120);
        ofRectangle rect = font.getStringBoundingBox(ofToHex(hex).replace(0, 2, "#"), 10, fontY);
        ofDrawRectangle(rect.x - 5, rect.y - 5, rect.width + 10, rect.height + 10);
    ofPopStyle();
    
    ofPushStyle();
    ofPushMatrix();
        ofNoFill();
        ofSetColor(0, 0, 0, 120);
        ofTranslate(-sampleSize/2, -sampleSize/2);
        ofDrawRectangle(ofGetWidth()/2-5, ofGetHeight()/2-5, sampleSize, sampleSize);
    ofPopMatrix();
    ofPopStyle();
    
    ofPushStyle();
        ofSetColor(0);
        font.drawString(ofToHex(hex).replace(0, 2, "#"), 10, fontY);
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
    switch (key) {
        case '=':
            if (sampleSize < 50) sampleSize++;
            break;
        case '-':
            if (sampleSize > 1) sampleSize--;
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == OF_KEY_RETURN){
        pauseSampling = !pauseSampling;
        if(pauseSampling){
            int hex = grabColor.getHex();
            ofxClipboard::copy(ofToHex(hex).replace(0, 2, "#"));
        }
    }
}

//--------------------------------------------------------------
void ofApp::copyButtonPressed(){
    int hex = grabColor.getHex();
    ofxClipboard::copy(ofToHex(hex).replace(0, 2, "#"));
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

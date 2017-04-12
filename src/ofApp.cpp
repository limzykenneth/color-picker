#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Color Picker #");
    
    bool retina = true;
    grabSizeX = 200;
    grabSizeY = 200;
    sampleSize = 5;
    grabber.setup(grabSizeX, grabSizeY, retina);

    font.load("InconsolataGo-Regular.ttf", 15);

    setupTextDisplay(&hexCode, 10, 20, 100, 30);

    setupTextDisplay(&redValue, 10, hexCode.bounds.y + hexCode.bounds.height + 10, 80, 30);
    setupTextDisplay(&greenValue, 10, redValue.bounds.y + redValue.bounds.height, 80, 30);
    setupTextDisplay(&blueValue, 10, greenValue.bounds.y + greenValue.bounds.height, 80, 30);

    setupTextDisplay(&hueValue, 10, blueValue.bounds.y + blueValue.bounds.height + 10, 80, 30);
    setupTextDisplay(&satValue, 10, hueValue.bounds.y + hueValue.bounds.height, 80, 30);
    setupTextDisplay(&brightValue, 10, satValue.bounds.y + satValue.bounds.height, 80, 30);

    pauseSampling = false;
}

//--------------------------------------------------------------
void ofApp::setupTextDisplay(ofxTextInputField* field, float x, float y, float w, float h){
    field->setup();
    field->bounds.x = x;
    field->bounds.y = y;
    field->bounds.width = w;
    field->bounds.height = h;
    field->setFont(font);
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
        if(!pauseSampling) {
            ofSetColor(255);
        }else{
            ofSetColor(120, 255, 120);
        }
        ofDrawRectangle(hexCode.bounds);

        ofDrawRectangle(redValue.bounds);
        ofDrawRectangle(greenValue.bounds);
        ofDrawRectangle(blueValue.bounds);

        ofDrawRectangle(hueValue.bounds);
        ofDrawRectangle(satValue.bounds);
        ofDrawRectangle(brightValue.bounds);

        ofSetColor(0);
        if(!pauseSampling) hexCode.text = ofToHex(hex).replace(0, 2, " #");
        hexCode.draw();

        int rStr = grabColor.r;
        if(!pauseSampling) redValue.text = " r: " + ofToString(rStr);
        redValue.draw();

        int gStr = grabColor.g;
        if(!pauseSampling) greenValue.text = " g: " + ofToString(gStr);
        greenValue.draw();

        int bStr = grabColor.b;
        if(!pauseSampling) blueValue.text = " b: " + ofToString(bStr);
        blueValue.draw();

        int hStr = grabColor.getHueAngle();
        if(!pauseSampling) hueValue.text = " H: " + ofToString(hStr);
        hueValue.draw();

        int sStr = ofMap(grabColor.getSaturation(), 0, 255, 0, 100, true);
        if(!pauseSampling) satValue.text = " S: " + ofToString(sStr);
        satValue.draw();

        int brStr = ofMap(grabColor.getLightness(), 0, 255, 0, 100, true);
        if(!pauseSampling) brightValue.text = " B: " + ofToString(brStr);
        brightValue.draw();
    ofPopStyle();

    ofPushStyle();
    ofPushMatrix();
        ofNoFill();
        ofSetColor(0, 0, 0, 120);
        ofTranslate(-sampleSize/2, -sampleSize/2);
        ofDrawRectangle(ofGetWidth()/2-5, ofGetHeight()/2-5, sampleSize, sampleSize);
    ofPopMatrix();
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
    }
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

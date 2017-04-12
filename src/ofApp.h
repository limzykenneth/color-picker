#pragma once

#include "ofMain.h"
#include "ofxScreenGrab.h"
#include "ofxClipboard.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void copyButtonPressed();

    ofColor averageColor(const ofPixels* pix);

    ofxScreenGrab grabber;
    float grabSizeX, grabSizeY, sampleSize;
    ofTexture tex;
    ofColor grabColor;

    ofTrueTypeFont font;
    
    ofxButton copyButton;
    ofxColorSlider color;
    ofParameterGroup hsb;
    ofParameter<int> hue;
    ofParameter<int> saturation;
    ofParameter<int> brightness;
    
    ofxPanel gui;

    bool pauseSampling;
    bool retina = true;
};

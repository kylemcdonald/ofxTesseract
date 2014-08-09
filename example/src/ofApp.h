#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxTesseract.h"
#include "CvUtils.h"

using namespace cv;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
		string runOcr(float scale, int medianSize);
		
		ofxTesseract tess;
		ofImage img, scaled;
		string ocrResult;

        ofxFloatSlider scale;
        ofxIntSlider medianSize;

        ofxButton process;

        ofxPanel gui;

        void processButtonPressed();

};

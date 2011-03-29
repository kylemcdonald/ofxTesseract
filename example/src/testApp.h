#pragma once

#include "ofMain.h"
#include "ofxTesseract.h"
#include "ofxAutoControlPanel.h"
#include "CvUtils.h"
using namespace cv;

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
		string runOcr(float scale, int medianSize);
		
		ofxTesseract tess;
		ofImage img, scaled;
		string ocrResult;
		ofxAutoControlPanel panel;
};

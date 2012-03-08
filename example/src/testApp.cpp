#include "testApp.h"

void testApp::setup(){
	panel.setup();
	panel.addPanel("Preprocessing");
	panel.addSlider("scale", "scale", 2.5, 1, 4);
	panel.addSlider("medianSize", "medianSize", 2, 0, 12, true);

	tess.setup();
	tess.setWhitelist("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.,");
	tess.setAccuracy(ofxTesseract::ACCURATE);
	tess.setMode(ofxTesseract::AUTO);
	
	img.loadImage("article.png");
	img.setImageType(OF_IMAGE_GRAYSCALE);
	img.update();
}

void testApp::update(){
	if(panel.hasValueChanged("scale") || panel.hasValueChanged("medianSize")) {
		ocrResult = runOcr(panel.getValueF("scale"), panel.getValueI("medianSize"));
		scaled.update();
		panel.clearAllChanged();
	}
}

void testApp::draw(){	
	ofPushMatrix();
	
	ofTranslate(300, 0);
	
	ofSetColor(0);	
	vector<string> lines = ofSplitString(ocrResult, "\n");
	for(int i = 0; i < lines.size(); i++) {
		ofDrawBitmapString(lines[i], 10, 20 + i * 12);
	}
	
	ofSetColor(255);
	img.draw(0, 200);
	scaled.draw(0, 400);
	
	ofPopMatrix();
}

// depending on the source of the text you want to OCR,
// you might need to preprocess it. here i'm doing a
// simple resize followed by a median blur.
string testApp::runOcr(float scale, int medianSize) {
	scaled = img;
	
	// resize and median blur the image
	scaled.resize(img.getWidth() * scale, img.getHeight() * scale);
	medianBlur(scaled, medianSize);
	
	return tess.findText(scaled);
}


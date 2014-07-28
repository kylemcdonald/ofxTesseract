#include "ofApp.h"

void ofApp::setup(){

	gui.setup(); // most of the time you don't need a name

	process.addListener(this,&ofApp::processButtonPressed);

	gui.add(scale.setup( "scale", 2.5, 1, 4 ));
	gui.add(medianSize.setup( "medianSize", 2, 0, 12 ));
	gui.add(process.setup("process"));

	tess.setup();
	tess.setWhitelist("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.,");
	tess.setAccuracy(ofxTesseract::ACCURATE);
	tess.setMode(ofxTesseract::AUTO);
	
	img.loadImage("article.png");
	img.setImageType(OF_IMAGE_GRAYSCALE);
	img.update();


    ocrResult = runOcr(scale, medianSize);
}

void ofApp::processButtonPressed()
{
    ocrResult = runOcr(scale, medianSize);
}


void ofApp::update(){
}


void ofApp::draw(){
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

    gui.draw();

}

// depending on the source of the text you want to OCR,
// you might need to preprocess it. here i'm doing a
// simple resize followed by a median blur.
string ofApp::runOcr(float scale, int medianSize) {
	scaled = img;
	
	// resize and median blur the image
	scaled.resize(img.getWidth() * scale, img.getHeight() * scale);

	medianBlur(scaled, medianSize);

	return tess.findText(scaled);
}


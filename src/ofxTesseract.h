#pragma once

/*
	ofxTesseract by @kcimc
	with help from rtwomey and julapy
	based on this discussion
	http://www.openframeworks.cc/forum/viewtopic.php?f=10&t=3728&p=27402
*/

#include "baseapi.h"
#include "ofMain.h"

class ofxTesseract {
public:
	enum Mode {
		AUTO = tesseract::PSM_AUTO,
		COLUMN = tesseract::PSM_SINGLE_COLUMN,
		BLOCK = tesseract::PSM_SINGLE_BLOCK,
		LINE = tesseract::PSM_SINGLE_LINE,
		WORD = tesseract::PSM_SINGLE_WORD,
		CHAR = tesseract::PSM_SINGLE_CHAR
	};
	
	enum Accuracy  {
		ACCURATE = tesseract::AVS_MOST_ACCURATE,
		FAST = tesseract::AVS_FASTEST
	};

	// dataPath is where to find a folder with tessdata inside
	// default arguments assume bin/data/tessdata/eng.traineddata
	void setup(string dataPath = "", bool absolute = false, string language = "eng");

	// you must call these after setup, contrary to the tesseract-ocr docs
	// whitelist means only those characters are used
	void setWhitelist(string whitelistCharacters);
	// blacklist means none of those characters are used
	void setBlacklist(string blacklistCharacters);
	
	// provides a hint for how to segment things
	// by default this is ofxTesseract::AUTO
	void setMode(Mode mode);
	
	// transform a mode name into a constant, for loading from XML files
	static Mode getMode(string modeName);
	
	// either ofxTesseract::ACCURATE or ofxTesseract::FAST
	// by default it is ofxTesseract::FAST
	void setAccuracy(Accuracy accuracy);
		
	// finally, do OCR on an image, or on an image within an roi
	// make sure your text is at least 10 pixels tall
	// OF_IMAGE_COLOR and OF_IMAGE_GRAYSCALE are both fine
	string findText(ofImage& img);
	string findText(ofImage& img, ofRectangle& roi);

	//raw pixel data? why not!
	string findText(ofPixels& pixels);
	string findText(ofPixels& pixels, ofRectangle& roi);
	
	//HOCR goodness
	string findTextHocr(ofImage& img);
	string findTextHocr(ofImage& img, ofRectangle& roi);
	
protected:
	tesseract::TessBaseAPI tess;

};
#include "ofxTesseract.h"

void ofxTesseract::setup(string dataPath, bool absolute, string language) {
	// this has to be done in setup() instead of a constructor
	// because the OF data path isn't ready during construction
	string absoluteTessdataPath = absolute ? dataPath : ofToDataPath(dataPath, true);
	
	// there is some kind of bug in Init that ignores the datapath argument
	// so we override it by setting an environment variable
	setenv("TESSDATA_PREFIX", absoluteTessdataPath.c_str(), 1);
	tess.Init(absoluteTessdataPath.c_str(), language.c_str());
	setMode(AUTO);
}

void ofxTesseract::setWhitelist(string whitelistCharacters) {
	tess.SetVariable("tessedit_char_whitelist", whitelistCharacters.c_str());
}

void ofxTesseract::setBlacklist(string blacklistCharacters) {
	tess.SetVariable("tessedit_char_blacklist", blacklistCharacters.c_str());
}

void ofxTesseract::setMode(ofxTesseractMode mode) {
	tess.SetPageSegMode((tesseract::PageSegMode) mode);
}

ofxTesseract::ofxTesseractMode ofxTesseract::getMode(string modeName) {
	if(modeName == "AUTO") {
		return AUTO;
	} else if(modeName == "COLUMN") {
		return COLUMN;
	} else if(modeName == "BLOCK") {
		return BLOCK;
	} else if(modeName == "LINE") {
		return LINE;
	} else if(modeName == "WORD") {
		return WORD;
	} else if(modeName == "CHAR") {
		return CHAR;
	}
}

void ofxTesseract::setAccuracy(ofxTesseractAccuracy accuracy) {
	tess.SetAccuracyVSpeed((tesseract::AccuracyVSpeed) accuracy);
}

string ofxTesseract::findText(ofImage& img) {
	ofRectangle roi(0, 0, img.getWidth(), img.getHeight());
	return findText(img, roi);
}

string ofxTesseract::findText(ofImage& img, ofRectangle& roi) {
	ofPixels& pixels = img.getPixelsRef();
	int bytesPerPixel = pixels.getBytesPerPixel();
	return tess.TesseractRect(
		pixels.getPixels(),
		bytesPerPixel,
		pixels.getWidth() * bytesPerPixel,
		roi.x, roi.y,
		roi.width, roi.height
	);
}
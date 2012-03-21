#include "ofxTesseract.h"

void ofxTesseract::setup(string dataPath, bool absolute, string language) {
	// this has to be done in setup() instead of a constructor
	// because the OF data path isn't ready during construction
	string absoluteTessdataPath = absolute ? dataPath : ofToDataPath(dataPath, true);
	
	// there is some kind of bug in Init that ignores the datapath argument
	// so we override it by setting an environment variable
	setenv("TESSDATA_PREFIX", absoluteTessdataPath.c_str(), 1);
	tess.Init(absoluteTessdataPath.c_str(), language.c_str());

	// fixes issues with hocr - see http://code.google.com/p/tesseract-ocr/issues/detail?id=463
	tess.SetInputName("");
	setMode(AUTO);
}


void ofxTesseract::setWhitelist(string whitelistCharacters) {
	tess.SetVariable("tessedit_char_whitelist", whitelistCharacters.c_str());
}

void ofxTesseract::setBlacklist(string blacklistCharacters) {
	tess.SetVariable("tessedit_char_blacklist", blacklistCharacters.c_str());
}

void ofxTesseract::setMode(Mode mode) {
	tess.SetPageSegMode((tesseract::PageSegMode) mode);
}

ofxTesseract::Mode ofxTesseract::getMode(string modeName) {
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

void ofxTesseract::setAccuracy(Accuracy accuracy) {
	tess.SetAccuracyVSpeed((tesseract::AccuracyVSpeed) accuracy);
}

string ofxTesseract::findText(ofImage& img) {
	ofRectangle roi(0, 0, img.getWidth(), img.getHeight());
	return findText(img, roi);
}

string ofxTesseract::findText(ofImage& img, ofRectangle& roi) {
	ofPixels& pixels = img.getPixelsRef();
	return findText(pixels, roi);
}

string ofxTesseract::findText(ofPixels& pixels) {
	ofRectangle roi(0, 0, pixels.getWidth(), pixels.getHeight());
	return findText(pixels, roi);
}

string ofxTesseract::findText(ofPixels& pixels, ofRectangle& roi) {
	int bytesPerPixel = pixels.getBytesPerPixel();
	return tess.TesseractRect(
							  pixels.getPixels(),
							  bytesPerPixel,
							  pixels.getWidth() * bytesPerPixel,
							  roi.x, roi.y,
							  roi.width, roi.height
							  );
}

string ofxTesseract::findTextHocr(ofImage& img) {
	ofRectangle roi(0, 0, img.getWidth(), img.getHeight());
	return findTextHocr(img, roi);
}

string ofxTesseract::findTextHocr(ofImage& img, ofRectangle& roi) {
	ofPixels& pixels = img.getPixelsRef();
	int bytesPerPixel = pixels.getBytesPerPixel();

	tess.SetImage(
				  pixels.getPixels(),
				  img.getWidth(),
				  img.getHeight(),
				  bytesPerPixel,
				  pixels.getWidth() * bytesPerPixel
	);
	
	tess.SetRectangle(
					  roi.x, roi.y,
					  roi.width, roi.height
	);

	return tess.GetHOCRText(0);
}
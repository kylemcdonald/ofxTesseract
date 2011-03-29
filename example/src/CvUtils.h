#pragma once

// small excerpt from forthcoming of-cv utility/addon

#include "ofConstants.h"
#include "ofImage.h"
#include "cv.h"

namespace cv {

inline int getCvImageType(const ofImageType& ofType) {
	switch(ofType) {
		case OF_IMAGE_GRAYSCALE: return CV_8UC1;
		case OF_IMAGE_COLOR: return CV_8UC3;
		case OF_IMAGE_COLOR_ALPHA: return CV_8UC4;
		default: return CV_8UC1;
	}
}

inline Mat getMat(ofImage& img) {
	int cvImageType = getCvImageType(img.getPixelsRef().getImageType());
	return Mat(img.getHeight(), img.getWidth(), cvImageType, img.getPixels(), 0);
}

inline int forceOdd(int x) {
	return (x / 2) * 2 + 1;
}

inline void medianBlur(ofImage& img, int size) {
	size = forceOdd(size);
	Mat mat = getMat(img);
	medianBlur(mat, mat, size);
}

};
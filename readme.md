# ofxTesseract is an addon for openFrameworks that provides access to the Tesseract OCR library.

*Warning: the training data provided here causes a segmentation fault in some cases. Please use the [latest version](http://code.google.com/p/tesseract-ocr/downloads/list?can=2&q=eng.tar.gz&colspec=Filename+Summary+Uploaded+ReleaseDate+Size+DownloadCount) available from the Tesseract project.*

## Overview

I've included a copy of eng.traineddata in the example, but if you need a newer one or a different language you can get it from the tesseract-ocr website:

https://code.google.com/p/tesseract-ocr/downloads/detail?name=eng.traineddata.gz&can=2&q=eng

Once downloaded, it should be placed in your data directory under a special directory named 'tessdata':

myApp/bin/data/tessdata/eng.traineddatat

Example usage of ofxTesseract looks like:

```cpp
#include "ofxTesseract.h"
...
ofxTesseract ocr;
ofImage img;
...
ocr.setup();
ocr.setWhitelist("0123456789");
tess.setAccuracy(ofxTesseract::ACCURATE);
img.loadImage("text.png");
string result = ocr.findText(img);
cout << result << endl;
```

## Building Tesseract

If you need to build the library from scratch, you need to be familiar with [building static libraries](http://thecoredump.org/2004/02/building-a-gnu-autoconf-static-library/). For Tesseract, after downloading the source, it looks something like this:

	cd /Users/username/tesseract
	./runautoconf
	./configure --disable-shared --enable-static --prefix=/Users/username/tesseract
	make
	sudo make install

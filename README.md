# ofxSimpleOsc

## Dependency

- `ofxOsc`
- C++11 or higher

## Usage

- ofApp.h

```cpp
#pragma once

#include "ofMain.h"
#include "ofxOsc.h" // Add this
#include "ofxSimpleOsc.h" // Add this

class ofApp : public ofBaseApp{
	public:
    	void setup();
		void update();
		void draw();

        // ...

		ofxSimpleOsc::Receiver osc_receiver; // Receiver
		ofxSimpleOsc::Sender osc_sender; // Sender

		ofColor color;
		ofColor background_color;
		ofPoint point;

		float w;
		float h;

}
```

- ofApp.cpp

```cpp
//--------------------------------------------------------------
void ofApp::setup(){
	ofLogToConsole();
	ofSetVerticalSync(true);
	ofSetFrameRate(60);

    // initial values
	color = ofColor(255, 0, 0);
	background_color = ofColor(0);
	point = ofPoint(0, 0);
	w = 100.0;
	h = 100.0;

    // define receiver
	osc_receiver.setup(7777, [&](const ofxOscMessage& msg) {
        // filter OSC
		ofxSimpleOsc::filter(msg)
			.when("/test", [&]() {
				ofLog() << "test OSC received!";
			})
			.bind("/color", &color)
			.bind("/background", &background_color)
			.bind("/point", &point)
			.bind("/size", &w, &h)
			.else_show_warning();
	});
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(background_color);

	ofSetColor(color);
	ofDrawEllipse(point, w, h);
}
```
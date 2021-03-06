# ofxSimpleOsc

## Features
- Print every logs of received OSCs (you can also disable)
- Show warning when you missed handling (use `Filter#else_show_warning()` or `Receiver#showNotHandledWarning()` )
- Selectable APIs as you like ( filter chain style, bind values, lambda block / callback style, or simply use if-else style )

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
        void keyPressed(int key);

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

        // setup receiver
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
			.when("/test2", [&](float a, float b) {
			        ofLog() << "test2 (" << a << "," << b << ")";
			})
			.when("/test3", [&](const ofxOscMessage& m){
                                ofLog() << "test3 (" << m.getArgAsString(0) << ")";
                        })
			.else_show_warning(); // Show not handled warning

                        // .else_([&](const ofxOscMessage& m){
                        //      // If you want to write code at end of method chain,
                        //      // please add .else_() instead of .else_show_warning()
                        //
                        //      // To warn, in this block, you can use
		        //	// osc_receiver.showNotHandledWarning();
                        // })

                // NOTE: You can also simply use ofxOscMessage, without using Filter
		//
		// if (msg.getAddress() == "/test") {
		//	 ofLog() << "test OSC received!";
		// }
		// else {
		//	 osc_receiver.showNotHandledWarning();
		// }

                // NOTE: And if you want, you can move above codes into
                //       `void ofApp::onOscMessage(const ofxOscMessage& msg)` or so on
		//
                // ofApp::onOscMessage(msg);
                //

	});

        
        // NOTE: ofxSimpleOsc prints logs of every received OSC messages.
        //       if you don't need them, you can disable:
        //
	// osc_receiver.setOscLogEnabled(false);

        // setup sender
        osc_sender.setup("localhost", 7778);
}

//--------------------------------------------------------------
void ofApp::update(){
	//osc_sender.send("/color", color);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(background_color);

	ofSetColor(color);
	ofDrawEllipse(point, w, h);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's') {
		osc_sender.send("/size", w, h);
	}
	else if (key == 'p') {
		osc_sender.send("/point", point);
	}
	else if(key == 't') {
		osc_sender.send("/test", "this is test from ofxSimpleOsc");
	}
}
```

## License

MIT License
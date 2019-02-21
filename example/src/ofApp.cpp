#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofLogToConsole();
	ofSetVerticalSync(true);
	ofSetFrameRate(60);

	color = ofColor(255, 0, 0);
	background_color = ofColor(0);
	point = ofPoint(0, 0);

	w = 100.0;
	h = 100.0;

	osc_receiver.setup(7777, [&](const ofxOscMessage& msg) {
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

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
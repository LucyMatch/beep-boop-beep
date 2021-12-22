#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetWindowTitle("osc events example");
	ofSetFrameRate(60); // run at 60 fps
	ofSetVerticalSync(true);
	ofBackground(255, 255, 255);
	ofEnableAlphaBlending();
	ofSetBackgroundAuto(false);
	ofSetCircleResolution(200);

	controller = OSCController();
	ofAddListener( ControllerEvent::events, this, &ofApp::onControllerEvent );

}

//--------------------------------------------------------------
void ofApp::update(){
	controller.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

	//bg
	ofSetColor(ofColor(bg, bg_alpha));
	ofFill();
	ofDrawRectangle(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth(), ofGetHeight());

}

void ofApp::onControllerEvent(ControllerEvent& e) {
	std::cout << "Controller Event : ";
	std::cout << e.input->name << " ";
	std::cout << e.input->id << " ";
	if (e.input->name == "pot") {
		std::cout << e.input->fvalue << std::endl;
	}
	else {
		std::cout << e.input->bvalue << std::endl;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}


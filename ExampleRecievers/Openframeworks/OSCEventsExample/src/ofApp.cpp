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

	//start controller
	controller = OSCController();

	//add listeners
	//general all inputs
	ofAddListener( ControllerEvent::events, this, &ofApp::onControllerEvent );

	//input type specific triggers
	ofAddListener( ControllerRangeEvent::events, this, &ofApp::onControllerRangeEvent);
	ofAddListener( ControllerSwitchEvent::events, this, &ofApp::onControllerSwitchEvent);
	ofAddListener( ControllerButtonEvent::events, this, &ofApp::onControllerButtonEvent);

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

//--------------------------------------------------------------
void ofApp::onControllerEvent(ControllerEvent& e) {
	string msg = "Controller Event : ";
	msg += e.input->name + " " + ofToString(e.input->id) + " ";
	msg += e.input->name == "pot" ? ofToString(e.input->fvalue) : (e.input->bvalue ? "true" : "false");
	std::cout << msg << std::endl;
}

//--------------------------------------------------------------
void ofApp::onControllerRangeEvent(ControllerRangeEvent& e) {
	string msg = "Range Event : ";
	msg += e.input->name + " " + ofToString(e.input->id) + " " + ofToString(e.input->fvalue);
	std::cout << msg << std::endl;
}

//--------------------------------------------------------------
void ofApp::onControllerSwitchEvent(ControllerSwitchEvent& e) {
	string msg = "Switch Event : ";
	msg += e.input->name + " " + ofToString(e.input->id) + " ";
	msg += e.input->bvalue ? "true" : "false";
	std::cout << msg << std::endl;
}

//--------------------------------------------------------------
void ofApp::onControllerButtonEvent(ControllerButtonEvent& e) {
	string msg =  "Button Event : ";
	msg +=  e.input->name + " " + ofToString(e.input->id) + " ";
	msg += e.input->bvalue ? "true" : "false";
	std::cout << msg << std::endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}


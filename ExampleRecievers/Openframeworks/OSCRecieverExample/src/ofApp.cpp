#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetWindowTitle("oscReceiveExample");
	ofSetFrameRate(60); // run at 60 fps
	ofSetVerticalSync(true);
	ofBackground(255, 255, 255);
	ofEnableAlphaBlending();
	ofSetBackgroundAuto(false);

	// listen on the given port
	ofLog() << "listening for osc messages on port " << PORT;
	receiver.setup(PORT);

}

//--------------------------------------------------------------
void ofApp::update(){

	while ( receiver.hasWaitingMessages() ) {
		ofxOscMessage m;
		receiver.getNextMessage(m);
		auto data = parseMessage(m);
		if (data.id >=0) {	//if new valid 
			updateInputs(data);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	//bg
	ofSetColor(255,255,255, bg_alpha);
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

}

//--------------------------------------------------------------
void ofApp::updateInputs( INPUT_DATA data ) {

	//a new valid input

	//here we quickly map our inputs to values - so they are updated when new values are recieved
	//eventually should do an event based example in here too



}

//--------------------------------------------------------------
INPUT_DATA ofApp::parseMessage(ofxOscMessage m) {

	INPUT_DATA data;
	data.id = -1; //flag for if unrecognized - if a valid input found this will change to >= 0

	auto addr = m.getAddress();
	string input_pot = "pot", input_switch = "swt", input_btn = "btn";
	string parent_address = "controller";
	bool unrecognized = false;

	std::cout << addr << std::endl;

	if (addr.find(parent_address)) {

		if (ofIsStringInString(addr, input_pot)) {
			//data.id = ofToInt(ofSplitString(addr, "_")[1]);
			data.name = input_pot;
			data.fvalue = m.getArgAsFloat(0);
			std::cout << "OSC : received controller pot input : ";
			std::cout << data.id << " : " << data.fvalue << std::endl;
		}
		else if (ofIsStringInString(addr, input_switch)) {
			//data.id = ofToInt(ofSplitString(addr, "_")[1]);
			data.name = input_switch;
			data.bvalue = m.getArgTypeName(0) == "T" ? true : false;
			std::cout << "OSC : received controller switch input : ";
			std::cout << data.id << " : " << data.bvalue << std::endl;
		}
		else if (ofIsStringInString(addr, input_btn)) {
			//data.id = ofToInt(ofSplitString(addr, "_")[1]);
			data.name = input_btn;
			data.bvalue = m.getArgTypeName(0) == "T" ? true : false;
			std::cout << "OSC : received controller btn input : ";
			std::cout << data.id << " : " << data.bvalue << std::endl;
		}
		else {unrecognized = true;}
	}
	else {unrecognized = true;}

	if (unrecognized) {
		string msg = " unrecognized : " + addr + " : ";
		for (auto i = 0; i < m.getNumArgs(); i++) {
			msg += m.getArgTypeName(i);
			// display the argument - make sure we get the right type
			if (m.getArgType(i) == OFXOSC_TYPE_INT32) {
				msg += ofToString(m.getArgAsInt32(i));
			}
			else if (m.getArgType(i) == OFXOSC_TYPE_FLOAT) {
				msg += ofToString(m.getArgAsFloat(i));
			}
			else if (m.getArgType(i) == OFXOSC_TYPE_STRING) {
				msg += m.getArgAsString(i);
			}
			else if (m.getArgType(i) == OFXOSC_TYPE_TRUE) {
				msg += "true";
			}
			else if (m.getArgType(i) == OFXOSC_TYPE_FALSE) {
				msg += "false";
			}
			else {
				msg += "unhandled argument type " + m.getArgTypeName(i);
			}
		}
	}

	return data;

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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

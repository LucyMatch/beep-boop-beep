#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetWindowTitle("oscReceiveExample");
	ofSetFrameRate(60); // run at 60 fps
	ofSetVerticalSync(true);
	ofBackground(255, 255, 255);
	ofEnableAlphaBlending();
	ofSetBackgroundAuto(false);
	ofSetCircleResolution(200);
	ofSetRectMode(OF_RECTMODE_CENTER);

	// listen on the given port
	ofLog() << "listening for osc messages on port " << PORT;
	receiver.setup(PORT);

}

//--------------------------------------------------------------
void ofApp::update(){

	while ( receiver.hasWaitingMessages() ) {

		//retrieve data
		ofxOscMessage m;
		receiver.getNextMessage(m);

		//sort data into IPNUT_DATA struct
		INPUT_DATA data = parseMessage(m);

		if (data.id >=0) {	//if new valid 
			//Update associated variables
			updateInputs(data);
		}
	}

	updateShape();
}

//--------------------------------------------------------------
void ofApp::draw(){

	//bg
	ofSetColor(ofColor(bg, bg_alpha));
	ofFill();
	ofDrawRectangle(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth(), ofGetHeight());

	for (auto s : shapes) {
		if (fill)
			ofFill();
		else
			ofNoFill();
		ofSetColor(ofColor(s.c, s.alpha));

		//option 1
		ofDrawCircle( s.x, s.y, s.r );

		//option 2
		//ofRotateDeg(45);
		//ofDrawRectangle(s.x, s.y, s.r, s.r);

		//option 3
		//ofPushMatrix();
		//	ofTranslate(s.x, s.y);
		//	ofRotateDeg(45);
		//	ofDrawRectangle(0, 0, s.r, s.r);
		//ofPopMatrix();
	}
	
}

//--------------------------------------------------------------
void ofApp::updateInputs( INPUT_DATA data ) {

	//a new valid input

	//here we quickly map our inputs to values - so they are updated when new values are recieved
	//eventually should do an event based example in here too ( w/ pointers likely to assigned variables )
	//as well a building out a template based approach to this configuration

	string updatemsg = "Updated value : ";

	//Pots
	if (data.name == "pot") {
		switch (data.id)
		{
			case 0:
				bg_alpha = ofMap(data.fvalue, 0, 1, 0, 255);
				updatemsg += "bg alpha => " + ofToString(bg_alpha);
				break;
			case 1:
				bg = ofColor(bg.r, bg.g, ofMap(data.fvalue, 1, 0, 0, 255));
				updatemsg += "bg blue => " + ofToString(ofMap(data.fvalue, 0, 1, 0, 255));
				break;
			case 2:
				bg = ofColor( bg.r, ofMap(data.fvalue, 0, 1, 0, 255), bg.b);
				updatemsg += "bg green => " + ofToString(ofMap(data.fvalue, 0, 1, 0, 255));
				break;
			case 3:
				bg = ofColor(ofMap(data.fvalue, 1, 0, 0, 255), bg.g, bg.b);
				updatemsg += "bg red => " + ofToString(ofMap(data.fvalue, 0, 1, 0, 255));
				break;
			default:
				break;
		}
	}

	//btns
	if (data.name == "swt") {
		switch (data.id)
		{
		case 0:
			fill = data.bvalue;
			updatemsg += " fill => " + fill;
			break;
		case 1:
			grow = data.bvalue;
			updatemsg += " grow => " + grow;
			break;
		case 2:
			fade = data.bvalue;
			updatemsg += " fade => " + fade;
			break;
		case 3:
			bounce = data.bvalue;
			updatemsg += " bounce => " + bounce;
			break;
		default:
			break;
		}
	}

	//swts
	if (data.name == "btn") {
		switch (data.id)
		{
		case 0:
			if (data.bvalue)spawnShape(ofColor(255,0,0));
			updatemsg += " spawned red ";
			break;
		case 1:
			if (data.bvalue)spawnShape(ofColor(255,255,0));
			updatemsg += " spawned yellow ";
			break;
		case 2:
			if (data.bvalue)spawnShape(ofColor(0,255,0));
			updatemsg += " spawned green ";
			break;
		case 3:
			if (data.bvalue)spawnShape(ofColor(0,0,255));
			updatemsg += " spawned blue ";
			break;
		default:
			break;
		}
	}

	std::cout << updatemsg << std::endl;

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
			data.id = ofToInt(ofSplitString(addr, "_")[1]);
			data.name = input_pot;
			data.fvalue = m.getArgAsFloat(0);
			std::cout << "OSC : received controller pot input : ";
			std::cout << data.id << " : " << data.fvalue << std::endl;
		}
		else if (ofIsStringInString(addr, input_switch)) {
			data.id = ofToInt(ofSplitString(addr, "_")[1]);
			data.name = input_switch;
			data.bvalue = m.getArgTypeName(0) == "T" ? true : false;
			std::cout << "OSC : received controller switch input : ";
			std::cout << data.id << " : " << data.bvalue << std::endl;
		}
		else if (ofIsStringInString(addr, input_btn)) {
			data.id = ofToInt(ofSplitString(addr, "_")[1]);
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
void ofApp::spawnShape( ofColor c ) {

	SHAPE temp;
	temp.c = c;
	temp.x = mouseX;
	temp.y = mouseY;
	if (!grow) {
		temp.r = ofGetWidth() / 2;
		temp.growing = false;
	}
	shapes.push_back(temp);

}

//--------------------------------------------------------------
void ofApp::updateShape() {

	for (auto &s : shapes) {

		//std::cout << "-----" << std::endl;
		//std::cout << s.r << " / " << s.alpha << "  ->  ";
		

		if (bounce) {
			//bounce radius
			if (s.growing)
				s.r++;
			else
				s.r--;
			//switch directions
			if (s.r < 0 || s.r > ofGetWidth() /2)s.growing = !s.growing;

			//bounce alpha
			if (fade) {
				if (s.fading)
					s.alpha = ofClamp(--s.alpha, 0, 255);
				else
					s.alpha = ofClamp(++s.alpha, 0, 255);
				//switch directions
				if (s.alpha <= 0 || s.alpha >= 255)s.fading = !s.fading;
			}
		}else {
			if (grow)
				s.r++;
			else
				s.r = ofClamp(--s.r, 0, ofGetWidth() / 2);

			if (fade)s.alpha = ofClamp(--s.alpha, 0, 255);

			//mark as dead if need be
			if (s.alpha == 0 || s.r == 0 || s.r >= ofGetWidth() / 2)s.dead = true;
		}

		//std::cout << s.r << " / " << s.alpha << std::endl;
		//std::cout << "-----" << std::endl;
	}

	//erase any dead ones
	for (int i = 0; i < shapes.size(); i++) {
		if (shapes[i].dead)shapes.erase(shapes.begin() + i);
	}

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
	shapes.clear();
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

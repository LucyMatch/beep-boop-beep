#include "OSCController.h"

//--------------------------------------------------------------
OSCController::OSCController() {
	setup();
}

//--------------------------------------------------------------
OSCController::~OSCController() {

}

//--------------------------------------------------------------
void OSCController::setup() {

	// listen on the given port
	ofLog() << "listening for osc messages on port " << PORT;
	receiver.setup(PORT);

	//	set up sender
	if (sender.setup(SENDHOST, SENDPORT)) {
		//if success sender set up
		//send a msg to ctrl to say hi + retrieve intial input values
		ofxOscMessage m;
		m.setAddress("/msg/init");
		sender.sendMessage(m, false);
	}

}

//--------------------------------------------------------------
void OSCController::update() {

	while (receiver.hasWaitingMessages()) {

		//retrieve data
		ofxOscMessage m;
		receiver.getNextMessage(m);

		//sparse msg
		parseMessage(m);

	}

}

//--------------------------------------------------------------
void OSCController::parseMessage(ofxOscMessage m) {

	auto addr = m.getAddress();
	string input_pot = "pot", input_switch = "swt", input_btn = "btn";
	string parent_address = "controller";
	bool unrecognized = false;

	INPUT_DATA data;

	//@TODO: templatize how these are defined

	if (addr.find(parent_address)) {

		if (ofIsStringInString(addr, input_pot)) {
			data.id = ofToInt(ofSplitString(addr, "_")[1]);
			data.name = input_pot;
			data.fvalue = m.getArgAsFloat(0);
			//std::cout << "OSC : received controller pot input : ";
			//std::cout << data.id << " : " << data.fvalue << std::endl;
		}
		else if (ofIsStringInString(addr, input_switch)) {
			data.id = ofToInt(ofSplitString(addr, "_")[1]);
			data.name = input_switch;
			data.bvalue = m.getArgTypeName(0) == "T" ? true : false;
			//std::cout << "OSC : received controller switch input : ";
			//std::cout << data.id << " : " << data.bvalue << std::endl;
		}
		else if (ofIsStringInString(addr, input_btn)) {
			data.id = ofToInt(ofSplitString(addr, "_")[1]);
			data.name = input_btn;
			data.bvalue = m.getArgTypeName(0) == "T" ? true : false;
			//std::cout << "OSC : received controller btn input : ";
			//std::cout << data.id << " : " << data.bvalue << std::endl;
		}
		else { unrecognized = true; }
	}
	else { unrecognized = true; }

	
	if (!unrecognized) {
		//if it was reconized msg trigger event
		triggerEvent(data);
	}
	else {
		//if not recogniozed print to console
		parseUnrecognizedMessage(m);
	}

}

//--------------------------------------------------------------
void OSCController::parseUnrecognizedMessage(ofxOscMessage m) {

	auto addr = m.getAddress();
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

//--------------------------------------------------------------
void OSCController::triggerEvent(INPUT_DATA data) {

	//trigger general input data event
	static ControllerEvent newEvent;
	newEvent.input = &data;
	ofNotifyEvent( ControllerEvent::events, newEvent );

	//trigger type specifc events
	//@TODO: tie these definitions to config file
	if (data.name == ("pot")) {
		static ControllerRangeEvent type_event;
		type_event.input = &data;
		ofNotifyEvent(ControllerRangeEvent::events, type_event);
	}
	else if (data.name == ("swt")) {
		static ControllerSwitchEvent type_event;
		type_event.input = &data;
		ofNotifyEvent(ControllerSwitchEvent::events, type_event);
	}
	else if (data.name == ("btn")) {
		static ControllerButtonEvent type_event;
		type_event.input = &data;
		ofNotifyEvent(ControllerButtonEvent::events, type_event);
	}

}
/*
			V1 . OSC CONTROLLER CLASS
current controller configeration is hardcoded - goal of current class is to
recieve message and trigger events - for ofApp to attach listeners to

osc message approach =
/Contoller/ [ type_channel ]
i.e. /controller/btn_0 .../swt_0 .../pot_0

/

current layout / configeration
x4 pots x4 btns x4 switches x4 leds

@TODO: 
- simple events firing
- configuration file to define controller layout + components
- configuartion file for ports / connect settings etc

*/

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ControllerEvent.h"

// listening port
#define PORT 12345

//sending port
#define SENDHOST "localhost"
#define SENDPORT 57121


class OSCController {

public : 

	OSCController();
	~OSCController();

	void setup();
	void update();
	void parseMessage(ofxOscMessage m);
	void parseUnrecognizedMessage(ofxOscMessage m);
	void triggerEvent( INPUT_DATA data );


	
private :

	ofxOscReceiver receiver;
	ofxOscSender sender;

};

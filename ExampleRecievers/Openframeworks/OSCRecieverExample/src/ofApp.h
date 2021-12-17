#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

// listening port
#define PORT 12345

//	this example recieves OSC messages + demonstrates simple usage with variables 
//	hardcoded configeration based on v1 of phidget controller
//	for beep-boop-beep controller project

//osc message approach =
// /Contoller/type_channel
// i.e. /controller/btn_0 .../swt_0 .../pot_0

//current layout / configeration 
// x4 pots
// x4 btns
// x4 switches
// x4 leds 

struct INPUT_DATA {
	int id;
	string name;
	float fvalue;
	bool bvalue;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		INPUT_DATA parseMessage(ofxOscMessage m);
		void updateInputs( INPUT_DATA data );

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		float bg_alpha = 0;

		ofxOscReceiver receiver;
		ofxOscSender sender;
		
};

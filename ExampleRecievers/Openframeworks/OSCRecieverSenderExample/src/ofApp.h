#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

// listening port
#define PORT 12345

#define SENDHOST "localhost"
#define SENDPORT 57121

//	this example recieves OSC messages + demonstrates simple usage with variables 
// //additionally has a osc send on init to handshake + recieve inital values - with led indicator for success
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

struct SHAPE {
	float x = 0;
	float y = 0;
	float alpha = 255;
	float r = 0;
	bool dead = false;
	bool growing = true;
	bool fading = true;
	ofColor c = ofColor(0, 0, 0);
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		INPUT_DATA parseMessage(ofxOscMessage m);
		void updateInputs( INPUT_DATA data );

		void spawnShape(ofColor c);
		void updateShape();

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

		float bg_alpha = 255;
		ofColor bg = ofColor(255,255,255,255);

		vector<SHAPE> shapes;
		bool fill = false, grow = false, fade = false, bounce = false;

		ofxOscReceiver receiver;
		ofxOscSender sender;
		
};

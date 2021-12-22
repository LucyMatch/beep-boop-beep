/*
			OSC EVENTS EXAMPLE

This example demostrates having custom events fired when 
reciving new osc messages and tying them to sketch variables 

*/

#pragma once

#include "ofMain.h"
#include "OSCController.h"
#include "ControllerEvent.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void onControllerEvent(ControllerEvent &e);

		void keyPressed(int key);
		void mousePressed(int x, int y, int button);

		OSCController controller;

		float bg_alpha = 255;
		ofColor bg = ofColor(255,255,255,255);
		
};

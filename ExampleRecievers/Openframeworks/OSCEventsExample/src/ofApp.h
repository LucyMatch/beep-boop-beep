/*
			OSC EVENTS EXAMPLE

This example demostrates having custom events fired when 
reciving new osc messages and how to add listeners
there is a listener for all inputs + for each range type
this sketch prints values to console for testing

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
		void onControllerRangeEvent(ControllerRangeEvent& e);
		void onControllerSwitchEvent(ControllerSwitchEvent& e);
		void onControllerButtonEvent(ControllerButtonEvent& e);

		void keyPressed(int key);
		void mousePressed(int x, int y, int button);

		OSCController controller;

		float bg_alpha = 255;
		ofColor bg = ofColor(255,255,255,255);
		
};

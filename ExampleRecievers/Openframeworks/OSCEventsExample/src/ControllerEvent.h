/*
V1 . CONTROLLER EVENT CLASS
*/

#pragma once
#include "ofMain.h"

struct INPUT_DATA {
	int id = -1;
	string name = "default";
	float fvalue = -1.0;
	bool bvalue = false;
};

//all type of events
class ControllerEvent : public ofEventArgs {

	public:

		ControllerEvent() {
			input = new INPUT_DATA;
		}

		INPUT_DATA *input;
		static ofEvent<ControllerEvent> events;
		
};

//range based controlls - pots / sensors / voltage inputs
class ControllerRangeEvent : public ofEventArgs {

public:

	ControllerRangeEvent() {
		input = new INPUT_DATA;
	}

	INPUT_DATA* input;
	static ofEvent<ControllerRangeEvent> events;

};

//switch based controls - true / false with set states
class ControllerSwitchEvent : public ofEventArgs {

public:

	ControllerSwitchEvent() {
		input = new INPUT_DATA;
	}

	INPUT_DATA* input;
	static ofEvent<ControllerSwitchEvent> events;

};

//button based controls - true / false with temporary states
class ControllerButtonEvent : public ofEventArgs {

public:

	ControllerButtonEvent() {
		input = new INPUT_DATA;
	}

	INPUT_DATA* input;
	static ofEvent<ControllerButtonEvent> events;

};


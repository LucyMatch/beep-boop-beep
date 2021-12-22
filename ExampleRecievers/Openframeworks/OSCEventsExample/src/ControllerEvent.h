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

class ControllerEvent : public ofEventArgs {

	public:

		ControllerEvent() {
			input = new INPUT_DATA;
		}

		INPUT_DATA *input;
		static ofEvent<ControllerEvent> events;
		
};


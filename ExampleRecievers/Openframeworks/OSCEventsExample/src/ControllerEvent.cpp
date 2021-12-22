#include "ControllerEvent.h"

//define static members
ofEvent<ControllerEvent> ControllerEvent::events;
ofEvent<ControllerRangeEvent> ControllerRangeEvent::events;
ofEvent<ControllerSwitchEvent> ControllerSwitchEvent::events;
ofEvent<ControllerButtonEvent> ControllerButtonEvent::events;
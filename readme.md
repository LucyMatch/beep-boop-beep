# CUSTOM CONTROLLER - WIP

Current hardware set up
* phidgets 8/8/8
* x4 analogue inputs ( pots )
* x8 digital inputs ( x4 buttons / x4 switches )
* x4 digital output ( x4 leds )

Current goal 
* create simple software interface to run the controller once plugged in that can interface with my other code sketches
* it will take inputs standardize them and send out using a different protocol so it can be connected to various programs easily + hopevially via a class / template
* for now i'm thinking OSC, specifcally so we can easily hook up with OF sketches + potentially GUI
* eventually would be configurable via a settings file etc... so it can run many different layouts of hardware configurations

Stack approach
* Phidgets + node + websockets
* express node server
* node-osc - for sending message out ( should I just use websockets? maybe both? nice to do this with options )
* simple web page for testing?

TODO
* input mapping
* osc output
* websocket output
* simple react interface local for visualising / debugging
* templatized layouts / congifuration
* other output protocol options
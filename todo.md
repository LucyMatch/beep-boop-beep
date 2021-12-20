fEATURE

* get initial values
  * on sketch start - we want to send an osc message to controller's server to say hey you're connected!
  * in return the controller osc server sends a payload of all input values to sketch osc so they can init values
* Templates
  * templatize controller configuration on node side - easy json file? defining which channels are which type of inputs 
    * + if they are high low / low high ( some pots are opposite whoops )
      + also define address names 
      + define any threshold settings... 
  * a way to templatize / have a config file on the sketch side - define a format
    * then create a command for node app that can generate the config file needed for the sketch


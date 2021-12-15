var phidget22 = require('phidget22');
var phidget = require('./scripts/phidgets');
var dialog = require('dialog-node');

require('dotenv').config() //get main config settings from .env

let runtime_function = null;

const selectMode = (code, retVal, stderr) => {
    if(retVal == "1"){
        runtime_function = phidget.runOSC;
        console.log("set controller mode to basic osc");
    }else{
        runtime_function = phidget.runTest;
        console.log("set controller mode to default test");
    }
    //prompt user to start controller
    dialog.question("Start Controller?", "Runtime", 5000, start)
}

const start = (code, retVal, stderr) => {
    if(retVal == "OK"){
        var conn = new phidget22.Connection(5661, 'localhost');
        conn.connect().then(runtime_function);
    }else{
        return;
    }
}

//Run it!
//if in development mode skip the dialogue prompts
if(process.env.DEVMODE == "true"){

    runtime_function = phidget.runOSC;
    var conn = new phidget22.Connection(5661, 'localhost');
    conn.connect().then(runtime_function);

}else{

    //run first dialogue to begin start up prompts
    dialog.entry(
        "Please type a number to select a mode to start the controller in;  0 - Test / 1 - Basic OSC", 
        "Controller Mode Selection", 
        5000, 
        selectMode
    );
    
}


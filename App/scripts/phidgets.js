var phidget22 = require('phidget22');
var testFunctions = require( './phidgetFunctions/basicTest');
var oscFunctions = require( './phidgetFunctions/basicOSC');

//containers
let voltage_inputs = [], digital_inputs = [], digital_outputs = [];

//flags utility
var configed = false;

//@TODO: eventually this would be from a config file
var vinput_count = 4, dinput_count = 8, doutput_count = 4;
var system_output_indicator = 1;


const runOSC = () => {

    console.log("hi");

    //create objects per controllers configuration
    init();

    //set callback functions to osc functions
    voltage_inputs.forEach(i => {
        i.onVoltageRatioChange = (voltageRatio) => {
            oscFunctions.voltageInputChange(i, voltageRatio)
        }
        i.onError = (code, description) =>{
            oscFunctions.onError(i, code, description);
        }
    })

    digital_inputs.forEach(i => {
        i.onStateChange = (state) => {
            oscFunctions.digitalInputChange(i, state)
        }
        i.onError = (code, description) =>{
            oscFunctions.onError(i, code, description);
        }
    })

    digital_outputs.forEach(i => {
        i.onError = (code, description) =>{
            oscFunctions.onError(i, code, description);
        }
    })

    //open channels + do led startup animation
    defaultStart();

}

const runTest = () => {

    init();

    voltage_inputs.forEach(i => {
        i.onVoltageRatioChange = (voltageRatio) => {
            testFunctions.voltageInputChange(i, voltageRatio)
        }
        i.onError = (code, description) =>{
            testFunctions.onError(i, code, description);
        }
    })

    digital_inputs.forEach(i => {
        i.onStateChange = (state) => {
            testFunctions.digitalInputChange(i, state)
        }
        i.onError = (code, description) =>{
            testFunctions.onError(i, code, description);
        }
    })

    digital_outputs.forEach(i => {
        i.onError = (code, description) =>{
            testFunctions.onError(i, code, description);
        }
    })

    defaultStart();
}

const init = () => {

    close(true);

    for( let i = 0; i < vinput_count; i++ ){
        let temp = new phidget22.VoltageRatioInput()
        temp.setChannel(i)
        voltage_inputs.push( temp )
    }

    for( let i = 0; i < dinput_count; i++ ){
        let temp = new phidget22.DigitalInput()
        temp.setChannel(i)
        digital_inputs.push( temp )
    }

    for( let i = 0; i < doutput_count; i++ ){
        let temp = new phidget22.DigitalOutput()
        temp.setChannel(i) 
        digital_outputs.push( temp )
    }
    
}

const config = () => {
    //@TODO: eventually also tied to a config file

    //setting thresholds for analogue / voltage inputs
    voltage_inputs.forEach( (i, index) => {
        i.setVoltageRatioChangeTrigger( 0.001 )
        .catch( (err)=>{
            console.log("phidget error updating change trigger");
            console.log(err);
        })
    })

    configed = true;

}

const defaultStart = () => {

    var openPromiseList = []
    voltage_inputs.forEach(i => {openPromiseList.push(i.open(5000));})
    digital_inputs.forEach(i => {openPromiseList.push(i.open(5000));})
    digital_outputs.forEach(i => {openPromiseList.push(i.open(5000));})

    Promise.all(openPromiseList).then(function(values){
        console.log("Controller On & Ready");

        //check if configed
        if(!configed)config();

        //set system led ons - start up "animation"
        digital_outputs.forEach(i => i.setDutyCycle(1))

        //turn off all but system light
        let o_index;
        var timeLightsOff = setInterval(function(){
            o_index = digital_outputs.findIndex((element, index) => index != system_output_indicator && element.getState());
            if(o_index >= 0 )
                digital_outputs[o_index].setDutyCycle(0);
            else
                clearInterval(timeLightsOff);
        }, 250)
    })

}

const close = ( clear = false ) => {
    if(voltage_inputs)voltage_inputs.forEach(i => i.close())
    if(digital_inputs)digital_inputs.forEach(i => i.close())
    if(digital_outputs)digital_outputs.forEach(i => i.close())
    if(clear){
        voltage_inputs.length = 0;
        digital_inputs.length = 0;
        digital_outputs.length = 0;
    }
}

module.exports = { runOSC, runTest }

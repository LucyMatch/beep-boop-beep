var osc = require("osc");
require('dotenv').config() //get main config settings from .env

var osc_settings = { 
    onInitCallBack : () => {return { msg : 'default on init' }},
    onInitComplete : () => {console.log('default on init complete');},
    localSendAddress: process.env.UDPSENDHOST,
    localSendPort: parseInt(process.env.UDPSENDPORT)
}

//OSC LISTENING AT PORT
//configure osc udp
var udpPort = new osc.UDPPort({
    localAddress: process.env.UDPHOST,
    localPort: parseInt(process.env.UDPPORT)
});

var getIPAddresses = function () {
    var os = require("os"),
        interfaces = os.networkInterfaces(),
        ipAddresses = [];

    for (var deviceName in interfaces) {
        var addresses = interfaces[deviceName];
        for (var i = 0; i < addresses.length; i++) {
            var addressInfo = addresses[i];
            if (addressInfo.family === "IPv4" && !addressInfo.internal) {
                ipAddresses.push(addressInfo.address);
            }
        }
    }

    return ipAddresses;
};

udpPort.on("ready", function () {
    var ipAddresses = getIPAddresses();

    console.log("Listening for OSC over UDP.");
    ipAddresses.forEach(function (address) {
        console.log(" Host:", address + ", Port:", udpPort.options.localPort);
    });
});

udpPort.on("message", function (oscMessage) {

    console.log(oscMessage);

    //if recieved init msgs
    //send back all current values
    if(oscMessage.address.includes("init")){
        console.log("recieved init handshake from output application");
        var payload = osc_settings.onInitCallBack();
        payload.forEach( i => {
            udpPort.send({
                address : i.address,
                args : [
                    {   
                        type: i.type,
                        value : i.value
                    }
                ]
            },process.env.UDPSENDHOST, parseInt(process.env.UDPSENDPORT))
        })
        osc_settings.onInitComplete();
    }

});

udpPort.on("error", function (err) {
    console.log(err);
});

///FUNCTIONS

const openPort = () =>{
    console.log("Opening OSC");
    udpPort.open();
}

//CALLBACKS FOR PHIDGETS

const voltageInputChange = (self, voltage) => {
    udpPort.send({
        address : "/controller/pot_" + self._channel,
        args : [
            {   
                type: "f",
                value : voltage
            }
        ]
    },process.env.UDPSENDHOST, parseInt(process.env.UDPSENDPORT))
}

const onError = (self, code, description) => {
    console.log('Error with : ');
    console.log(self.name + " - " + self._channel);
    console.log('Description: ' + description.toString())
    console.log('---------');
}

const digitalInputChange = (self, state) => {

    //@TODO: again would want this type of configuration tied to a config template
    //want to differienate the address switches + btns are send as diff behaviours
    var addr_type = "btn_" + self._channel
    if(self._channel > 3) addr_type = "swt_" + (parseInt(self._channel) - 4)

    //@TODO:
    //these flags aren't full standard
    //and you're meant to sent empty packet with this type
    //may just wanna send a string- determine when doing recievers
    var flag = "T";
    if(!state)flag = "F"

    udpPort.send({
        address : "/controller/" + addr_type,
        args : [
            {
                type : flag,
                value : state
            }
        ]
    },process.env.UDPSENDHOST, parseInt(process.env.UDPSENDPORT))

}

module.exports = { 
openPort,
voltageInputChange, 
digitalInputChange,  
onError,
osc_settings
}

const voltageInputChange = (self, voltage) => {
        console.log("Voltage Input " + self._channel);
        console.log('Voltage : ' + voltage.toString())
        console.log('----------');
}

const onError = (self, code, description) => {
        console.log('Error with : ');
        console.log(self.name + " - " + self._channel);
        console.log('Description: ' + description.toString())
        console.log('---------');
}

const digitalInputChange = (self, state) => {
        console.log("Digital Input " + self._channel);
        console.log('State : ' + state.toString())
        console.log('----------');
}

module.exports = { 
    voltageInputChange, 
    digitalInputChange,  
    onError
}

var phidget22 = require('phidget22');
var phidget = require('./scripts/phidgets');

//something here that lets you select run time opperation
//let runtime_function = phidget.runTest;
let runtime_function = phidget.runOSC;

var conn = new phidget22.Connection(5661, 'localhost');
conn.connect().then(runtime_function);
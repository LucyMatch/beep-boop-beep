var phidget22 = require('phidget22');
var phidget = require('./scripts/phidgets');

var conn = new phidget22.Connection(5661, 'localhost');
conn.connect().then(phidget.runTest);
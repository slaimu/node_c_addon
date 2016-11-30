var bindings = require('bindings')
var addon = bindings('pass_argument')

console.log(addon.length(process.argv[2]));

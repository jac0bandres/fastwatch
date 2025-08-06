const fastwatch = require('../build/Release/fastwatch.node')
const { exec } = require('child_process')

console.log("hi")

function watch(event, path) {
    console.log(event, path)
    if (event == "modify") {
        exec(`node ${__filename}`);
    }
}

// oh yeah

fastwatch.start("./", watch)
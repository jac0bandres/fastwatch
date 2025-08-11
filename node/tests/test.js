const fastwatch = require('../build/Release/fastwatch.node')

const enums = fastwatch.EventType
console.log(enums)

function watch(path, event) {
    console.log(path, event)
    if (event == fastwatch.EventType.CREATE) {
        console.log("new file")
    }
}

fastwatch.watch("./", watch)
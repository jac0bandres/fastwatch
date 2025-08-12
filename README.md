# fastwatch

A high-performance, cross-platform file system watcher written in C++ with Node.js bindings.

## Features

- Efficient recursive watching on Linux (using inotify)
- Planned support for macOS and Windows
- Native Node.js addon with async callbacks via N-API
- Easy to extend with other language bindings (Python, Go, etc.)

## Usage (Node.js)

```js
const fastwatch = require('../build/Release/fastwatch.node')

function watch(path, event) {
    console.log(path, event)
    if (event == fastwatch.EventType.CREATE) {
        console.log("new file")
    }
}

fastwatch.watch("./", watch)
watcher.stop();
```
## Event-driven
`fastwatch.EventType` contains C++ enum mappings to common file events, translated to JavaScript objects and cross-platform support.
File watching is event-driven using native APIs, with no polling or additional overhead.

## Building
### CMAKE
Run cmake from the build directory to build the C++ source. 
### Node Addon
run `node-gyp configure build` in the `/node` directory to build node addon. It compiles the source relative to it's path so don't change the `/node` location relative to `/build` unless you plan on editing `binding.gyp`.
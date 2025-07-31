i# fastwatch

A high-performance, cross-platform file system watcher written in C++ with Node.js bindings.

## Features

- Efficient recursive watching on Linux (using inotify)
- Planned support for macOS and Windows
- Native Node.js addon with async callbacks via N-API
- Easy to extend with other language bindings (Python, Go, etc.)

## Usage (Node.js)

```js
const fastwatch = require('./build/Release/fastwatch');

const watcher = new fastwatch.FastWatch('/path/to/watch', true);

watcher.start((path, event) => {
  console.log(`File ${event}: ${path}`);
});

// Stop watcher when done
// watcher.stop();

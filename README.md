![GitHub](https://img.shields.io/github/license/jnyfah/Shortest-Route)
[![Build status](https://ci.appveyor.com/api/projects/status/aw2kfy9o59mfjkij?svg=true)](https://ci.appveyor.com/project/jnyfah/shortest-route)
# Shortest-Route

This repository includes code for implementing a Dijkstra's algorithm in c++ to be used in modern web development with the help of webassembly. The program uses auto complete to allow users select input from available cities, it displays the shortest distance between the two selected cities with paths to follow.

To test it out [visit this web page](https://jnyfah.github.io/Shortest-Route/)

PS: I am not soo good with frontend :sweat: :sweat: 
![Alt text](/web/image.png?raw=true)

## Dependencies

- ### CMake :
  [CMake](https://cmake.org/) is a cross-platform open-source meta-build system which can build, test and package software. It can be used to support multiple native build environments including make, Apple's xcode and Microsoft Visual Studio

#### why would you want to use a build system ??

1. Cross platform portability
2. Dependency management
3. Continuos Integration

- ### Webassembly :
[WebAssembly](https://webassembly.org/) also known as WASM (web assembly state machine) is not just a programming language or instruction set, it is also a compilation target for other languages to compile to, as well as a language in itself. 
WASM is augmentation of the abilities of JS by allowing other languages to operate in the browser, it executes binary code in the browser.

For instance, you have a C++ or Rust code running on terminal and you want to show i off to your friends, webasembly can help you do that seamlessly, You write code in other languages, compile them into WebAssembly and ship o the web!. Rust, C/C++, Go, C#; these are just a few of the languages with WebAssembly as a compile target.

#### How it Works

High level languages like C, C++ and Rust are compiled into binary format .wasm and text format .wat using a compiler. Later, the .wasm code can be used with the help of javascript in your html file to display the output.
![alt text](https://www.tutorialspoint.com/webassembly/images/wasm.jpg)

#### Why WASM
Using WebAssembly means using the right tool for the job. For instance, who wants to write a banking app in JS?. If you're running anything that relies on mathematical numerical accuracy or speed that meant, until now, another AJAX call to have another language do alllllllll the math. With WebAssembly, we can do this in the browser, with, say Rust.

## Getting Started

To compile our C/C++ code to WebAssembly, we need a toolchain. This tool will be responsible for translating the code into WebAssembly format. To do that, we will install the [Emscripten](https://emscripten.org/index.html) toolchain. It is an open-source project that can compile any portable C/C++ code into WebAssembly. 

Emscripten has already been added to this repository as a submodule.

```cmd
git clone --recursive https://github.com/jnyfah/Shortest-Route
cd emsdk
./emsdk install latest
./emsdk activate latest
```
With the tools installed, you will also want to set the some environment variables. Add variables to PATH:

```bash
emsdk_env.bat             (windows)

source ./emsdk_env.sh      (unix)
```
The updates that this makes to environment variables isn't persistent; it will need to be run again with the next reboot.

## Compiling

To compile the code: 

```bash
cd ..
emcmake cmake 
emcc --bind -o index.js src/Dijkstra.cpp --std=c++1z --preload-file utils || exit 1
```

This would generate an `index.js`, `index.wasm` and `index.data` files in the root folder

## Serving

If you try to open the HTML file directly, your code probably will not run. Instead, the page will have to be served through an HTTP server
Install the package `http-server` for the node application to be able to serve the html file:

```bash
emrun --port 8080 index.html
```

Now, open the browser and access `http://localhost:8080`


rm build/ -rf
mkdir build
cd build
emcc --bind -o index.js ../src/Dijkstra.cpp --std=c++1z --preload-file ../utils || exit 1
mv index.js ../web/
mv index.wasm ../web/
mv index.data ../web/


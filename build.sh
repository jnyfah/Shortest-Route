emcmake cmake  
make
emcc --bind -o index.js src/Dijkstra.cpp --std=c++1z --preload-file utils || exit 1
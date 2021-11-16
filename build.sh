rm build/ -rf
mkdir build
cd build
em++ ../src/Dijkstra.cpp -g -std=c++1z -s WASM=1 -s EXCEPTION_CATCHING_ALLOWED=[..] -o index.js || exit 1
mv index.js ../web/gen/
mv index.wasm ../web/gen/
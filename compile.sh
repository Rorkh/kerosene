mkdir -p bin

g++ src/main.cpp src/misc/utils.cpp -lX11 -lXtst -lstdc++fs -std=c++17 -o bin/kerosene
g++ src/configure.cpp src/misc/utils.cpp -lX11 -lXtst -lstdc++fs -std=c++17 -o bin/configure

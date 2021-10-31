mkdir -p bin

g++ kerosene/main.cpp src/misc/utils.cpp -lX11 -lXtst -lstdc++fs -std=c++17 -o bin/kerosene
g++ kerosene-configure/main.cpp src/misc/utils.cpp -o bin/configure
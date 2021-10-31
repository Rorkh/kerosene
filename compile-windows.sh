mkdir -p bin

g++ src/main.cpp src/misc/utils.cpp -std=c++17 -o bin/kerosene.exe
g++ src/configure.cpp src/misc/utils.cpp -std=c++17 -o bin/configure.exe
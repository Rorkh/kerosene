mkdir -p bin

g++ -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread src/main.cpp src/misc/utils.cpp -std=c++17 -o bin/kerosene.exe
g++ -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread src/configure.cpp src/misc/utils.cpp -std=c++17 -o bin/configure.exe
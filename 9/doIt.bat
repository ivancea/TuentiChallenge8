del main.exe

g++.exe -fexceptions -mno-ms-bitfields -O3 -std=c++17 -DSFML_STATIC -IC:\includes\SFML-2.3.2\include -c Image.cpp -o Image.o
g++.exe -fexceptions -mno-ms-bitfields -O3 -std=c++17 -DSFML_STATIC -IC:\includes\SFML-2.3.2\include -c main.cpp -o main.o
g++.exe -LC:\includes\SFML-2.3.2\lib -LC:\includes\SFML-2.3.2\extlib -o main.exe Image.o main.o  -s -static -lsfml-audio-s -lsfml-graphics-s -lsfml-network-s -lsfml-window-s -lsfml-system-s -lOpenGL32 -lgdi32 -lwinmm -ljpeg

del Image.o
del main.o

main.exe

pause
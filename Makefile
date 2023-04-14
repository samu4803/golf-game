all:
	g++ -Isrc/Include -Lsrc/lib -Isrc/res -mwindows -o main main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image 
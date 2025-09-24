SDL_PATH := lib\SDL2-2.0.12\x86_64-w64-mingw32

SRC_FILES := src\main.c src\display.c src\vector.c src\mesh.c
INCLUDES := -I$(SDL_PATH)\include
LDLIBS := -lmingw32 -L$(SDL_PATH)\lib -lSDL2main -lSDL2

build:
	gcc -Wall -std=c99 $(SRC_FILES) $(INCLUDES) $(LDLIBS) -o renderer

run:
	.\renderer

clean:
	del .\renderer.exes
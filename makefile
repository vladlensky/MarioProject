FILES=src/main.c src/GameState.c src/MainState.c src/JeuState.c src/Mario.c
LIBSW=-lSDLmain -lSDL -lSDL_image
LIBSU=-lSDLmain -lSDL -lSDL_image
OPTS=-Wall -Wextra -ansi -pedantic -iquoteinclude
OUTPUT=SMB

all:
	gcc $(OPTS) $(FILES)  $(LIBSW) -o $(OUTPUT)

unix:
	gcc $(OPTS) $(FILES) $(LIBSU) -o $(OUTPUT)

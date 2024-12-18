
gcc main.c game.c graph.c save.c  sdl_helper/audio_functions.c sdl_helper/constants.c function.c sdl_helper/text_functions.c -o main.out -lSDL2main -lSDL2_mixer -lSDL2_ttf -lSDL2 -lcjson -lm
echo "Compilated gros bozo"
./main.out


#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define FPS 60

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern int window_width;
extern int window_height;
extern char* name;



#define MAX_AUDIO_CHANNELS 8


extern SDL_Color textColor;
extern TTF_Font* comfortaaFont_16;
extern TTF_Font* comfortaaFont_18;
extern TTF_Font* comfortaaFont_24;
extern TTF_Font* comfortaaFont_28;
extern TTF_Font* comfortaaFont_36;
extern TTF_Font* comfortaaFont_52;
void constantsLoadFont();

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

void textInitializeTtfLibrary();

void textChangeFontSize(int fontSize);

void textChangeColor(int colorR, int colorG, int colorB, int colorAlpha);

void textDrawText(char* textToDraw, int destinationX, int destinationY, TTF_Font* font);


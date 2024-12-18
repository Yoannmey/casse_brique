#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

void audioInitializeMixer();

void audioLoadAndPlay(char* file, int channel);

void audioSimpleLoadAndPlay(char* file);

void audioCleanup();


#pragma once

#include <stdlib.h>
#include <SDL2/SDL.h>

#ifndef SDL_GAME_H
#define SDL_GAME_H

void moove();

void rebond();

void moovePaddle();

void initTab();

void collision();

void brickBomb();

void dropPoint();

void randBrick();

void streakCount();

void reset();

void varLvl();

void brickEnd();

void pointSave();

void soundReset();

void game();

#endif

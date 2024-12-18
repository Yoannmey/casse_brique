#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "constants.h"
#include "text_functions.h"


// Initialize text library
void textInitializeTtfLibrary() {
    if (TTF_Init() == -1) {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        SDL_Quit();
    }
}


// Change the text color
void textChangeColor(int colorR, int colorG, int colorB, int colorAlpha) {
    textColor.r = colorR;
    textColor.g = colorG;
    textColor.b = colorB;
    textColor.a = colorAlpha;
}


// Displays a custom text on the screen
void textDrawText(char* textToDraw, int destinationX, int destinationY, TTF_Font* font) {

    // Check if the given font exists
    if (font == NULL) {
        printf("Error: No font for function drawText (font == NULL)");
    }

    // Creates a surface with the text
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, textToDraw, textColor);
    if (textSurface == NULL) {
        printf("TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        /*
        TTF_CloseFont(gameFont);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        */
    }

    // Creates a texture from the text
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (textTexture == NULL) {
    printf("Error: failed to create texture from surface. SDL Error: %s\n", SDL_GetError());
    }

    // Set the destinantion to be a rectagne with the width and height of the texture
    int textureWidth = 0;
    int textureHeight = 0;
    SDL_QueryTexture(textTexture, NULL, NULL, &textureWidth, &textureHeight);
    SDL_Rect destinationRect = {destinationX, destinationY, textureWidth, textureHeight};

    // Copy to renderer and free memory used by textTexture
    SDL_RenderCopy(renderer, textTexture, NULL, &destinationRect);
    SDL_DestroyTexture(textTexture);
}


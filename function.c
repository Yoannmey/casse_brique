#include "function.h"
#include "game.h"
#include "sdl_helper/constants.h"
#include "sdl_helper/audio_functions.h"
#include "sdl_helper/text_functions.h"

#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

extern int count;  // Compteur caractère
extern int menu;  // Variable gestion des menus
extern int menuCount;  // Variable de gestion du menuStart
extern int launch;  // Variable gestion lancement balle
extern float vX, vY; // X vitesse
extern int text;  // Variable gestion du texte
extern char scan[50];  // Chaine username
extern char scanSave[1]; // Chaine affichage caractère par caractère
extern int start;  // Variable gestion démarrage d'une partie
extern int pauseMenu; // Variable gestion menu pause
extern int over; // Variable affichage menu game over
extern int nextLvl; // Variable affichage menu fin de niveau
extern int lvl;  // Gestion du niveau
extern int brickCount; // Variable compte de briques
extern int x; // PosX de la balle
extern int rect; // Compteur de frame


void out(){
    printf("Vous dessinez en dehors de la fenetre\n");
}

/*void checkPos(int x, int y){
    /** @brief verifie que x et y sont bien dans l'ecran initialisé
     *  @param x position à verifier
     *  @param y position à verifier
     
    if (x < 0) {
        printf("ATTENTION position x < 0 (x = %d)\n", x);
        out();
    }
    if (x > window_width) {
        printf("ATTENTION position x > largeur de la fenetre (x = %d > %d)\n", x, window_width);
        out();
    }
    if (y < 0) {
        printf("ATTENTION position y < 0 (y = %d)\n", x);
        printf("ATTENTION position y > hauteur de la fenetre (y = %d > %d)\n", y, window_height);
        out();
    }
    if (y > window_height) {
        printf("ATTENTION position y > hauteur de la fenetre (y = %d > %d)\n", y, window_height);
        out();
    }
}*/


void init(int windowWidth, int windowHeight) {
    /** @brief initialise la fenêtre window et le renderer (moteur de rendu) renderer
     *  @param windowWidth la largeur de la fenêtre
     *  @param windowHeight la hauteur de la fenêtre
     */
    window_width = windowWidth;
    window_height = windowHeight;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("ERREUR : Init SDL > %s\nParametres passes %d , %d\n",SDL_GetError(), windowWidth, windowHeight);
        freeAndTerminate();
    }
    if (SDL_CreateWindowAndRenderer(windowWidth, windowHeight, 0, &window, &renderer)) {
        SDL_Log("ERREUR : Init window and renderer > %s\nParametres passes %d , %d\n",SDL_GetError(), windowWidth, windowHeight);
        freeAndTerminate();
    }
    SDL_SetWindowTitle(window, "Brick Breaker");
    SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);


    textInitializeTtfLibrary();
    constantsLoadFont();
    audioInitializeMixer();
}

void freeWindow() {
    /** @brief libère la mémoire allouée à la fenêtre
     */
    if (window) SDL_DestroyWindow(window);
}

void freeRenderer() {
    /** @brief libère la mémoire allouée au renderer
     */
    if (renderer) SDL_DestroyRenderer(renderer);
}

void freeTexture(SDL_Texture *texture) {
    /** @brief libère la mémoire allouée à la texture (utilisée pour dans la fonction sprite() pour afficher une image)
     *  @param texture la texture utilisée pour afficher l'image
     */
    if (texture) SDL_DestroyTexture(texture);
}

void freeAndTerminate() {
    /** @brief libère la mémoire allouée au programme(renderer et fenêtre) puis quitte la SDL et le programme
     */
    freeRenderer();
    freeWindow();
    audioCleanup();
    SDL_Quit();
    exit(EXIT_SUCCESS);
}


void actualize() {
    /** @brief actualise le renderer (i.e affiche ce qu'on a dessiné / fait dessus)
     */
    SDL_RenderPresent(renderer);
}

void changeColor(int r, int g, int b) {
    /** @brief change la couleur avec laquelle on dessine sur le renderer en celle du code RGB
     *  @param r Rouge dans le code RGB de la couleur choisi, entre 0 et 255
     *  @param g Vert dans le code RGB de la couleur choisi, entre 0 et 255
     *  @param b Bleu dans le code RGB de la couleur choisi, entre 0 et 255
     */
    if (SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE)) {
        SDL_Log("ERREUR : changement de couleur > %s\nParametres passes %d , %d, %d\n",SDL_GetError(), r, g, b);
        freeAndTerminate();
    }
}

void clear() {
    /** @brief réinitialise le fenêtre et reset la couleur
     *         (i.e supprime ce qu'on a dessiné dessus pour avoir une fenêtre noire)
     */
    changeColor(0, 0, 0);
    SDL_RenderClear(renderer);
    changeColor(255, 255, 255);
}

void drawSquare(int posX, int posY, int longueur) {
    /** @brief dessine un carré
     *  @param posX position sur l'axe horizontale du coin supérieur gauche du carré
     *  @param posY position sur l'axe verticale du coin supérieur gauche du carré
     *  @param longueur longeur du coté du carré
     */

    SDL_Rect rectangle;
    rectangle.x = posX;
    rectangle.y = posY;
    rectangle.w = longueur;
    rectangle.h = longueur;

    if (SDL_RenderFillRect(renderer, &rectangle)) {
        SDL_Log("ERREUR : Impossible de creer le carre > %s\nParametres passes %d , %d, %d\n",SDL_GetError(), posX, posY, longueur);
        freeAndTerminate();
    }
}

void drawRect(int posX, int posY, int longueur, int hauteur) {
    /** @brief dessine un rectangle
     *  @param posX position sur l'axe horizontale du coin supérieur gauche du rectangle
     *  @param posY position sur l'axe verticale du coin supérieur gauche du rectangle
     *  @param longueur longeur du coté du rectangle
     *  @param hauteur hauteur du coté du carré
     */

    SDL_Rect rectangle;
    rectangle.x = posX;
    rectangle.y = posY;
    rectangle.w = longueur;
    rectangle.h = hauteur;

    if (SDL_RenderFillRect(renderer, &rectangle)) {
        SDL_Log("ERREUR : Impossible de creer le rectangle > %s\nParametres passes %d , %d, %d, %d\n",SDL_GetError(), posX, posY, longueur, hauteur);
        freeAndTerminate();
    }
}

void drawCircle(int centerX, int centerY, int rayon) {
    /** @brief dessine un cercle de centre (x,y) et de rayon r sur le renderer
     *         (utilise l'équation d'un cercle x^2 + y^2 <= a^2)
     *  @param centerX position sur l'axe horizontal du centre
     *  @param centerY position sur l'axe vertical du centre
     *  @param rayon le rayon du cercle
     */

    for (int i = centerX - rayon; i <= centerX + rayon; i++) {
        for(int j = centerY - rayon; j <= centerY +rayon; j++) {
            int x = i - centerX;
            int y = j - centerY;
            if (x * x + y * y <= rayon * rayon) {
                SDL_RenderDrawPoint(renderer, i, j);
            }
        }
    }
}

void drawPoint(int x, int  y) {
    /** @brief dessine un point à la position (x,y) i.e change la couleur du pixel
     *  @param x position sur l'axe horizontal du point
     *  @param y position sur l'axe vertical du point
     */
    SDL_RenderDrawPoint(renderer, x, y);
}

void drawLine(int x1, int y1, int x2, int y2) {
    /** @brief trace une ligne entre le point 1 : (x1,y1) et 2 : (x2,y2)
     *  @param x1 position sur l'axe horizontal du point 1
     *  @param y1 position sur l'axe vertical du point 1
     *  @param x2 position sur l'axe horizontal du point 2
     *  @param y2 position sur l'axe vertical du point 2
     */
    if (SDL_RenderDrawLine( renderer, x1, y1, x2, y2)) {
        SDL_Log("ERREUR : drawLine() > %s\nParametres passes %d , %d, %d, %d\n",SDL_GetError(), x1, y1, x2, y2);
        freeAndTerminate();
    }
}

void drawLinePoints(Point point1, Point point2) {
    /** @brief même fonction que drawLine() mais avec des structure (voir struct Point)
     *  @param point1 Point d'origine de la ligne
     *  @param point2 Point d'arrivée de la ligne
     */
    if (SDL_RenderDrawLine( renderer, point1.x, point1.y, point2.x, point2.y)) {
        SDL_Log("ERREUR : drawLinePoints() > %s\nParametres passes (%d,%d), (%d,%d)\n",SDL_GetError(), point1.x, point1.y, point2.x, point2.y);
        freeAndTerminate();
    }
}

void sprite(int posX, int posY, char *imgBMPSrc) {
    /** @brief affiche un image .bmp sur le renderer
     *  @param posX position sur l'axe horizontale du coin supérieur gauche de l'image
     *  @param posY position sur l'axe verticale du coin supérieur gauche de l'image
     *  @param imgBMPSrc le chemin vers l'image que l'on veut afficher
     */

    SDL_Texture *textureImg = NULL;
    SDL_Surface *surfaceImg = NULL;
    if (!(surfaceImg = SDL_LoadBMP(imgBMPSrc))) {
        SDL_Log("ERREUR : chargement img > %s\nParametres passes %d , %d, %s\n",SDL_GetError(), posX, posY, imgBMPSrc);
        freeAndTerminate();
    }
    textureImg = SDL_CreateTextureFromSurface(renderer, surfaceImg);
    SDL_FreeSurface(surfaceImg);
    if (textureImg == NULL) {
        SDL_Log("ERREUR : chargement texture > %s\nParametres passes %d , %d, %s\n",SDL_GetError(), posX, posY, imgBMPSrc);
        freeTexture(textureImg);
        freeAndTerminate();
    }

    SDL_Rect rectangle;
    if (SDL_QueryTexture(textureImg, NULL, NULL, &rectangle.w, &rectangle.h)) {
        SDL_Log("ERREUR : image : query texture > %s\nParametres passes %d , %d, %s\n",SDL_GetError(), posX, posY, imgBMPSrc);
        freeTexture(textureImg);
        freeAndTerminate();
    }
    rectangle.x = posX;
    rectangle.y = posY;
    if (SDL_RenderCopy(renderer, textureImg, NULL, &rectangle) != 0) {
        SDL_Log("ERREUR: image : RenderCopy > %s\nParametres passes %d , %d, %s\n",SDL_GetError(), posX, posY, imgBMPSrc);
        freeTexture(textureImg);
        freeAndTerminate();
    }
    freeTexture(textureImg);
}

void lastKeyPressed(SDL_Event *event) {
    /** @brief affiche dans le terminal le caractère associé à la dernière touche appuyée
     *         ne fonctionne que si le type de l'event est SDL_KEYDOWN
     *         la gestion d'évènement se fait avec SDL_PollEvent(&event)
     *  @param event l'evenement qui s'est produit
     */
    if (event->type == SDL_KEYDOWN) {
        printf("Last Key Pressed: %c\n", event->key.keysym.sym);
    }
}
void KeyPressed(SDL_Keycode touche){
    /** @brief event.key.keysym.sym renvoi la touche appuyé
     *
     */
    switch (touche) {
        // Voir doc SDL_Keycode pour plus de touches https://wiki.libsdl.org/SDL_Keycode
        // ici exemple ou appuyer sur les touches Q | D modifie x (position du carré dans drawGame())
        case SDLK_BACKSPACE:
            if(menu==2){
                scan[count]=scanSave[0];
                if(count>0){
                    count--;
                }
            }
            break;
        case SDLK_0:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="0\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_KP_0:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="0\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_1:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="1\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_KP_1:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="1\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_2:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="2\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
            case SDLK_KP_2:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="2\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_3:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="3\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
            case SDLK_KP_3:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="3\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_4:
             if(menu==2){
                 audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="4\0";
                strcat(scan,scanTemp);
                count++;
                printf("prout\n");
            }
            break;
        case SDLK_KP_4:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="4\0";
                strcat(scan,scanTemp);
                count++;
                printf("bite\n");
            }
            break;
        case SDLK_5:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="5\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_KP_5:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="5\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_6:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="6\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_KP_6:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="6\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_7:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="7\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_KP_7:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="7\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_8:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="8\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_KP_8:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="8\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_9:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="9\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_KP_9:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="9\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_a:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="a\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_z:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="z\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_e:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="e\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_r:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="r\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_t:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="t\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_y:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="y\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_u:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="u\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_i:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="i\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_q:
            if(launch==0 && vX>-10){
                vX--;
            }
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="q\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_o:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="o\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_p:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="p\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_s:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="s\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_f:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="f\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_g:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="g\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_h:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="h\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_j:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="j\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_k:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="k\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_l:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="l\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_m:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="m\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_w:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="w\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_x:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="x\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_c:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="c\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_v:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="v\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_b:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="b\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_n:
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="n\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_d:
            if(launch==0 && vX<10){
                vX++;
            }
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]="d\0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_SPACE:
            if(launch==0 && start==1){
                launch++;
                if(vX>0){
                    switch(lvl){
                        case 1:
                            vX=vX+3;
                            vY=vY-3;
                            break;
                        case 2:
                            vX=vX+4;
                            vY=vY-4;
                            break;
                        case 3:
                            vX=vX+6;
                            vY=vY-6;
                            break;
                    }
                }
                if(vX<0){
                    switch(lvl){
                        case 1:
                            vX=vX-3;
                            vY=vY-3;
                            break;
                        case 2:
                            vX=vX-4;
                            vY=vY-4;
                            break;
                        case 3:
                            vX=vX-6;
                            vY=vY-6;
                            break;
                    }
                }
            }
            if(menu==2){
                audioLoadAndPlay("sound/key.wav",1);
                char scanTemp[50]=" \0";
                strcat(scan,scanTemp);
                count++;
            }
            break;
        case SDLK_RETURN:
            if(menuCount==0){
                soundReset();
                menuCount++;
            }
            if(menu<3){
                menu++;
                text=0;
            }
            if(start==1){
                nextLvl=1;
                rect=0;
            }
            break;
        case SDLK_ESCAPE:
            if(start==1 && pauseMenu==0 && over==0 && nextLvl<2){
                pauseMenu++;
            }
            if(start==0){
                freeAndTerminate();
            }
            break;
        default:
            break;
    }
}


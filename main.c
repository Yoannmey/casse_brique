#include <SDL2/SDL.h>
#include <unistd.h>

#include "save.h"
#include "graph.h"
#include "game.h"
#include "function.h"
#include "sdl_helper/text_functions.h"
#include "sdl_helper/audio_functions.h"
#include "sdl_helper/constants.h"


extern float mooveX, mooveY; // Position paddle
extern int brickX, brickY; // Postion brique
extern int launch; // Variable gestion lancement balle
extern int compteurPoint; // Variable de sauvegarde du nombre de points
extern int sizePaddle; // Variable taille paddle
extern int menu;  // Variable gestion des menus
extern int text; // Variable gestion du texte
extern int menuCount; // Variable de gestion du menuStart
extern int rect; // Variable de compte des frames
extern int theme; // Variable gestion du theme
extern int pauseMenu;  // Variable gestion menu pause
extern int vXsave, vYsave;  // Variable sauvegarde vX et vY
extern int yMoove; // Variable gestion mouvement bonus
extern int over;  // Variable affichage menu game over
extern int nextLvl;  // Variable affichage menu fin de niveau
extern int lvl;  // Gestion du niveau
extern int savePoint;  // Variable sauvegarde des points
extern int menuL;  // Variable affichage du menu des niveaux

float x = 940; // PosX balle
float y = 855; // PosY balle
float vX = 0; // X vitesse
float vY = -5; // Y vitesse
float vMoove =10; // Vitesse paddle
int start=0; // Variable gestion démarrage d'une partie
int count=0;  // Compteur caractère
char scan[50];  // Chaine username
char scanSave[1]; // Chaine affichage caractère par caractère
int theme1=0; // Variable gestion indicateur de bouton
int theme2=0; // Variable gestion indicateur de bouton
int theme3=0; // Variable gestion indicateur de bouton
int theme4=0; // Variable gestion indicateur de bouton
int score=0; // Variable gestion affichage du tableau des scores
int scoreBack=0; // Variable gestion retour au menu
int pauseTheme1=0; // Variable gestion indicateur de bouton
int pauseTheme2=0; // Variable gestion indicateur de bouton
int programLaunched2 = 0; // Variable gestion menuLoop


void init_game(){

// Initialisation des variables et du tableau des briques

    initTab();
    initSave();
    char scan[50]=" ";
    char scanSave[0]="";
    char scanTemp[50]="";
    if(menuCount==0){
        audioLoadAndPlay("sound/revolte.wav",1);
    }
}

void drawMenu(){

// Fonction appellée dans la boucle affichage des menus

    if(menu==0){ // Menu animé
        menuStart();
    }
    if(menu>0 && menu<4){ // Menu d'introduction et de saisie du nom de joueur
        menuTheme();
        actualize();
        usleep(1000000/ FPS);
    }
    if(menu==4){ // Menu de choix de thème
        actualize();
        usleep(1000000/ FPS);
        pickTheme();
    }
    if(theme>0){ // Menu du jeu
        gameMenu();
        actualize();
        usleep(1000000/ FPS);
    }
    frameCount();

}
void drawGame(){

// Fonction appelée dans la boucle d'affichage du jeu

    clear();
    graph();
    game();
    printf("|%d|\n",rect);
    frameCount();
    actualize();
    usleep(1000000 / FPS); // 60 images par seconde | 1000000 = 1
}

void menuLoop(){ // Boucle des menus
    programLaunched2 = 1;
    while (programLaunched2 == 1) {
        // Boucle pour garder le programme ouvert
        // lorsque programLaunched est different de 1
        // on sort de la boucle, donc de la fonction
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // boucle pour la gestion d'évenement
            switch (event.type) {
                /** event.type renvoi le type d'evenement qui se passe
                 * (si on appuie sur une touche, clique de souris...)
                 * en fonction du type d'évènement on à alors
                 * différentes information accessibles
                 * voir doc pour plus d'event https://wiki.libsdl.org/SDL_EventType
                 */
                case SDL_QUIT:
                    // quand on clique sur fermer la fénêtre en haut à droite
                    programLaunched2 = 0;
                    break;
                case SDL_MOUSEBUTTONUP:
                    /* clique de la souris
                     * event.motion.y | event.motion.x pour les positions de la souris
                     */
                    printf("position de la souris x : %d , y : %d\n", event.motion.x, event.motion.y);
                    if(menu==4){ // Menu choix theme
                        if(event.motion.x>380 && event.motion.x<640 && event.motion.y>625 && event.motion.y<880){
                            //steampunk
                            theme=1;
                            menu++;
                            theme1=0;
                            theme2=0;
                            theme3=0;
                            theme4=0;
                            variableTheme();
                            audioLoadAndPlay("sound/menuClick.wav",1);
                        }
                        if(event.motion.x>830 && event.motion.x<1090 && event.motion.y>625 && event.motion.y<880){
                            //arcade
                            theme=2;
                            menu++;
                            theme1=0;
                            theme2=0;
                            theme3=0;
                            theme4=0;
                            variableTheme();
                            audioLoadAndPlay("sound/menuClick.wav",1);
                        }
                        if(event.motion.x>1260 && event.motion.x<1550 && event.motion.y>625 && event.motion.y<880){
                            //Classique
                            theme=3;
                            menu++;
                            theme1=0;
                            theme2=0;
                            theme3=0;
                            theme4=0;
                            variableTheme();
                            audioLoadAndPlay("sound/menuClick.wav",1);
                        }
                    }
                    if(theme==1){ // Menu Steampunk
                        if(event.motion.x<250 && event.motion.x>125 && event.motion.y<300 && event.motion.y>250){

                            // Début de partie

                            start++;
                            yMoove=2;
                            programLaunched2=2;
                            audioLoadAndPlay("sound/menuClick.wav",1);
                            soundReset();
                        }
                        else if(event.motion.x<280 && event.motion.x>125 && event.motion.y<390 && event.motion.y>330){

                            // Accés menu des niveaux

                            menuL++;
                            audioLoadAndPlay("sound/menuClick.wav",1);
                        }
                        else  if(event.motion.x<300 && event.motion.x>125 && event.motion.y<475 && event.motion.y>420){

                            // Accés au tableau des scores

                            score++;
                            audioLoadAndPlay("sound/menuClick.wav",1);
                        }
                        else  if(event.motion.x<250 && event.motion.x>125 && event.motion.y<565 && event.motion.y>505){

                            // Fermeture du jeu

                            audioLoadAndPlay("sound/menuClick.wav",1);
                            freeAndTerminate();
                        }
                        if(score>0){

                            // Retour du tableau des scores

                            if(event.motion.x<240 && event.motion.x>80 && event.motion.y<135 && event.motion.y>70){
                                score=0;
                                audioLoadAndPlay("sound/menuClick.wav",1);
                            }
                        }
                    }
                    if(theme==2){ // Menu Arcade
                        if(event.motion.x<330 && event.motion.x>115 && event.motion.y<300 && event.motion.y>250){

                            // Début de partie

                            programLaunched2=2;
                            start++;
                            yMoove=2;
                            audioLoadAndPlay("sound/menuClick.wav",1);
                            soundReset();
                        }
                        else if(event.motion.x<360 && event.motion.x>115 && event.motion.y<390 && event.motion.y>340){

                            // Accés menu des niveaux

                            menuL++;
                            audioLoadAndPlay("sound/menuClick.wav",1);
                        }
                        else  if(event.motion.x<375 && event.motion.x>115 && event.motion.y<480 && event.motion.y>430){

                            // Accés tableau des scores

                            score++;
                            audioLoadAndPlay("sound/menuClick.wav",1);
                        }
                        else  if(event.motion.x<320 && event.motion.x>115 && event.motion.y<565 && event.motion.y>520){

                            // Fermeture du jeu

                            audioLoadAndPlay("sound/menuClick.wav",1);
                            freeAndTerminate();
                        }
                        if(score>=0){

                            // Retour du tableau des scores

                            if(event.motion.x<240 && event.motion.x>80 && event.motion.y<135 && event.motion.y>70){
                            score=0;
                            audioLoadAndPlay("sound/menuClick.wav",1);
                            }
                        }
                    }
                    if(theme==3){ // Menu Classique
                        if(event.motion.x<260 && event.motion.x>115 && event.motion.y<300 && event.motion.y>240){

                            //Début de partie

                            programLaunched2=2;
                            start++;
                            yMoove=2;
                            audioLoadAndPlay("sound/menuClick.wav",1);
                            soundReset();
                        }
                        else if(event.motion.x<290 && event.motion.x>115 && event.motion.y<385 && event.motion.y>330){

                            //Accés menu des niveaux

                            menuL++;
                            audioLoadAndPlay("sound/menuClick.wav",1);
                        }
                        else  if(event.motion.x<310 && event.motion.x>115 && event.motion.y<475 && event.motion.y>410){

                            // Accés tableau des scores

                            score++;
                            audioLoadAndPlay("sound/menuClick.wav",1);
                        }
                        else  if(event.motion.x<250 && event.motion.x>115 && event.motion.y<560 && event.motion.y>500){

                            // Fermeture du jeu

                            audioLoadAndPlay("sound/menuClick.wav",1);
                            freeAndTerminate();
                        }
                        if(score>0){

                            // Retour du tableau des scores

                            if(event.motion.x<240 && event.motion.x>80 && event.motion.y<135 && event.motion.y>70){
                            score=0;
                            audioLoadAndPlay("sound/menuClick.wav",1);
                            }
                        }
                    }
                    if(menuL==1){
                        switch(theme){
                            case 1: // Steampunk
                                if(event.motion.x<1140 && event.motion.x>780 && event.motion.y<275 && event.motion.y>175){

                                    // Début du premier niveau

                                    lvl=1;
                                    initTab();
                                    start=1;
                                    yMoove=2;
                                    audioLoadAndPlay("sound/menuClick.wav",1);
                                    programLaunched2=2;
                                    soundReset();
                                }
                                else if(event.motion.x<1140 && event.motion.x>780 && event.motion.y<520 && event.motion.y>330){

                                    // Début du deuxième niveau

                                    lvl=2;
                                    initTab();
                                    start=1;
                                    yMoove=2;
                                    audioLoadAndPlay("sound/menuClick.wav",1);
                                    programLaunched2=2;
                                    soundReset();
                                }
                                else  if(event.motion.x<1140 && event.motion.x>780 && event.motion.y<770 && event.motion.y>675){

                                    // Début du troisième niveau

                                    lvl=3;
                                    initTab();
                                    start=1;
                                    yMoove=2;
                                    audioLoadAndPlay("sound/menuClick.wav",1);
                                    programLaunched2=2;
                                    soundReset();
                                }
                                else  if(event.motion.x<270 && event.motion.x>130 && event.motion.y<165 && event.motion.y>115){

                                    // Retour du menu des niveaux

                                    menuL=0;
                                    audioLoadAndPlay("sound/menuClick.wav",1);
                                }
                                break;
                            case 2: // Arcade
                                if(event.motion.x<1250 && event.motion.x>680 && event.motion.y<280 && event.motion.y>195){

                                    // Début du premier niveau

                                    lvl=1;
                                    initTab();
                                    start=1;
                                    yMoove=2;
                                    audioLoadAndPlay("sound/menuClick.wav",1);
                                    programLaunched2=2;
                                    soundReset();
                                }
                                else if(event.motion.x<1250 && event.motion.x>680 && event.motion.y<530 && event.motion.y>445){

                                    // Début du deuxième niveau

                                    lvl=2;
                                    initTab();
                                    start=1;
                                    yMoove=2;
                                    audioLoadAndPlay("sound/menuClick.wav",1);
                                    programLaunched2=2;
                                    soundReset();
                                }
                                else  if(event.motion.x<1250 && event.motion.x>680 && event.motion.y<775 && event.motion.y>695){

                                    // Début du troisième niveau
                                    lvl=3;
                                    initTab();
                                    start=1;
                                    yMoove=2;
                                    audioLoadAndPlay("sound/menuClick.wav",1);
                                    programLaunched2=2;
                                    soundReset();
                                }
                                else  if(event.motion.x<290 && event.motion.x>105 && event.motion.y<170 && event.motion.y>120){

                                    // Retour du menu des niveaux

                                    menuL=0;
                                    audioLoadAndPlay("sound/menuClick.wav",1);
                                }
                                break;
                            case 3: // Classique
                                if(event.motion.x<1170 && event.motion.x>760 && event.motion.y<270 && event.motion.y>175){

                                    // Début du premier niveau

                                    lvl=1;
                                    initTab();
                                    start=1;
                                    yMoove=2;
                                    audioLoadAndPlay("sound/menuClick.wav",1);
                                    programLaunched2=2;
                                    soundReset();
                                }
                                else if(event.motion.x<1170 && event.motion.x>760 && event.motion.y<515 && event.motion.y>415){

                                    // Début du deuxième niveau

                                    lvl=2;
                                    initTab();
                                    start=1;
                                    yMoove=2;
                                    audioLoadAndPlay("sound/menuClick.wav",1);
                                    programLaunched2=2;
                                    soundReset();
                                }
                                else  if(event.motion.x<1170 && event.motion.x>760 && event.motion.y<760 && event.motion.y>670){

                                    // Début du troisième niveau

                                    lvl=3;
                                    initTab();
                                    start=1;
                                    yMoove=2;
                                    audioLoadAndPlay("sound/menuClick.wav",1);
                                    programLaunched2=2;
                                    soundReset();
                                }
                                else  if(event.motion.x<290 && event.motion.x>110 && event.motion.y<165 && event.motion.y>115){

                                    // Retour du menu des niveaux
                                    lvl=1;
                                    audioLoadAndPlay("sound/menuClick.wav",1);
                                }
                                break;
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    KeyPressed(event.key.keysym.sym);
                    break;
                case SDL_KEYUP:
                    break;
                case SDL_MOUSEMOTION:
                    if(menu==4){ // Menu choix theme
                        if(event.motion.x>380 && event.motion.x<640 && event.motion.y>625 && event.motion.y<880){

                            // Steampunk

                            theme1++;
                        }
                        else if(event.motion.x>830 && event.motion.x<1090 && event.motion.y>625 && event.motion.y<880){

                            // Arcade

                            theme2++;
                        }
                        else  if(event.motion.x>1260 && event.motion.x<1550 && event.motion.y>625 && event.motion.y<880){

                            // Classique

                            theme3++;
                        }
                        else{

                            // Reset de la variable des boutons

                            theme1=0;
                            theme2=0;
                            theme3=0;
                        }
                    }
                    if(theme==1){ // Menu Steampunk
                        if(event.motion.x<250 && event.motion.x>125 && event.motion.y<300 && event.motion.y>250){
                            theme1++;
                        }
                        else if(event.motion.x<280 && event.motion.x>125 && event.motion.y<390 && event.motion.y>330){
                            theme2++;
                        }
                        else  if(event.motion.x<300 && event.motion.x>125 && event.motion.y<475 && event.motion.y>420){
                            theme3++;
                        }
                        else  if(event.motion.x<250 && event.motion.x>125 && event.motion.y<565 && event.motion.y>505){
                            theme4++;
                        }
                        else{
                            theme1=0;
                            theme2=0;
                            theme3=0;
                            theme4=0;
                        }
                        if(score>0){
                            if(event.motion.x<240 && event.motion.x>80 && event.motion.y<135 && event.motion.y>70){
                            scoreBack++;
                            }
                            else{
                                scoreBack=0;
                            }
                        }
                    }
                    if(theme==2){ // Menu Arcade
                        if(event.motion.x<330 && event.motion.x>115 && event.motion.y<300 && event.motion.y>250){
                            theme1++;
                        }
                        else if(event.motion.x<360 && event.motion.x>115 && event.motion.y<390 && event.motion.y>340){
                            theme2++;
                        }
                        else  if(event.motion.x<375 && event.motion.x>115 && event.motion.y<480 && event.motion.y>430){
                            theme3++;
                        }
                        else  if(event.motion.x<320 && event.motion.x>115 && event.motion.y<565 && event.motion.y>520){
                            theme4++;
                        }
                        else{
                            theme1=0;
                            theme2=0;
                            theme3=0;
                            theme4=0;
                        }
                        if(score>0){
                            if(event.motion.x<240 && event.motion.x>80 && event.motion.y<135 && event.motion.y>70){
                            scoreBack++;
                            }
                            else{
                                scoreBack=0;
                            }
                        }
                    }
                    if(theme==3){ // Menu Classique
                        if(event.motion.x<260 && event.motion.x>115 && event.motion.y<300 && event.motion.y>240){
                            theme1++;
                        }
                        else if(event.motion.x<290 && event.motion.x>115 && event.motion.y<385 && event.motion.y>330){
                            theme2++;
                        }
                        else  if(event.motion.x<310 && event.motion.x>115 && event.motion.y<475 && event.motion.y>410){
                            theme3++;
                        }
                        else  if(event.motion.x<250 && event.motion.x>115 && event.motion.y<560 && event.motion.y>500){
                            theme4++;
                        }
                        else{
                            theme1=0;
                            theme2=0;
                            theme3=0;
                            theme4=0;
                        }
                        if(score>0){
                            if(event.motion.x<240 && event.motion.x>80 && event.motion.y<135 && event.motion.y>70){
                            scoreBack++;
                            }
                            else{
                                scoreBack=0;
                            }
                        }
                    }
                    if(menuL==1){
                        switch(theme){
                            case 1:
                                if(event.motion.x<1140 && event.motion.x>780 && event.motion.y<275 && event.motion.y>175){
                                    theme1++;
                                }
                                else if(event.motion.x<1140 && event.motion.x>780 && event.motion.y<520 && event.motion.y>330){
                                    theme2++;
                                }
                                else  if(event.motion.x<1140 && event.motion.x>780 && event.motion.y<770 && event.motion.y>675){
                                    theme3++;
                                }
                                else  if(event.motion.x<270 && event.motion.x>130 && event.motion.y<165 && event.motion.y>115){
                                    theme4++;// refaire x
                                }
                                else{
                                    theme1=0;
                                    theme2=0;
                                    theme3=0;
                                    theme4=0;
                                }
                                break;
                            case 2:
                                if(event.motion.x<1250 && event.motion.x>680 && event.motion.y<280 && event.motion.y>195){
                                    theme1++;
                                }
                                else if(event.motion.x<1250 && event.motion.x>680 && event.motion.y<530 && event.motion.y>445){
                                    theme2++;
                                }
                                else  if(event.motion.x<1250 && event.motion.x>680 && event.motion.y<775 && event.motion.y>695){
                                    theme3++;
                                }
                                else  if(event.motion.x<290 && event.motion.x>105 && event.motion.y<170 && event.motion.y>120){
                                    theme4++;
                                }
                                else{
                                    theme1=0;
                                    theme2=0;
                                    theme3=0;
                                    theme4=0;
                                }
                                break;
                            case 3:
                                if(event.motion.x<1170 && event.motion.x>760 && event.motion.y<270 && event.motion.y>175){
                                    theme1++;
                                }
                                else if(event.motion.x<1170 && event.motion.x>760 && event.motion.y<515 && event.motion.y>415){
                                    theme2++;
                                }
                                else  if(event.motion.x<1170 && event.motion.x>760 && event.motion.y<760 && event.motion.y>670){
                                    theme3++;
                                }
                                else  if(event.motion.x<290 && event.motion.x>110 && event.motion.y<165 && event.motion.y>115){
                                    theme4++;
                                }
                                else{
                                    theme1=0;
                                    theme2=0;
                                    theme3=0;
                                    theme4=0;
                                }
                                break;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        /* coder ici pour que le code s'execute après chaque évenement
         * exemple dessiner un carré avec position int x, int y qu'on peut
         * deplacer lorsqu'on appuie sur une touche
         */
            drawMenu();

    }
}

void gameLoop() { // Boucle du jeu
    int programLaunched = 1;
    while (programLaunched == 1) {
        // Boucle pour garder le programme ouvert
        // lorsque programLaunched est different de 1
        // on sort de la boucle, donc de la fonction
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // boucle pour la gestion d'évenement
            switch (event.type) {
                /** event.type renvoi le type d'evenement qui se passe
                 * (si on appuie sur une touche, clique de souris...)
                 * en fonction du type d'évènement on à alors
                 * différentes information accessibles
                 * voir doc pour plus d'event https://wiki.libsdl.org/SDL_EventType
                 */
                case SDL_QUIT:
                    // quand on clique sur fermer la fénêtre en haut à droite
                    programLaunched = 0;
                    break;
                case SDL_MOUSEBUTTONUP:
                    /* clique de la souris
                     * event.motion.y | event.motion.x pour les positions de la souris
                     */
                    printf("position de la souris x : %d , y : %d\n", event.motion.x, event.motion.y);
                    if(pauseMenu>0){
                        if(theme==1){ // Menu pause Steampunk
                            if(event.motion.x<1070 && event.motion.x>835 && event.motion.y<455 && event.motion.y>415){

                                // Retour au menu

                                reset();
                                savePoint=0;
                                lvl=1;
                                audioLoadAndPlay("sound/menuClick.wav",1);
                                menuLoop();
                            }
                            else if(event.motion.x<1015 && event.motion.x>885 && event.motion.y<535 && event.motion.y>500){

                                // Reprise de la partie

                                vX=vXsave;
                                vY=vYsave;
                                yMoove=2;
                                pauseMenu=0;
                                audioLoadAndPlay("sound/menuClick.wav",1);
                            }
                        }
                        if(theme==2){  // Menu pause Arcade
                            if(event.motion.x<1125 && event.motion.x>775 && event.motion.y<460 && event.motion.y>420){

                                // Retour au menu

                                reset();
                                lvl=1;
                                savePoint=0;
                                audioLoadAndPlay("sound/menuClick.wav",1);
                                menuLoop();
                            }
                            else if(event.motion.x<1050 && event.motion.x>850 && event.motion.y<520 && event.motion.y>490){

                                // Reprise de la partie

                                vX=vXsave;
                                vY=vYsave;
                                yMoove=2;
                                pauseMenu=0;
                                audioLoadAndPlay("sound/menuClick.wav",1);
                            }
                        }
                        if(theme==3){  // Menu pause Classique
                            if(event.motion.x<1090 && event.motion.x>815 && event.motion.y<450 && event.motion.y>415){

                                // Retour au menu

                                reset();
                                lvl=1;
                                savePoint=0;
                                audioLoadAndPlay("sound/menuClick.wav",1);
                                menuLoop();
                            }
                            else if(event.motion.x<1035 && event.motion.x>875 && event.motion.y<510 && event.motion.y>475){

                                // Reprise de la partie

                                vX=vXsave;
                                vY=vYsave;
                                yMoove=2;
                                pauseMenu=0;
                                audioLoadAndPlay("sound/menuClick.wav",1);
                            }
                        }
                    }
                    if(over==1){ // Menu de game over
                        if(theme==1){ // Steampunk
                            if(event.motion.x<910 && event.motion.x>850 && event.motion.y<540 && event.motion.y>515){

                                // Retour au menu

                                reset();
                                lvl=1;
                                savePoint=0;
                                audioLoadAndPlay("sound/menuClick.wav",1);
                                menuLoop();
                            }
                            else if(event.motion.x<1085 && event.motion.x>980 && event.motion.y<540 && event.motion.y>515){

                                // Nouvelle partie

                                reset();
                                savePoint=0;
                                start++;
                                audioLoadAndPlay("sound/menuClick.wav",1);
                            }
                        }
                        if(theme==2){ // Arcade
                            if(event.motion.x<920 && event.motion.x>835 && event.motion.y<540 && event.motion.y>515){

                                // Retour au menu

                                reset();
                                lvl=1;
                                savePoint=0;
                                menuLoop();
                                audioLoadAndPlay("sound/menuClick.wav",1);
                            }
                            else if(event.motion.x<1115 && event.motion.x>950 && event.motion.y<540 && event.motion.y>515){

                                // Nouvelle partie

                                reset();
                                savePoint=0;
                                start++;
                                audioLoadAndPlay("sound/menuClick.wav",1);
                            }
                        }
                        if(theme==3){ // Classique

                            if(event.motion.x<915 && event.motion.x>845 && event.motion.y<540 && event.motion.y>515){

                                // Retour au menu

                                reset();
                                lvl=1;
                                savePoint=0;
                                audioLoadAndPlay("sound/menuClick.wav",1);
                                menuLoop();
                            }
                            else if(event.motion.x<1090 && event.motion.x>970 && event.motion.y<540 && event.motion.y>515){

                                // Nouvelle partie

                                reset();
                                start++;
                                savePoint=0;
                                audioLoadAndPlay("sound/menuClick.wav",1);
                            }
                        }
                    }
                    if(nextLvl>1){// Menu niveau suivant
                        if(lvl==1 || lvl==2){ // Pour les niveaux 1 et 2
                            if(theme==1){ // Steampunk
                                if(event.motion.x<940 && event.motion.x>820 && event.motion.y<540 && event.motion.y>515){

                                    // Niveau suivant

                                    pointSave();
                                    reset();
                                    lvl++;
                                    start++;
                                    audioLoadAndPlay("sound/menuClick.wav",1);
                                    initTab();
                                }
                                else if(event.motion.x<1060 && event.motion.x>1000 && event.motion.y<540 && event.motion.y>515){

                                    // Retour au menu

                                    reset();
                                    savePoint=0;
                                    lvl=1;
                                    audioLoadAndPlay("sound/menuClick.wav",1);
                                    menuLoop();
                                }
                            }
                            if(theme==2){ // Arcade
                                if(event.motion.x<975 && event.motion.x>790 && event.motion.y<540 && event.motion.y>515){

                                    // Niveau suivant

                                    pointSave();
                                    reset();
                                    lvl++;
                                    start++;
                                    initTab();
                                    audioLoadAndPlay("sound/menuClick.wav",1);
                                }
                                else if(event.motion.x<1100 && event.motion.x>1010 && event.motion.y<540 && event.motion.y>515){

                                    // Retour au menu

                                    reset();
                                    savePoint=0;
                                    lvl=1;
                                    audioLoadAndPlay("sound/menuClick.wav",1);
                                    menuLoop();
                                }
                            }
                            if(theme==3){ // Classique
                                if(event.motion.x<945 && event.motion.x>815 && event.motion.y<540 && event.motion.y>515){

                                    // Niveau suivant

                                    pointSave();
                                    reset();
                                    lvl++;
                                    start++;
                                    initTab();
                                    audioLoadAndPlay("sound/menuClick.wav",1);
                                }
                                else if(event.motion.x<1065 && event.motion.x>995 && event.motion.y<540 && event.motion.y>515){

                                    // Retour au menu

                                    reset();
                                    savePoint=0;
                                    lvl=1;
                                    audioLoadAndPlay("sound/menuClick.wav",1);
                                    menuLoop();
                                }
                            }
                        }
                         if(lvl==3){ // Pour le troisième niveau
                            if(theme==1){ // Steampunk
                                if(event.motion.x<990 && event.motion.x>925 && event.motion.y<540 && event.motion.y>520){

                                    // Retour au menu

                                    pointSave();
                                    saveScore();
                                    savePoint=0;
                                    reset();
                                    lvl=1;
                                    audioLoadAndPlay("sound/menuClick.wav",1);
                                    menuLoop();
                                }
                            }
                            if(theme==2){ // Arcade
                                if(event.motion.x<995 && event.motion.x>910 && event.motion.y<540 && event.motion.y>520){

                                    // Retour au menu

                                    pointSave();
                                    saveScore();
                                    savePoint=0;
                                    reset();
                                    lvl=1;
                                    audioLoadAndPlay("sound/menuClick.wav",1);
                                    menuLoop();
                                }
                            }
                            if(theme==3){ // Classique
                                if(event.motion.x<990 && event.motion.x>915 && event.motion.y<540 && event.motion.y>520){

                                    // Retour au menu

                                    pointSave();
                                    saveScore();
                                    savePoint=0;
                                    reset();
                                    lvl=1;
                                    audioLoadAndPlay("sound/menuClick.wav",1);
                                    menuLoop();
                                }
                            }
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    KeyPressed(event.key.keysym.sym);
                    break;
                case SDL_KEYUP:
                    break;
                case SDL_MOUSEMOTION:
                    if(launch==1 && pauseMenu==0 && over==0 && nextLvl<2){
                        mooveX=event.motion.x;
                        if(mooveX>=1920-sizePaddle){
                            mooveX=1920-sizePaddle;
                        }
                    }
                    if(pauseMenu>0){
                        if(theme==1){  // Menu pause Steampunk
                            if(event.motion.x<1070 && event.motion.x>835 && event.motion.y<455 && event.motion.y>415){
                                pauseTheme1++;
                            }
                            else if(event.motion.x<1015 && event.motion.x>885 && event.motion.y<535 && event.motion.y>500){
                                pauseTheme2++;
                            }
                            else{
                                pauseTheme1=0;
                                pauseTheme2=0;
                            }
                        }
                        if(theme==2){  // Menu pause  Arcade
                            if(event.motion.x<1125 && event.motion.x>775 && event.motion.y<460 && event.motion.y>420){
                                pauseTheme1++;
                            }
                            else if(event.motion.x<1050 && event.motion.x>850 && event.motion.y<520 && event.motion.y>490){
                                pauseTheme2++;
                            }
                            else{
                                pauseTheme1=0;
                                pauseTheme2=0;
                            }
                        }
                        if(theme==3){  // Menu pause Classique
                            if(event.motion.x<1090 && event.motion.x>815 && event.motion.y<450 && event.motion.y>415){
                                pauseTheme1++;
                            }
                            else if(event.motion.x<1035 && event.motion.x>875 && event.motion.y<510 && event.motion.y>475){
                                pauseTheme2++;
                            }
                            else{
                                pauseTheme1=0;
                                pauseTheme2=0;
                            }
                        }
                    }
                    if(over==1){// Menu game over
                        if(theme==1){
                            if(event.motion.x<910 && event.motion.x>850 && event.motion.y<540 && event.motion.y>515){
                                pauseTheme1++;
                            }
                            else if(event.motion.x<1085 && event.motion.x>980 && event.motion.y<540 && event.motion.y>515){
                                pauseTheme2++;
                            }
                            else{
                                pauseTheme1=0;
                                pauseTheme2=0;
                            }
                        }
                        if(theme==2){
                            if(event.motion.x<920 && event.motion.x>835 && event.motion.y<540 && event.motion.y>515){
                                pauseTheme1++;
                            }
                            else if(event.motion.x<1115 && event.motion.x>950 && event.motion.y<540 && event.motion.y>515){
                                pauseTheme2++;
                            }
                            else{
                                pauseTheme1=0;
                                pauseTheme2=0;
                            }
                        }
                        if(theme==3){
                            if(event.motion.x<915 && event.motion.x>845 && event.motion.y<540 && event.motion.y>515){
                                pauseTheme1++;
                            }
                            else if(event.motion.x<1090 && event.motion.x>970 && event.motion.y<540 && event.motion.y>515){
                                pauseTheme2++;
                            }
                            else{
                                pauseTheme1=0;
                                pauseTheme2=0;
                            }
                        }
                    }
                    if(nextLvl>1){// Menu niveau suivant
                        if(lvl==1 || lvl==2){
                            if(theme==1){
                                if(event.motion.x<940 && event.motion.x>820 && event.motion.y<540 && event.motion.y>515){
                                    pauseTheme1++;
                                }
                                else if(event.motion.x<1060 && event.motion.x>1000 && event.motion.y<540 && event.motion.y>515){
                                    pauseTheme2++;
                                }
                                else{
                                    pauseTheme1=0;
                                    pauseTheme2=0;
                                }
                            }
                            if(theme==2){
                                if(event.motion.x<975 && event.motion.x>790 && event.motion.y<540 && event.motion.y>515){
                                    pauseTheme1++;
                                }
                                else if(event.motion.x<1100 && event.motion.x>1010 && event.motion.y<540 && event.motion.y>515){
                                    pauseTheme2++;
                                }
                                else{
                                    pauseTheme1=0;
                                    pauseTheme2=0;
                                }
                            }
                            if(theme==3){
                                if(event.motion.x<945 && event.motion.x>815 && event.motion.y<540 && event.motion.y>515){
                                    pauseTheme1++;
                                }
                                else if(event.motion.x<1065 && event.motion.x>995 && event.motion.y<540 && event.motion.y>515){
                                    pauseTheme2++;
                                }
                                else{
                                    pauseTheme1=0;
                                    pauseTheme2=0;
                                }
                            }
                        }
                        if(lvl==3){
                            if(theme==1){
                                if(event.motion.x<990 && event.motion.x>925 && event.motion.y<540 && event.motion.y>520){
                                    pauseTheme1++;
                                }
                                else{
                                    pauseTheme1=0;
                                }
                            }
                            if(theme==2){
                                if(event.motion.x<995 && event.motion.x>910 && event.motion.y<540 && event.motion.y>520){
                                    pauseTheme1++;
                                }
                                else{
                                    pauseTheme1=0;
                                }
                            }
                            if(theme==3){
                                if(event.motion.x<990 && event.motion.x>915 && event.motion.y<540 && event.motion.y>520){
                                    pauseTheme1++;
                                }
                                else{
                                    pauseTheme1=0;
                                }
                            }
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        /* coder ici pour que le code s'execute après chaque évenement
         * exemple dessiner un carré avec position int x, int y qu'on peut
         * deplacer lorsqu'on appuie sur une touche
         */
            drawGame();
    }
}

int main(){
    /** @description 3 fonctions dans le main qui permettent de créer l'application et la maintenir ouverte :
     *  init(...) : initialiser la SDL/ fenêtre
     *  gameLoop() : boucle de jeu dans laquelle l'application reste ouverte
     *  freeAndTerminate() : quitte le programme proprement
     */
    init(WINDOW_WIDTH, WINDOW_HEIGHT);
    init_game();
    menuLoop();
    gameLoop();
    printf("Fin du programme\n");
    freeAndTerminate();
}



#include "game.h"
#include "function.h"
#include "graph.h"
#include "save.h"
#include "sdl_helper/text_functions.h"
#include "sdl_helper/audio_functions.h"
#include "sdl_helper/constants.h"

#include <SDL2/SDL.h>
#include <unistd.h>
#include <time.h>

#define RAYON 15
#define BRICKLONG 100
#define BRICKHAUT 50

extern float vX,vY; // Vitesse balle
extern float x,y; // Position balle
extern Point tabPoint[500]; // Tableau gestion position des points
extern int nmbrPoint; // Variable gestion nombre de points
extern int sizePaddle; // Variable gestion taille paddle
extern int brickX, brickY; // Position brique
extern int start;  // Variable gestion démarrage d'une partie
extern int pauseMenu; // Variable gestion menu pause
extern int over;  // Variable affichage menu game over
extern int nextLvl; // Variable affichage menu fin de niveau
extern int bonusCount; // Compte des bonus
extern int resultScore; // Résultat du calcul des scores
extern int text, text2; // Gestion affichage des textes
extern int resetChar; // Variable de reset des chaines de caractères calcul des scores
extern int rect; // Variable compte frame
extern int sound; // Variable gestion de la musique du menu
extern int theme; // Variable gestion du theme
extern int bomb; // Variable de gestion de l'affichage du design des briques bombe
extern int rand1, rand2, rand3;  // Variable affichage des evenements aléatoires
extern int draw;  // Variable de gestion de changement de design pour les briques


float mooveX=885, mooveY=900; // Position paddle
int tabBrick[10][40]; // Tableau statut des briques
int colonne; // Gestion des colonnes du tableau tabBrick
int ligne; // Gestion des lignes du tableau tabBrick
int launch=0; // Variable gestion lancement balle
int compteurPoint; // Variable sauvegarde nombre points
int streakSave; // Variable sauvegarde streak
int streak; // Variable compte streak
int yMoove=2; // Variable gestion mouvement bonus
int life=3; // Variable nombre de vies
int gapX=0; // Variable écart brique X
int gapY=0;  // Variable écart brique Y
int largX=0; // Variable écart brique écran X
int largY=0; // Variable écart brique écran Y
int brickCount=0; // Variable compte de briques
int lvl=1;  // Gestion du niveau
int savePoint=0; // Variable sauvegarde des points
int randEvent=0; // Gestion des events random
int saveX1=0, saveX2=0, saveX3=0, saveX4=0, saveX5=0; // Sauvegarde des postions X des briques
int saveY1=0, saveY2=0, saveY3=0, saveY4=0, saveY5=0; // Sauvegarde des postions Y des briques
int jBomb; // Colonnes de briques
int iBomb; // Lignes de briques

void moove(){

// Mouvement de la balle par itération de la boucle gameLoop

    if(launch==1){
      x=x+vX;
      y=y+vY;
    }

// Mouvement des bonus

    for(int i=0;i<300;i++){
      tabPoint[i].y= tabPoint[i].y+yMoove;
    }

}

void rebond(){
    
// Gestion des rebonds sur les murs

    if(((x<=20 && vX<0) || (x>=1900 && vX>0)) && y<1080){
      vX=vX*-1;
      audioLoadAndPlay("sound/paddle.wav",1);
    }

    if(y<=10){
      vY=vY*-1;
      audioLoadAndPlay("sound/paddle.wav",1);
    }

// Gestion des rebonds sur le paddle

    if(y+RAYON>=mooveY-RAYON-5 && y+RAYON<=mooveY){
      if((x+RAYON>=mooveX) && (x+RAYON<=mooveX+(sizePaddle/2)) && vY>0){
        streakSave=streak;
        streak=0;
        if(vX>0){
          vX=vX*-1;
        }
        vY=vY*1,4;
        vY=vY*-1;
        audioLoadAndPlay("sound/paddle.wav",1);
      }

      else if((x+RAYON>=mooveX+(sizePaddle/2)) && (x+RAYON<=mooveX+sizePaddle) && vY>0){
        streakSave=streak;
        streak=0;
        if(vX<0){
          vX=vX*-1;
        }
        vY=vY*-1;
        audioLoadAndPlay("sound/paddle.wav",1);
      }

    }

// Gestion des contact de la balle et des bonus sur le paddle et sur le bas de l'écran

    if(y>=925 && y<1000){

      if(life>0){
        audioLoadAndPlay("sound/life.wav",1);
      }

      if(life>=1){
        life--;
        launch=0;
        vX=0;
        vY=-5;
        x=940;
        y=855;
        mooveX=885;
        for(int i=0;i<300;i++){
          if(tabPoint[i].y<930){
            tabPoint[i].y+=1000;
            bonusCount--;
          }
        }
      }

      else{
        audioLoadAndPlay("sound/gameOver.wav",1);
        over=1;
        y=1200;
        for(int i=0;i<300;i++){
          if(tabPoint[i].y<930){
            tabPoint[i].y+=1000;
            bonusCount--;
          }
        }
      }

    }

    for(int i=0;i<300;i++){
      if(tabPoint[i].y+25>mooveY && tabPoint[i].y<mooveY+10 && tabPoint[i].x+20>=mooveX && tabPoint[i].x<=mooveX+sizePaddle){
        compteurPoint++;
        bonusCount--;
        tabPoint[i].y+=1000;
        audioLoadAndPlay("sound/bonus.wav",1);
      }
    }

    for(int i=0;i<300;i++){
       if(tabPoint[i].y+20>=930 && tabPoint[i].y+20<=990){
         bonusCount--;
         tabPoint[i].y+=1000;
      }
    }

}

void initTab(){

//Initialisation du tableau de position des briques

  varLvl();
  srand(time(NULL));
  for(int i=0;i<ligne;i++){
    for(int j=0;j<colonne;j++){
      if(rand()%10==0 && lvl>1){
        tabBrick[i][j]=2;
      }
      else if(rand()%10==0 && lvl>2){
        tabBrick[i][j]=3;
      }
      else{
      tabBrick[i][j]=1;
      }
      printf("|%d|",tabBrick[i][j]);
    }
    printf("\n");
  }

//Initialisation du tableau de position des points

  for(int i=0;i<300;i++){
      tabPoint[i].x=1950;
      tabPoint[i].y=1000;
  }
}

void collision(){

//Gestion des collisions

  for(int i=0;i<ligne;i++){
    for(int j=0;j<colonne;j++){
      brickX=(j*(BRICKLONG+gapX))+largX;
      brickY=(i*(BRICKHAUT+gapY))+largY;
        //Droite brique
      if(tabBrick[i][j]==1 || tabBrick[i][j]==2 || tabBrick[i][j]==3){
        if((y+RAYON>=brickY) && (y+RAYON<=brickY+BRICKHAUT) && (x+RAYON<=brickX+BRICKLONG+RAYON) && (x+RAYON>=brickX+RAYON) && (vX<0)){
          vX=vX*-1;
          if(tabBrick[i][j]==1){
          tabBrick[i][j]=0;
          }
          if(tabBrick[i][j]==2){
            jBomb=j;
            iBomb=i;
            brickBomb();
          }
          if(tabBrick[i][j]==3){
            tabBrick[i][j]=0;
            randBrick();
          }
          dropPoint();
          streak++;
          audioLoadAndPlay("sound/brick.wav",1);
          printf("Collision:|%d|%d|\n",brickX, brickY);
        }
        //Gauche brique
        else if((y+RAYON>=brickY) && (y+RAYON<=brickY+BRICKHAUT) && (x+RAYON>=brickX-RAYON) && (x+RAYON<=brickX-RAYON+BRICKLONG) && (vX>0)){
          vX=vX*-1;
          if(tabBrick[i][j]==1){
            tabBrick[i][j]=0;
          }
          if(tabBrick[i][j]==2){
            jBomb=j;
            iBomb=i;
            brickBomb();
          }
          if(tabBrick[i][j]==3){
            tabBrick[i][j]=0;
            randBrick();
          }
          dropPoint();
          streak++;
          printf("Collision:|%d|%d|\n",brickX, brickY);
        }
        //Bas brique
        else if((x+RAYON>=brickX) && (x+RAYON<=brickX+BRICKLONG) && (y+RAYON<=brickY+BRICKHAUT+RAYON) && (y+RAYON>=brickY+RAYON) && (vY<0)){
          vY=vY*-1;
          if(tabBrick[i][j]==1){
            tabBrick[i][j]=0;
          }
          if(tabBrick[i][j]==2){
            jBomb=j;
            iBomb=i;
            brickBomb();
          }
          if(tabBrick[i][j]==3){
            tabBrick[i][j]=0;
            randBrick();
          }
          dropPoint();
          streak++;
          audioLoadAndPlay("sound/brick.wav",1);
          printf("Collision:|%d|%d|\n",brickX, brickY);
        }
        //Haut brique
       else if((x+RAYON>=brickX) && (x+RAYON<=brickX+BRICKLONG) && (y+RAYON>=brickY-RAYON) && (y+RAYON<=brickY-RAYON+BRICKHAUT) && (vY>0)){
          vY=vY*-1;
          if(tabBrick[i][j]==1){
            tabBrick[i][j]=0;
          }
          if(tabBrick[i][j]==2){
            jBomb=j;
            iBomb=i;
            brickBomb();
          }
          if(tabBrick[i][j]==3){
            tabBrick[i][j]=0;
            randBrick();
          }
          dropPoint();
          streak++;
          audioLoadAndPlay("sound/brick.wav",1);
          printf("Collision:|%d|%d|\n",brickX, brickY);
        }
      }
    }
  }
}


void brickBomb(){

//Gestion des briques qui explosent

      if(tabBrick[iBomb][jBomb]==2){
        tabBrick[iBomb][jBomb]=0;
        dropPoint();
        saveX1=brickX;
        saveY1=brickY;
        if(tabBrick[iBomb-1][jBomb]==1 || tabBrick[iBomb-1][jBomb]==3){
          tabBrick[iBomb-1][jBomb]=0;
          brickX=saveX1;
          brickY=saveY1-gapY-BRICKHAUT;
          dropPoint();
          saveX2=brickX;
          saveY2=brickY;
          if(tabBrick[iBomb-1][jBomb]==3){
            randBrick();
          }
        }

        if(tabBrick[iBomb+1][jBomb]==1 || tabBrick[iBomb+1][jBomb]==3){
          tabBrick[iBomb+1][jBomb]=0;
          brickX=saveX1;
          brickY=saveY1+gapY+BRICKHAUT;
          dropPoint();
          saveX3=brickX;
          saveY3=brickY;
          if(tabBrick[iBomb+1][jBomb]==3){
            randBrick();
          }
        }

        if(tabBrick[iBomb][jBomb+1]==1 || tabBrick[iBomb][jBomb+1]==3){
          tabBrick[iBomb][jBomb+1]=0;
          brickX=saveX1+gapX+BRICKLONG;
          brickY=saveY1;
          dropPoint();
          saveX4=brickX;
          saveY4=brickY;
          if(tabBrick[iBomb][jBomb+1]==3){
            randBrick();
          }
        }

        if(tabBrick[iBomb][jBomb-1]==1 || tabBrick[iBomb][jBomb-1]==3){
          tabBrick[iBomb][jBomb-1]=0;
          brickX=saveX1-gapX-BRICKLONG;
          brickY=saveY1;
          dropPoint();
          saveX5=brickX;
          saveY5=brickY;
          if(tabBrick[iBomb][jBomb-1]==3){
            randBrick();
          }
        }
  }
  rect=0;
  bomb=1;
  draw++;
}

void dropPoint(){

//Gestion de position des points

    bonusCount++;
    tabPoint[nmbrPoint].x=brickX+30;
    tabPoint[nmbrPoint].y=brickY+5;
    nmbrPoint++;

}

void randBrick(){

//Rand des event des briques mystères

  randEvent=rand()%3;
  draw++;

  switch(randEvent){
    case 0:
      sizePaddle+=50;
      rect=0;
      rand1=1;
      break;
    case 1:
      if(sizePaddle>50){
        sizePaddle-=50;
        rect=0;
        rand2=1;
      }
      else{
        randEvent=2;
      }
      break;
    case 2:
      rect=0;
      rand3=1;
      if(vX<0 && vY<0){
        vX=vX-2;
        vY=vY-2;
      }
      else if(vX<0 && vY>0){
        vX=vX-2;
        vY=vY+2;
      }
      else if(vX>0 && vY>0){
        vX=vX+2;
        vY=vY+2;
      }
      else if(vX>0 && vY<0){
        vX=vX+2;
        vY=vY-2;
      }
        break;
  }
}

void streakCount(){

// Fonction qui transforme les streaks en points

  if(streakSave>1 && streakSave<6){
    compteurPoint=compteurPoint+(streakSave*2);
    streakSave=0;
  }
  else if(streakSave>5 && streakSave<11){
    compteurPoint=compteurPoint+(streakSave*3);
    streakSave=0;
  }
  else if(streakSave>10){
    compteurPoint=compteurPoint+(streakSave*4);
    streakSave=0;
  }

}

void reset(){

// Reset des variables en fin ou abandon de partie

  start=0;
  mooveX=885;
  mooveY=900;
  launch=0;
  x = 940;
  y = 855;
  vX = 0;
  vY = -5;
  nmbrPoint=0;
  sizePaddle=150;
  pauseMenu=0;
  life=3;
  compteurPoint=0;
  over=0;
  bonusCount=0;
  brickCount=0;
  nextLvl=0;
  resultScore=0;
  text=0;
  text2=0;
  resetChar=1;
  streak=0;
  sound=0;
  initTab();

}

void varLvl(){

// Changement des variables en fonction du niveau

  if(lvl==1){
    gapX=40;
    gapY=10;
    largX=320;
    largY=90;
    colonne=10;//10
    ligne=3;//3
  }
  if(lvl==2){
    gapX=110;
    gapY=10;
    largX=175;
    largY=90;
    colonne=8;//8
    ligne=7;//7
  }
  if(lvl==3){
    gapX=4;
    gapY=4;
    largX=130;
    largY=90;
    colonne=16;//16
    ligne=6;//6
  }
}

void brickEnd(){

 // Compteur de briques fin de niveau

  if(brickCount==0 && nextLvl==0){
      nextLvl=2;
      rect=0;
  }
}

void pointSave(){

//Sauvegarde des points pour le tableau des scores

  savePoint=savePoint+compteurPoint+(50*life);
}

void soundReset(){

// Reset des channels de piste audio

  audioCleanup();
  audioInitializeMixer();

}

void game(){

// Appel des fonctions pour le drawGame

    streakCount(); // Compte des streaks
    launchBall(); // Lancement de la balle
    moove(); // Déplacement de la balle
    rebond(); // Rebond de la balle sur la raquette et les bords
    collision(); // Collisions sur les briques
    varLvl(); // Changement des variables en fonction du niveau
    brickEnd(); // Compteur de briques fin de niveau
}


#include "graph.h"
#include "function.h"
#include "save.h"
#include "sdl_helper/audio_functions.h"
#include "sdl_helper/constants.h"
#include "sdl_helper/text_functions.h"

#include <SDL2/SDL.h>
#include <unistd.h>
#include <string.h>

#define FPS 60
#define BRICKLONG 100
#define BRICKHAUT 50

extern float x,y; // Position balle
extern float mooveX, mooveY; // Postion brique
extern int tabBrick[10][40]; // Tableau statut des briques
extern int launch; // Variable gestion lancement balle
extern float vX, vY; // Vitesse balle
extern int colonne;  // Gestion des colonnes du tableau tabBrick
extern int ligne; // Gestion des lignes du tableau tabBrick
extern int menuCount; // Variable gestion affichage du menuStart
extern int compteurPoint; // Variable sauvegarde nombre points
extern char scan[50]; // Chaine username
extern char scanTemp[]; // Chaine temporaire "_"
extern char scanSave[1]; // Chaine affichage caractère par caractère
extern int count; // Compteur caractère
extern int theme1, theme2, theme3, theme4, score, scoreBack, pauseTheme1, pauseTheme2;// Variable gestion indicateur de bouton
extern int yMoove; // Variable gestion mouvement bonus
extern int life; // Variable nombre de vies
extern int streak; // Variable compte streak
extern int gapX; // Variable écart brique X
extern int gapY; // Variable écart brique Y
extern int largX;  // Variable écart brique écran X
extern int largY; // Variable écart brique écran Y
extern int lvl; // Gestion du niveau
extern int brickCount;  // Variable compte de briques
extern int savePoint; // Variable sauvegarde des points
extern int programLaunched2;  // Variable gestion menuLoop
extern int saveX1, saveX2, saveX3, saveX4, saveX5; // Sauvegarde des postions X des briques
extern int saveY1, saveY2, saveY3, saveY4, saveY5; // Sauvegarde des postions Y des briques


int brickX, brickY; // Position brique
double xLaunch, yLaunch; // Position ligne de lancement
Point tabPoint[500]; // Tableau gestion position des points
int nmbrPoint=0; // Variable gestion nombre de points
int sizePaddle=150; // Variable gestion taille paddle
int menu=0; // Variable gestion des menus
int text=0; // Variable gestion du texte
int rect=0; // Variable compte frame
char temp[1]="_";  //Chaine temporaire "_"
int menuCount=0; // Variable de gestion du menuStart
int theme=0; // Variable gestion du theme
int pauseMenu=0; // Variable gestion menu pause
int vXsave=0; // Variable sauvegarde vX
int vYsave=0; // Variable sauvegarde vY
int xSprite=0; // PosX sprite animés sur les menus
int ySprite=0; // PosY sprite animés sur les menus
int xSprite2=0;  // PosX sprite animés sur les menus
int ySprite2=0; // PosY sprite animés sur les menus
int over=0; // Variable affichage menu game over
int nextLvl=0; // Variable affichage menu fin de niveau
int bonusCount=0; // Compte des bonus
int resultScore; // Résultat du calcul des scores
int text2; // Gestion affichage du texte de calcul des scores
int confettisX=0; // PoxX sprite confettis
int confettisY1=-1080; // PoxY sprite confettis
int confettisY2=-2160; // PoxY sprite confettis
int resetChar=0; // Variable de reset des chaines de caractères calcul des scores
int menuL=0; // Variable affichage du menu des niveaux
int sound=0; // Variable gestion de la musique du menu
int bomb=0; // Variable de gestion de l'affichage du design des briques bombe
int rand1=0, rand2=0, rand3=0; // Variable affichage des evenements aléatoires
int draw=0; // Variable de gestion de changement de design pour les briques

char chaineScore[50]="Points calculation...\0"; // Chaine de caractère de calcul des niveaux
char saveChaine[50]=""; // Chaine de sauvegarde de calcul des niveaux
char saveChaine2[100]="";  // Chaine de sauvegarde de calcul des niveaux


void raquette(){

//Draw paddle

  if(theme==1){
    changeColor(115,86,80);
  }
  if(theme==2){
    changeColor(223,116,186);
  }
  if(theme==3){
    changeColor(196,39,39);
  }
  drawRect(mooveX, mooveY, sizePaddle, 10);

}

void graphisme(){

//Draw background

  if(theme==1){
    sprite(0,0,"img/menuSteampunk/backSteampunk.bmp");
    changeColor(255, 145, 77);
    drawRect(0,930,1920,10);
    drawRect(1150,930,10,200);
    if(nextLvl<2){
      drawRect(670,930,10,200);
    }
  }
  if(theme==2){
    sprite(0,0,"img/menuArcade/backArcade.bmp");
    changeColor(148,80,249);
    drawRect(0,930,1920,10);
    drawRect(1150,930,10,200);
    if(nextLvl<2){
      drawRect(670,930,10,200);
    }
  }

  if(theme==3){
    sprite(0,0,"img/menuClassique/backClassique.bmp");
    changeColor(123,71,33);
    drawRect(0,930,1920,10);
    drawRect(1150,930,10,200);
    if(nextLvl<2){
      drawRect(670,930,10,200);
    }
  }


}

void drawBall(){

// Affichae de la balle en fonction du thème

  if(theme==1){
    sprite(x,y,"img/menuSteampunk/ballSteampunk.bmp");
  }
  if(theme==2){
    sprite(x,y,"img/menuArcade/ballArcade.bmp");
  }
  if(theme==3){
    sprite(x,y,"img/menuClassique/ballClassique.bmp");
  }

}

void brickPrint(){

// Affichage des briques

brickCount=0;
  for(int i=0;i<ligne;i++){
    for(int j=0;j<colonne;j++){
      if(tabBrick[i][j]==1){
        brickX=(j*(BRICKLONG+gapX))+largX;
        brickY=(i*(BRICKHAUT+gapY))+largY;
        if(theme==1){
          sprite(brickX, brickY,"img/menuSteampunk/brickSteampunk.bmp");
          brickCount++;
        }
        if(theme==2){
          sprite(brickX, brickY,"img/menuArcade/brickArcade.bmp");
          brickCount++;
        }
        if(theme==3){
          sprite(brickX, brickY,"img/menuClassique/brickClassique.bmp");
          brickCount++;
        }
      }
      if(tabBrick[i][j]==2){
        brickX=(j*(BRICKLONG+gapX))+largX;
        brickY=(i*(BRICKHAUT+gapY))+largY;
        if(theme==1){
          sprite(brickX, brickY,"img/menuSteampunk/brickSteampunk.bmp");
          brickCount++;
        }
        if(theme==2){
          sprite(brickX, brickY,"img/menuArcade/brickArcade.bmp");
          brickCount++;
        }
        if(theme==3){
          sprite(brickX, brickY,"img/menuClassique/brickClassique.bmp");
          brickCount++;
        }
      }
      if(tabBrick[i][j]==3){
        brickX=(j*(BRICKLONG+gapX))+largX;
        brickY=(i*(BRICKHAUT+gapY))+largY;
        if(theme==1){
          sprite(brickX, brickY,"img/menuSteampunk/brickSteampunk.bmp");
          brickCount++;
        }
        if(theme==2){
          sprite(brickX, brickY,"img/menuArcade/brickArcade.bmp");
          brickCount++;
        }
        if(theme==3){
          sprite(brickX, brickY,"img/menuClassique/brickClassique.bmp");
          brickCount++;
        }
      }
    }
  }
}

void launchBall(){

//Draw ligne de lancement de la balle

  if(launch==0){
    yLaunch=y;
    xLaunch=x+20;
    for(int i=0;i<6;i++){
      yLaunch=yLaunch-12;
      xLaunch=xLaunch+(vX*2);
      if(theme==1){
        changeColor(115,86,80);
      }
      if(theme==2){
        changeColor(223,116,186);
      }
      if(theme==3){
        changeColor(196,39,39);
      }
      drawCircle(xLaunch,yLaunch,6-i);
    }
  }
}

void drawDropPoint(){

//Affichage des sprites des bonus

  for(int i=0;i<300;i++){
    if(theme==1){
      sprite(tabPoint[i].x,tabPoint[i].y,"img/menuSteampunk/bonusSteampunk.bmp");
    }
    if(theme==2){
      sprite(tabPoint[i].x,tabPoint[i].y,"img/menuArcade/bonusArcade.bmp");
    }
    if(theme==3){
      sprite(tabPoint[i].x,tabPoint[i].y,"img/menuClassique/bonusClassique.bmp");
    }
  }

}

void menuStart(){

// 1er menu (animé)

  if(menuCount==0){
    sprite(0,0,"img/menuStart/menuStart1.bmp");
    usleep(1500000 / FPS);
    actualize();
    sprite(0,0,"img/menuStart/menuStart2.bmp");
    usleep(1500000 / FPS);
    actualize();
    sprite(0,0,"img/menuStart/menuStart3.bmp");
    usleep(1500000 / FPS);
    actualize();
    sprite(0,0,"img/menuStart/menuStart4.bmp");
    usleep(1500000 / FPS);
    actualize();
    sprite(0,0,"img/menuStart/menuStart5.bmp");
    usleep(1500000 / FPS);
    actualize();
    sprite(0,0,"img/menuStart/menuStart6.bmp");
    usleep(1500000 / FPS);
    actualize();
    sprite(0,0,"img/menuStart/menuStart7.bmp");
    usleep(1500000 / FPS);
    actualize();
    sprite(0,0,"img/menuStart/menuStart8.bmp");
    usleep(1500000 / FPS);
    actualize();
    sprite(0,0,"img/menuStart/menuStart9.bmp");
    usleep(1500000 / FPS);
    actualize();
    sprite(0,0,"img/menuStart/menuStart10.bmp");
    usleep(1500000 / FPS);
    actualize();
    sprite(0,0,"img/menuStart/menuStart11.bmp");
    usleep(1500000 / FPS);
    actualize();
    sprite(0,0,"img/menuStart/menuStart12.bmp");
    usleep(1500000 / FPS);
    actualize();
    sprite(0,0,"img/menuStart/menuStart13.bmp");
    usleep(1500000 / FPS);
    actualize();
    sprite(0,0,"img/menuStart/menuStart14.bmp");
    usleep(1500000 / FPS);
    actualize();
    sprite(0,0,"img/menuStart/menuStart15.bmp");
    usleep(1500000 / FPS);
    actualize();
    sprite(0,0,"img/menuStart/menuStart16.bmp");
    usleep(1500000 / FPS);
    actualize();
    sprite(0,0,"img/menuStart/menuStart17.bmp");
    usleep(1500000 / FPS);
    actualize();
    sprite(0,0,"img/menuStart/menuStart18.bmp");
    usleep(1500000 / FPS);
    actualize();
    sprite(0,0,"img/menuStart/menuStart19.bmp");
    usleep(1500000 / FPS);
    actualize();
    sprite(0,0,"img/menuStart/menuStart20.bmp");
    usleep(1500000 / FPS);
    actualize();
    sprite(0,0,"img/menuStart/menuStart21.bmp");
    usleep(1500000 / FPS);
    actualize();
    sprite(0,0,"img/menuStart/menuStart22.bmp");
    usleep(1500000 / FPS);
    actualize();
    sprite(0,0,"img/menuStart/menuStart23.bmp");
    usleep(1500000 / FPS);
    actualize();
    sprite(0,0,"img/menuStart/menuStart24.bmp");
    usleep(1500000 / FPS);
    actualize();
    sprite(0,0,"img/menuStart/menuStart25.bmp");
  }
}

void compteurPoints(){

// Affichage du compteur des points pendant le jeu

  char compteur[300];
  sprintf(compteur,"%d", compteurPoint);
  if(theme==1 && nextLvl<2){
  textChangeColor(255, 145, 77,255);
  textDrawText("Points:", 90, 990,comfortaaFont_36);
  textDrawText(compteur , 230, 980,comfortaaFont_52);
  }
  if(theme==2 && nextLvl<2){
  textChangeColor(148,80,249,255);
  textDrawText("Points:", 90, 990,comfortaaFont_36);
  textDrawText(compteur , 230, 980,comfortaaFont_52);
  }
  if(theme==3 && nextLvl<2){
  textChangeColor(123,71,33,255);
  textDrawText("Points:", 90, 990,comfortaaFont_36);
  textDrawText(compteur , 230, 980,comfortaaFont_52);
  }

}

void menuTheme(){

// Affichage du menu de scan du nom du joueur

  char chaineTheme[23]="Welcome to BrickCrusher";
  char chaineTheme1[67]="This game is inspired by a very famous 2D game, the brick breaker\0";
  char chaineTheme2[53]="Please enter your username. Press RETURN to confirm\0";
  char chaineTheme3[23]="Please choose a theme\0";
  char saveChaine[23]=" ";
  char saveChaine1[67]=" ";
  char saveChaine2[53]=" ";
  char saveChaine3[23]=" ";

  if(menu==1){
    while(text<23){
        sprite(0,0,"img/menu/1.bmp");
        saveChaine[text]=chaineTheme[text];
        textChangeColor(255,255,255,255);
        textDrawText(saveChaine,390,245,comfortaaFont_28);
        text++;
        usleep(1000000/FPS);
        actualize();
    }
    text=0;
    while(text<67){
        sprite(0,0,"img/menu/1.bmp");
        saveChaine1[text]=chaineTheme1[text];
        textChangeColor(255,255,255,255);
        textDrawText(chaineTheme,390,245,comfortaaFont_28);
        textDrawText(saveChaine1,390,280,comfortaaFont_28);
        text++;
        usleep(1000000/FPS);
        actualize();
    }
    text=0;
    menu++;
  }
  if(menu==2){
      while(text<28){
        sprite(0,0,"img/menu/2.bmp");
        saveChaine2[text]=chaineTheme2[text];
        textChangeColor(255,255,255,255);
        textDrawText(saveChaine2,390,360,comfortaaFont_28);
        textDrawText(chaineTheme,390,245,comfortaaFont_28);
        textDrawText(chaineTheme1,390,280,comfortaaFont_28);
        text++;
        usleep(1000000/FPS);
        actualize();
      }
      scanRect();
  }

  if(menu==3){

    while(text<23){
      sprite(0,0,"img/menu/3.bmp");
      textChangeColor(255,255,255,255);
      textDrawText(chaineTheme2,390,360,comfortaaFont_28);
      textDrawText(chaineTheme1,390,280,comfortaaFont_28);
      textDrawText(chaineTheme,390,245,comfortaaFont_28);
      textChangeColor(0,0,0,255);
      textDrawText(scan,390,435,comfortaaFont_28);
      saveChaine3[text]=chaineTheme3[text];
      textChangeColor(255,255,255,255);
      textDrawText(saveChaine3,390,520,comfortaaFont_28);
      text++;
      usleep(1000000/FPS);
      actualize();
    }
    menu++;
    text=0;
  }
}

void scanRect(){

// Underscore qui clignote pour le scan du nom du joueur

  char chaineTheme[23]="Welcome to BrickCrusher";
  char chaineTheme1[67]="This game is inspired by a very famous 2D game, the brick breaker\0";
  char chaineTheme2[53]="Please enter your username. Press RETURN to confirm\0";

  sprite(0,0,"img/menu/2.bmp");
  textChangeColor(255,255,255,255);
  textDrawText(chaineTheme2,390,360,comfortaaFont_28);
  textDrawText(chaineTheme1,390,280,comfortaaFont_28);
  textDrawText(chaineTheme,390,245,comfortaaFont_28);

  if(rect==1 || rect==2 || rect==3 || rect==4 || rect==5 || rect==6){
    textChangeColor(0,0,0,255);
    textDrawText(strcat(scan,temp),390,435,comfortaaFont_28);
    scan[count]=scanSave[0];
  }
  else{
    textChangeColor(0,0,0,255);
    textDrawText(scan,390,435,comfortaaFont_28);
  }
}

void pickTheme(){

// Affichage du choix du thème

    char chaineTheme[23]="Welcome to BrickCrusher";
    char chaineTheme1[67]="This game is inspired by a very famous 2D game, the brick breaker\0";
    char chaineTheme2[53]="Please enter your username. Press RETURN to confirm\0";
    char chaineTheme3[23]="Please choose a theme\0";

    sprite(0,0,"img/menu/3.bmp");
    textChangeColor(255,255,255,255);
    textDrawText(chaineTheme3,390,520,comfortaaFont_28);
    textDrawText(chaineTheme2,390,360,comfortaaFont_28);
    textDrawText(chaineTheme1,390,280,comfortaaFont_28);
    textDrawText(chaineTheme,390,245,comfortaaFont_28);
    textChangeColor(0,0,0,255);
    textDrawText(scan,390,435,comfortaaFont_28);

    if(theme1>0){
      //steampunk

      if(rect==1 || rect==2 || rect==3 || rect==4 || rect==5 || rect==6){
        sprite(640,675,"img/menu/droite.bmp");
        sprite(230,675,"img/menu/gauche.bmp");
      }
      else{
        sprite(650,675,"img/menu/droite.bmp");
        sprite(220,675,"img/menu/gauche.bmp");
      }
    }
    if(theme2>0){
      //arcade
      if(rect==1 || rect==2 || rect==3 || rect==4 || rect==5 || rect==6){
        sprite(1095,675,"img/menu/droite.bmp");
        sprite(675,675,"img/menu/gauche.bmp");
      }
      else{
        sprite(1105,675,"img/menu/droite.bmp");
        sprite(665,675,"img/menu/gauche.bmp");
      }
    }
    if(theme3>0){
      //classique
      if(rect==1 || rect==2 || rect==3 || rect==4 || rect==5 || rect==6){
        sprite(1550,675,"img/menu/droite.bmp");
        sprite(1110,675,"img/menu/gauche.bmp");
      }
      else{
        sprite(1560,675,"img/menu/droite.bmp");
        sprite(1100,675,"img/menu/gauche.bmp");
      }
    }
}

void frameCount(){

// Compte des frames pour les animations

  rect++;
  if(rect>12 && menu==2){
    rect=0;
  }
  if(rect==12 && menu==4){
    rect=0;
  }
  if(rect==60 && programLaunched2==1 && (theme==3 || theme==2 || theme==1 || menu<2)){
    rect=0;
  }
  if(rect>110 && nextLvl==2){
    rect=0;
  }
}

void variableTheme(){

// Initialisation des variables en fonction du thème choisi

  if(theme==1){
    xSprite=1920;
    ySprite=0;
    xSprite2=0;
    ySprite2=760;
    rect=0;
  }
  if(theme==2){
    rect=0;
    xSprite=1920;
    ySprite=980;
    xSprite2=0;
    ySprite2=760;
  }
  if(theme==3){
    xSprite=1920;
    ySprite=880;
    xSprite2=0;
    ySprite2=760;
    rect=0;
  }
}

void gameMenu(){

// Affichage des menus en fonction du thème choisi

  if(sound==0){
    audioLoadAndPlay("sound/menu.wav",2);
    sound=1;
  }
  if(theme==1){
    sprite(0,0,"img/menuSteampunk/menuSteampunk.bmp");
    if(theme1>0){
      changeColor(115,86,80);
      drawRect(125,300,125,5);
    }
    if(theme2>0){
      changeColor(115,86,80);
      drawRect(125,390,150,5);
    }
    if(theme3>0){
      changeColor(115,86,80);
      drawRect(125,480,170,5);
    }
    if(theme4>0){
      changeColor(115,86,80);
      drawRect(125,570,110,5);
    }
    if(score>0){
      sprite(0,0,"img/menuSteampunk/scoreSteampunk.bmp");
      drawScore();
      if(scoreBack>0){
          changeColor(115,86,80);
          drawRect(80,135,150,5);
      }
    }
    if(rect>=0 && rect<=30){
    sprite(xSprite, ySprite,"img/menuSteampunk/dirigeable.bmp");
     }
     if(rect>=31 && rect<=60){
    sprite(xSprite, ySprite-5,"img/menuSteampunk/dirigeable.bmp");
     }
    xSprite=xSprite-2;
    if(xSprite<-300){
      xSprite=1920;
    }
    menuLevel();
  }
  if(theme==2){
    sprite(0,0,"img/menuArcade/menuArcade.bmp");
    if(theme1>0){
      changeColor(223,116,186);
      drawRect(115,310,200,5);
    }
    if(theme2>0){
      changeColor(223,116,186);
      drawRect(115,400,240,5);
    }
    if(theme3>0){
      changeColor(223,116,186);
      drawRect(115,485,250,5);
    }
    if(theme4>0){
      changeColor(223,116,186);
      drawRect(115,575,200,5);
    }
    if(score>0){
      sprite(0,0,"img/menuArcade/scoreArcade.bmp");
      drawScore();
      if(scoreBack>0){
          changeColor(247, 195, 154);
          drawRect(60,145,208,5);
      }
    }
    if(rect>=0 && rect<=30){
    sprite(xSprite, ySprite,"img/menuArcade/mob.bmp");
     }
     if(rect>=31 && rect<=60){
    sprite(xSprite, ySprite-5,"img/menuArcade/mob.bmp");
     }
    xSprite=xSprite-2;
    if(xSprite<-300){
      xSprite=1920;
    }
    menuLevel();
  }
  if(theme==3){
    sprite(0,0,"img/menuClassique/menuClassique.bmp");
    if(theme1>0){
      changeColor(196,39,39);
      drawRect(115,300,150,5);
    }
    if(theme2>0){
      changeColor(196,39,39);
      drawRect(115,390,180,5);
    }
    if(theme3>0){
      changeColor(196,39,39);
      drawRect(115,480,200,5);
    }
    if(theme4>0){
      changeColor(196,39,39);
      drawRect(115,570,130,5);
    }
    if(score>0){
      sprite(0,0,"img/menuClassique/scoreClassique.bmp");
      drawScore();
      if(scoreBack>0){
          changeColor(196,39,39);
          drawRect(80,135,170,5);
      }
    }
    xSprite2++;
    if(rect>=0 && rect<=15){
      sprite(xSprite2, ySprite2,"img/menuClassique/old1.bmp");
    }
    if(rect>=16 && rect<=30){
      sprite(xSprite2, ySprite2,"img/menuClassique/old2.bmp");
    }
    if(rect>=31 && rect<=45){
      sprite(xSprite2, ySprite2,"img/menuClassique/old3.bmp");
    }
    if(rect>=46 && rect<=60){
      sprite(xSprite2, ySprite2,"img/menuClassique/old4.bmp");
    }
    if(xSprite2>1920){
      xSprite2=0;
    }
    sprite(xSprite, ySprite,"img/menuClassique/car.bmp");
    xSprite=xSprite-5;
    if(xSprite<-300){
      xSprite=1920;
    }
    menuLevel();
  }
}

void menuPause(){

// Affichage du menu pause et mise en pause du jeu

  if(pauseMenu==1){
    vXsave=vX;
    vYsave=vY;
    vX=0;
    vY=0;
    yMoove=0;
  }
  if(pauseMenu>0){
    if(theme==1){
      sprite(750,300,"img/menuSteampunk/menuIGSteampunk.bmp");
      if(pauseTheme1>0){
        changeColor(255, 145, 77);
        drawRect(835,460,230,5);
      }
      if(pauseTheme2>0){
        changeColor(255, 145, 77);
        drawRect(885,540,130,5);
      }
    }
    if(theme==2){
      sprite(750,300,"img/menuArcade/menuIGArcade.bmp");
      if(pauseTheme1>0){
        changeColor(148,80,249);
        drawRect(775,465,355,5);
      }
      if(pauseTheme2>0){
        changeColor(148,80,249);
        drawRect(850,525,200,5);
      }
    }
    if(theme==3){
      sprite(750,300,"img/menuClassique/menuIGClassique.bmp");
      if(pauseTheme1>0){
        changeColor(123,71,33);
        drawRect(815,455,275,5);
      }
      if(pauseTheme2>0){
        changeColor(123,71,33);
        drawRect(875,515,160,5);
      }
    }
    pauseMenu++;
  }
}

void drawLife(){

// Affichage du nombre de vie restante

  if(theme==1){
    textChangeColor(255, 145, 77,255);
    textDrawText("Lives remaining:",1200,990,comfortaaFont_36);
    if(life==3){
      if(text2<43){
        sprite(1500,960,"img/menuSteampunk/lifeSteampunk.bmp");
      }
      else{
        sprite(1500,960,"img/menuSteampunk/checkSteampunk.bmp");
      }
      if(text2<29){
        sprite(1620,960,"img/menuSteampunk/lifeSteampunk.bmp");
      }
      else{
        sprite(1620,960,"img/menuSteampunk/checkSteampunk.bmp");
      }
      if(text2<15){
        sprite(1740,960,"img/menuSteampunk/lifeSteampunk.bmp");
      }
      else{
        sprite(1740,960,"img/menuSteampunk/checkSteampunk.bmp");
      }
    }
    if(life==2){
      if(text2<29){
        sprite(1500,960,"img/menuSteampunk/lifeSteampunk.bmp");
      }
      else{
        sprite(1500,960,"img/menuSteampunk/checkSteampunk.bmp");
      }
      if(text2<15){
        sprite(1620,960,"img/menuSteampunk/lifeSteampunk.bmp");
      }
      else{
        sprite(1620,960,"img/menuSteampunk/checkSteampunk.bmp");
      }
    }
    if(life==1){
      if(text2<15){
        sprite(1500,960,"img/menuSteampunk/lifeSteampunk.bmp");
      }
      else{
        sprite(1500,960,"img/menuSteampunk/checkSteampunk.bmp");
      }
    }
  }
  if(theme==2){
    textChangeColor(148,80,249,255);
    textDrawText("Life remain:",1300,990,comfortaaFont_36);
    if(life==3){
      if(text2<43){
        sprite(1500,960,"img/menuArcade/lifeArcade.bmp");
      }
      else{
        sprite(1500,960,"img/menuArcade/checkArcade.bmp");
      }
      if(text2<29){
        sprite(1620,960,"img/menuArcade/lifeArcade.bmp");
      }
      else{
        sprite(1620,960,"img/menuArcade/checkArcade.bmp");
      }
      if(text2<15){
        sprite(1740,960,"img/menuArcade/lifeArcade.bmp");
      }
      else{
        sprite(1740,960,"img/menuArcade/checkArcade.bmp");
      }
    }
    if(life==2){
      if(text2<29){
        sprite(1500,960,"img/menuArcade/lifeArcade.bmp");
      }
      else{
        sprite(1500,960,"img/menuArcade/checkArcade.bmp");
      }
      if(text2<15){
        sprite(1620,960,"img/menuArcade/lifeArcade.bmp");
      }
      else{
        sprite(1620,960,"img/menuArcade/checkArcade.bmp");
      }
    }
    if(life==1){
      if(text2<15){
        sprite(1500,960,"img/menuArcade/lifeArcade.bmp");
      }
      else{
        sprite(1500,960,"img/menuArcade/checkArcade.bmp");
      }
    }
  }
  if(theme==3){
    textChangeColor(123,71,33,255);
    textDrawText("Life remain:",1300,990,comfortaaFont_36);
    if(life==3){
      if(text2<43){
        sprite(1500,960,"img/menuClassique/lifeClassique.bmp");
      }
      else{
        sprite(1500,960,"img/menuClassique/checkClassique.bmp");
      }
      if(text2<29){
        sprite(1620,960,"img/menuClassique/lifeClassique.bmp");
      }
      else{
        sprite(1620,960,"img/menuClassique/checkClassique.bmp");
      }
      if(text2<15){
        sprite(1740,960,"img/menuClassique/lifeClassique.bmp");
      }
      else{
        sprite(1740,960,"img/menuClassique/checkClassique.bmp");
      }
    }
    if(life==2){
      if(text2<29){
        sprite(1500,960,"img/menuClassique/lifeClassique.bmp");
      }
      else{
        sprite(1500,960,"img/menuClassique/checkClassique.bmp");
      }
      if(text2<15){
        sprite(1620,960,"img/menuClassique/lifeClassique.bmp");
      }
      else{
        sprite(1620,960,"img/menuClassique/checkClassique.bmp");
      }
    }
    if(life==1){
      if(text2<15){
        sprite(1500,960,"img/menuClassique/lifeClassique.bmp");
      }
      else{
        sprite(1500,960,"img/menuClassique/checkClassique.bmp");
      }
    }
  }
}

void drawStreak(){

// Affichage des streaks

  char compteur[300];
  sprintf(compteur,"%d", streak);
  if(theme==1 && nextLvl<2){
  textChangeColor(255, 145, 77,255);
  textDrawText("Streak: X", 780, 990,comfortaaFont_36);
  textDrawText(compteur , 950, 980,comfortaaFont_52);
  }
  if(theme==2 && nextLvl<2){
  textChangeColor(148,80,249,255);
  textDrawText("Streak: X", 780, 990,comfortaaFont_36);
  textDrawText(compteur , 950, 980,comfortaaFont_52);
  }
  if(theme==3 && nextLvl<2){
  textChangeColor(123,71,33,255);
  textDrawText("Streak: X", 780, 990,comfortaaFont_36);
  textDrawText(compteur , 950, 980,comfortaaFont_52);
  }
}

void gameOver(){

// Affichage du menu game over

  if(over>0){
    if(theme==1){
      sprite(750,300,"img/menuSteampunk/menuGOSteampunk.bmp");
      if(pauseTheme1>0){
        changeColor(255, 145, 77);
        drawRect(850,545,60,5);
      }
      if(pauseTheme2>0){
        changeColor(255, 145, 77);
        drawRect(980,545,100,5);
      }
    }
    if(theme==2){
      sprite(750,300,"img/menuArcade/menuGOArcade.bmp");
      if(pauseTheme1>0){
        changeColor(148,80,249);
        drawRect(835,545,90,5);
      }
      if(pauseTheme2>0){
        changeColor(148,80,249);
        drawRect(950,545,170,5);
      }
    }
    if(theme==3){
      sprite(750,300,"img/menuClassique/menuGOClassique.bmp");
      if(pauseTheme1>0){
        changeColor(123,71,33);
        drawRect(845,545,70,5);
      }
      if(pauseTheme2>0){
        changeColor(123,71,33);
        drawRect(970,545,120,5);
      }
    }
  }
}

void endLvl(){

// Affichage du menu de fin de niveau

    if(nextLvl>0 && bonusCount==0){
        nextLvl=2;
        launch=0;
        vX=0;
        vY=-5;
        x=940;
        y=855;
        mooveX=885;
      if(lvl==1 || lvl==2){
        if(theme==1){
          sprite(750,300,"img/menuSteampunk/menuNLSteampunk.bmp");
          if(pauseTheme1>0){
            changeColor(255, 145, 77);
            drawRect(820,545,120,5);
          }
          if(pauseTheme2>0){
            changeColor(255, 145, 77);
            drawRect(1000,545,60,5);
          }
        }
        if(theme==2){
          sprite(750,300,"img/menuArcade/menuNLArcade.bmp");
          if(pauseTheme1>0){
            changeColor(148,80,249);
            drawRect(790,545,190,5);
          }
          if(pauseTheme2>0){
            changeColor(148,80,249);
            drawRect(1010,545,85,5);
          }
        }
        if(theme==3){
          sprite(750,300,"img/menuClassique/menuNLClassique.bmp");
          if(pauseTheme1>0){
            changeColor(123,71,33);
            drawRect(815,545,130,5);
          }
          if(pauseTheme2>0){
            changeColor(123,71,33);
            drawRect(995,545,70,5);
          }
        }
      }
      if(lvl==3){

      confettis();
        if(theme==1){
          sprite(750,300,"img/menuSteampunk/menuWINSteampunk.bmp");
          if(pauseTheme1>0){
            changeColor(255, 145, 77);
            drawRect(925,545,65,5);
          }
        }
        if(theme==2){
          sprite(750,300,"img/menuArcade/menuWINArcade.bmp");
          if(pauseTheme1>0){
            changeColor(148,80,249);
            drawRect(910,545,85,5);
          }
        }
        if(theme==3){
          sprite(750,300,"img/menuClassique/menuWINClassique.bmp");
          if(pauseTheme1>0){
            changeColor(123,71,33);
            drawRect(915,545,75,5);
          }
        }
      }
    }
}

void pointCount(){

// Affichage de l'animation de calcul des points en fin de niveau

  if(nextLvl>1){
    if(resetChar==1){
        strcpy(saveChaine,"                                       ");
        strcpy(saveChaine2,"                                                                                    ");
      resetChar=0;
    }
    if(theme==1){
      textChangeColor(255, 145, 77,255);
    }
    if(theme==2){
      textChangeColor(148,80,249,255);
    }
    if(theme==3){
      textChangeColor(123,71,33,255);
    }
    if(text<=23){
        saveChaine[text]=chaineScore[text];
        textDrawText(saveChaine, 20, 955,comfortaaFont_28);
        text++;
      }
    if(text>23){
      textDrawText(chaineScore, 20, 955,comfortaaFont_28);
    }
    char point[100]="";
    sprintf(point,"%d",compteurPoint);

    char lifeChaine[50]=" + 1 life (50)";

    char plus[50]=" + points past levels (";

    char lastpoint[50]="";
    sprintf(lastpoint,"%d",savePoint);

    char end[10]=") = ";

    char result[10]="";
    resultScore=compteurPoint+savePoint+(50*life);
    sprintf(result,"%d",resultScore);

    switch(life){
      case 0:
        strcat(point,plus);
        strcat(point,lastpoint);
        strcat(point,end);
        strcat(point,result);
        if(text>23 && text2<100){
          saveChaine2[text2]=point[text2];
          textDrawText(saveChaine2, 20, 990,comfortaaFont_28);
          text2++;
        }
        else if(text2>=100){
          textDrawText(point, 20, 990,comfortaaFont_28);
        }
        break;
      case 1:
        strcat(point,lifeChaine);
        strcat(point,plus);
        strcat(point,lastpoint);
        strcat(point,end);
        strcat(point,result);
        if(text>23 && text2<100){
          saveChaine2[text2]=point[text2];
          textDrawText(saveChaine2, 20, 990,comfortaaFont_28);
          text++;
        }
        else if(text2>=100){
          textDrawText(point, 20, 990,comfortaaFont_28);
        }
        break;
      case 2:
        strcat(point,lifeChaine);
        strcat(point,lifeChaine);
        strcat(point,plus);
        strcat(point,lastpoint);
        strcat(point,end);
        strcat(point,result);
        if(text>23 && text2<100){
          saveChaine2[text2]=point[text2];
          textDrawText(saveChaine2, 20, 990,comfortaaFont_28);
          text2++;
        }
        else if(text2>=100){
          textDrawText(point, 20, 990,comfortaaFont_28);
        }
        break;
      case 3:
        strcat(point,lifeChaine);
        strcat(point,lifeChaine);
        strcat(point,lifeChaine);
        strcat(point,plus);
        strcat(point,lastpoint);
        strcat(point,end);
        strcat(point,result);
        if(text>23 && text2<100){
          saveChaine2[text2]=point[text2];
          textDrawText(saveChaine2, 20, 990,comfortaaFont_28);
          text2++;
        }
        else if(text2>=100){
          textDrawText(point, 20, 990,comfortaaFont_28);
        }
        break;
    }
  }
}

void confettis(){

// Affichage des confettis à la fin du dernier niveau

  if(nextLvl>1 && lvl==3){
    sprite(confettisX, confettisY1,"img/confettis.bmp");
    sprite(confettisX, confettisY2,"img/confettis.bmp");
    confettisY1=confettisY1+4;
    confettisY2=confettisY2+4;
    if(rect==10){
        audioLoadAndPlay("sound/win.wav",1);
      }
    if(confettisY1==1080){
      confettisY1=-1080;
    }
    if(confettisY2==1080){
      confettisY2=-1080;
    }
  }
}

void menuLevel(){

// Affichage du menu de gestion des niveaux

  if(menuL==1){
    switch(theme){
      case 1:
        sprite(0,0,"img/menuSteampunk/menuLSteampunk.bmp");
        if(theme1>0){
          changeColor(115,86,80);
          drawRect(780,280,370,5);
        }
        if(theme2>0){
          changeColor(115,86,80);
          drawRect(780,525,370,5);
        }
        if(theme3>0){
          changeColor(115,86,80);
          drawRect(780,775,370,5);
        }
        if(theme4>0){
          changeColor(115,86,80);
          drawRect(130,170,140,5);
        }
        break;
      case 2:
        sprite(0,0,"img/menuArcade/menuLArcade.bmp");
        if(theme1>0){
          changeColor(223,116,186);
          drawRect(680,285,580,5);
        }
        if(theme2>0){
          changeColor(223,116,186);
          drawRect(680,535,580,5);
        }
        if(theme3>0){
          changeColor(223,116,186);
          drawRect(680,780,580,5);
        }
        if(theme4>0){
          changeColor(223,116,186);
          drawRect(105,175,180,5);
        }
        break;
      case 3:
        sprite(0,0,"img/menuClassique/menuLClassique.bmp");
        if(theme1>0){
          changeColor(196,39,39);
          drawRect(760,275,420,5);
        }
        if(theme2>0){
          changeColor(196,39,39);
          drawRect(760,525,420,5);
        }
        if(theme3>0){
          changeColor(196,39,39);
          drawRect(760,770,420,5);
        }
        if(theme4>0){
          changeColor(196,39,39);
          drawRect(110,170,190,5);
        }
        break;
    }
  }
}

void eventText(){

  switch(theme){
    case 1:
      changeColor(255, 145, 77);
      break;
    case 2:
      changeColor(148,80,249);
      break;
    case 3:
      changeColor(123,71,33);
      break;
  }
  if(bomb==1){
    if(rect<40){
      if(draw==0){
        textDrawText("BOMB",120,870, comfortaaFont_36);
      }
      if(saveY1>0 && saveX1>0 && rect<20){
        sprite(saveX1, saveY1, "img/fireBrick.bmp");
      }
      if(saveY2>0 && saveX2>0 && rect<20){
        sprite(saveX2, saveY2, "img/fireBrick.bmp");
      }
      if(saveY3>0 && saveX3>0 && rect<20){
        sprite(saveX3, saveY3, "img/fireBrick.bmp");
      }
      if(saveY4>0 && saveX4>0 && rect<20){
        sprite(saveX4, saveY4, "img/fireBrick.bmp");
      }
      if(saveY5>0 && saveX5>0 && rect<20){
        sprite(saveX5, saveY5, "img/fireBrick.bmp");
      }
    }
    if(rect>40){
      bomb=0;
      draw=0;
      saveX1=2000;
      saveX2=2000;
      saveX3=2000;
      saveX4=2000;
      saveX5=2000;
      saveY1=2000;
      saveY2=2000;
      saveY3=2000;
      saveY4=2000;
      saveY5=2000;
    }
  }
  if(rand1==1 && draw==1){
    if(rect<40){
      textDrawText("PADDLE SIZE++",120,870, comfortaaFont_36);
    }
    if(rect>40){
      rand1=0;
      draw=0;
    }
  }
  if(rand2==1 && draw==0){
    if(rect<40){
      textDrawText("PADDLE SIZE--",120, 870, comfortaaFont_36);
    }
    if(rect>40){
      rand2=0;
      draw=0;
    }
  }
  if(rand3==1 && draw==0){
    if(rect<40){
      textDrawText("BALL SPEED++",120,870, comfortaaFont_36);
    }
    if(rect>40){
      rand3=0;
      draw=0;
    }
  }
}

void graph(){

    graphisme(); //Draw background
    brickPrint(); // Affichage des briques
    raquette(); // Affichage de la raquette
    drawDropPoint(); // Affichage des sprites des bonus
    drawBall(); // Affichae de la balle en fonction du thème
    compteurPoints(); // Affichage du compteur des points pendant le jeu
    menuPause(); // Affichage du menu pause et mise en pause du jeu
    pointCount(); // Affichage de l'animation de calcul des points en fin de niveau
    drawStreak(); // Affichage des streaks
    drawLife(); // Affichage du nombre de vie restante
    gameOver(); // Affichage du menu game over
    endLvl(); // Affichage du menu de fin de niveau
    eventText(); // Affichage messsage event brick

}


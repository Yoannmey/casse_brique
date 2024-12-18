#include <cjson/cJSON.h>
#include <stdio.h>
#include <string.h>

#include "save.h"
#include "function.h"
#include "sdl_helper/audio_functions.h"
#include "sdl_helper/constants.h"
#include "sdl_helper/text_functions.h"


extern char scan[50]; // Chaine nom du joueur
extern int savePoint; // Variable sauvegarde des points
extern int theme; // Variable gestion du theme

int decale=0; // Variable décalage des scores sur le tableau

typedef struct save{ // Structure nom du joueur, score du joueur
    char player[50];
    int score;
} save;

save save1, save2, save3, save4, save5, save6, save7, save8, save9, save10; // Sauvegarde des scores avant placement sur le tableau
save score1, score2, score3, score4, score5, score6, score7, score8, score9, score10; // Placement des scores sur le tableau

void saveScore(){

// Enregistrement du nom du joueur et des score obtenus

    if(savePoint>save1.score){
        decale=1;
        shift();
        strcpy(save1.player,scan);
        save1.score=savePoint;
    }
    else if(savePoint>save2.score){
        decale=2;
        shift();
        strcpy(save2.player,scan);
        save2.score=savePoint;
    }
    else if(savePoint>save3.score){
        decale=3;
        shift();
        strcpy(save3.player,scan);
        save3.score=savePoint;
    }
    else if(savePoint>save4.score){
        decale=4;
        shift();
        strcpy(save4.player,scan);
        save4.score=savePoint;
    }
    else if(savePoint>save5.score){
        decale=5;
        shift();
        strcpy(save5.player,scan);
        save5.score=savePoint;
    }
    else if(savePoint>save6.score){
        decale=6;
        shift();
        strcpy(save6.player,scan);
        save6.score=savePoint;
    }
    else if(savePoint>save7.score){
        decale=7;
        shift();
        strcpy(save7.player,scan);
        save7.score=savePoint;
    }
    else if(savePoint>save8.score){
        decale=8;
        shift();
        strcpy(save8.player,scan);
        save8.score=savePoint;
    }
    else if(savePoint>save9.score){
        decale=9;
        shift();
        strcpy(save9.player,scan);
        save9.score=savePoint;
    }
    else if(savePoint>save10.score){
        decale=10;
        shift();
        strcpy(save10.player,scan);
        save10.score=savePoint;
    }
    saveFile();
}

void saveFile() {

// Ouverture et premiere écriture dans le fichier json pour la sauvegarde du nom et des scores des joueurs

   // Creation des objets JSON (player et score)
   cJSON *json = cJSON_CreateObject();
   cJSON_AddStringToObject(json, "player1",save1.player);
   cJSON_AddNumberToObject(json, "score1", save1.score);
   cJSON_AddStringToObject(json, "player2",save2.player);
   cJSON_AddNumberToObject(json, "score2", save2.score);
   cJSON_AddStringToObject(json, "player3",save3.player);
   cJSON_AddNumberToObject(json, "score3", save3.score);
   cJSON_AddStringToObject(json, "player4",save4.player);
   cJSON_AddNumberToObject(json, "score4", save4.score);
   cJSON_AddStringToObject(json, "player5",save5.player);
   cJSON_AddNumberToObject(json, "score5", save5.score);
   cJSON_AddStringToObject(json, "player6",save6.player);
   cJSON_AddNumberToObject(json, "score6", save6.score);
   cJSON_AddStringToObject(json, "player7",save7.player);
   cJSON_AddNumberToObject(json, "score7", save7.score);
   cJSON_AddStringToObject(json, "player8",save8.player);
   cJSON_AddNumberToObject(json, "score8", save8.score);
   cJSON_AddStringToObject(json, "player9",save9.player);
   cJSON_AddNumberToObject(json, "score9", save9.score);
   cJSON_AddStringToObject(json, "player10",save10.player);
   cJSON_AddNumberToObject(json, "score10", save10.score);


   // Mettre les objets dans une chaine de caractère
   char *json_str = cJSON_Print(json);

   //  Ouvrir en écriture le fichier
   FILE *file = fopen("save.json", "w");
   fprintf(file,"%s\n",json_str);
   fclose(file);

   cJSON_free(json_str);
   cJSON_Delete(json);
}

void initSave(){

// Ouverture et modification du fichier json à la fin d'une partie'*

    FILE *file =fopen("save.json","r"); // Ouverture du fichier "save.json"(Il devient file)
    char temp[100000]; // Chaine de caractère "tampon" (buffer)
    fread(temp,1,100000,file); // Read du fichier file dans temp (nomChaine,taille octect(1),taille chaine(1000),fichier )
    fclose(file); // Fermeture du fichier

    cJSON *json = cJSON_Parse(temp); // Analyse de la chaine temp pour pouvoir en extraire les données

    cJSON *player1 = cJSON_GetObjectItemCaseSensitive(json, "player1");
    strcpy(save1.player,player1->valuestring);
    cJSON *score1 = cJSON_GetObjectItemCaseSensitive(json, "score1");
    save1.score = score1->valueint;

    cJSON *player2 = cJSON_GetObjectItemCaseSensitive(json, "player2");
    strcpy(save2.player,player2->valuestring);
    cJSON *score2 = cJSON_GetObjectItemCaseSensitive(json, "score2");
    save2.score = score2->valueint;

    cJSON *player3 = cJSON_GetObjectItemCaseSensitive(json, "player3");
    strcpy(save3.player,player3->valuestring);
    cJSON *score3 = cJSON_GetObjectItemCaseSensitive(json, "score3");
    save3.score = score3->valueint;

    cJSON *player4 = cJSON_GetObjectItemCaseSensitive(json, "player4");
    strcpy(save4.player,player4->valuestring);
    cJSON *score4 = cJSON_GetObjectItemCaseSensitive(json, "score4");
    save4.score = score4->valueint;

    cJSON *player5 = cJSON_GetObjectItemCaseSensitive(json, "player5");
    strcpy(save5.player,player5->valuestring);
    cJSON *score5 = cJSON_GetObjectItemCaseSensitive(json, "score5");
    save5.score = score5->valueint;

    cJSON *player6 = cJSON_GetObjectItemCaseSensitive(json, "player6");
    strcpy(save6.player,player6->valuestring);
    cJSON *score6 = cJSON_GetObjectItemCaseSensitive(json, "score6");
    save6.score = score6->valueint;

    cJSON *player7 = cJSON_GetObjectItemCaseSensitive(json, "player7");
    strcpy(save7.player,player7->valuestring);
    cJSON *score7 = cJSON_GetObjectItemCaseSensitive(json, "score7");
    save7.score = score7->valueint;

    cJSON *player8 = cJSON_GetObjectItemCaseSensitive(json, "player8");
    strcpy(save8.player,player8->valuestring);
    cJSON *score8 = cJSON_GetObjectItemCaseSensitive(json, "score8");
    save8.score = score8->valueint;

    cJSON *player9 = cJSON_GetObjectItemCaseSensitive(json, "player9");
    strcpy(save9.player,player9->valuestring);
    cJSON *score9 = cJSON_GetObjectItemCaseSensitive(json, "score9");
    save9.score = score9->valueint;

    cJSON *player10 = cJSON_GetObjectItemCaseSensitive(json, "player10");
    strcpy(save10.player,player10->valuestring);
    cJSON *score10 = cJSON_GetObjectItemCaseSensitive(json, "score10");
    save10.score = score10->valueint;

    cJSON_Delete(json);
}

void shift(){

// Decalage des scores sur le tableau en fonction du dernier résultat obtenu

    switch(decale){
        case 1:
            save10.score=save9.score;
            strcpy(save10.player,save9.player);
            save9.score=save8.score;
            strcpy(save9.player,save8.player);
            save8.score=save7.score;
            strcpy(save8.player,save7.player);
            save7.score=save6.score;
            strcpy(save7.player,save6.player);
            save6.score=save5.score;
            strcpy(save6.player,save5.player);
            save5.score=save4.score;
            strcpy(save5.player,save4.player);
            save4.score=save3.score;
            strcpy(save4.player,save3.player);
            save3.score=save2.score;
            strcpy(save3.player,save2.player);
            save2.score=save1.score;
            strcpy(save2.player,save1.player);
            break;
        case 2:
            save10.score=save9.score;
            strcpy(save10.player,save9.player);
            save9.score=save8.score;
            strcpy(save9.player,save8.player);
            save8.score=save7.score;
            strcpy(save8.player,save7.player);
            save7.score=save6.score;
            strcpy(save7.player,save6.player);
            save6.score=save5.score;
            strcpy(save6.player,save5.player);
            save5.score=save4.score;
            strcpy(save5.player,save4.player);
            save4.score=save3.score;
            strcpy(save4.player,save3.player);
            save3.score=save2.score;
            strcpy(save3.player,save2.player);
            break;
        case 3:
            save10.score=save9.score;
            strcpy(save10.player,save9.player);
            save9.score=save8.score;
            strcpy(save9.player,save8.player);
            save8.score=save7.score;
            strcpy(save8.player,save7.player);
            save7.score=save6.score;
            strcpy(save7.player,save6.player);
            save6.score=save5.score;
            strcpy(save6.player,save5.player);
            save5.score=save4.score;
            strcpy(save5.player,save4.player);
            save4.score=save3.score;
            strcpy(save4.player,save3.player);
            break;
        case 4:
            save10.score=save9.score;
            strcpy(save10.player,save9.player);
            save9.score=save8.score;
            strcpy(save9.player,save8.player);
            save8.score=save7.score;
            strcpy(save8.player,save7.player);
            save7.score=save6.score;
            strcpy(save7.player,save6.player);
            save6.score=save5.score;
            strcpy(save6.player,save5.player);
            save5.score=save4.score;
            strcpy(save5.player,save4.player);
            break;
        case 5:
            save10.score=save9.score;
            strcpy(save10.player,save9.player);
            save9.score=save8.score;
            strcpy(save9.player,save8.player);
            save8.score=save7.score;
            strcpy(save8.player,save7.player);
            save7.score=save6.score;
            strcpy(save7.player,save6.player);
            save6.score=save5.score;
            strcpy(save6.player,save5.player);
            break;
        case 6:
            save10.score=save9.score;
            strcpy(save10.player,save9.player);
            save9.score=save8.score;
            strcpy(save9.player,save8.player);
            save8.score=save7.score;
            strcpy(save8.player,save7.player);
            save7.score=save6.score;
            strcpy(save7.player,save6.player);
            break;
        case 7:
            save10.score=save9.score;
            strcpy(save10.player,save9.player);
            save9.score=save8.score;
            strcpy(save9.player,save8.player);
            save8.score=save7.score;
            strcpy(save8.player,save7.player);
            break;
        case 8:
            save10.score=save9.score;
            strcpy(save10.player,save9.player);
            save9.score=save8.score;
            strcpy(save9.player,save8.player);
            break;
        case 9:
            save10.score=save9.score;
            strcpy(save10.player,save9.player);
            break;
    }
}

void drawScore(){

// Affichage du nom du joueut et de son score sur le tableau des scores

    switch(theme){
        case 1:
            textChangeColor(115, 86, 80,255);
            break;
        case 2:
            textChangeColor(247, 195, 154,255);
            break;
        case 3:
            textChangeColor(196,39,39,255);
            break;
    }
    if(save1.score>0){
        textDrawText(save1.player,420,220,comfortaaFont_52);
        sprintf(score1.player,"%d", save1.score);
        textDrawText(score1.player,775,225,comfortaaFont_52);
    }
    if(save2.score>0){
        textDrawText(save2.player,420,293,comfortaaFont_52);
        sprintf(score2.player,"%d", save2.score);
        textDrawText(score2.player,775,298,comfortaaFont_52);
    }
    if(save3.score>0){
        textDrawText(save3.player,420,366,comfortaaFont_52);
        sprintf(score3.player,"%d", save3.score);
        textDrawText(score3.player,775,371,comfortaaFont_52);
    }
    if(save4.score>0){
        textDrawText(save4.player,420,439,comfortaaFont_52);
        sprintf(score4.player,"%d", save4.score);
        textDrawText(score4.player,775,444,comfortaaFont_52);
    }
    if(save5.score>0){
        textDrawText(save5.player,420,512,comfortaaFont_52);
        sprintf(score5.player,"%d", save5.score);
        textDrawText(score5.player,775,517,comfortaaFont_52);
    }
    if(save6.score>0){
        textDrawText(save6.player,420,585,comfortaaFont_52);
        sprintf(score6.player,"%d", save6.score);
        textDrawText(score6.player,775,590,comfortaaFont_52);
    }
    if(save7.score>0){
        textDrawText(save7.player,420,658,comfortaaFont_52);
        sprintf(score7.player,"%d", save7.score);
        textDrawText(score7.player,775,663,comfortaaFont_52);
    }
    if(save8.score>0){
        textDrawText(save8.player,420,731,comfortaaFont_52);
        sprintf(score8.player,"%d", save8.score);
        textDrawText(score8.player,775,736,comfortaaFont_52);
    }
    if(save9.score>0){
        textDrawText(save9.player,420,804,comfortaaFont_52);
        sprintf(score9.player,"%d", save9.score);
        textDrawText(score9.player,775,809,comfortaaFont_52);
    }
    if(save10.score>0){
        textDrawText(save10.player,420,877,comfortaaFont_52);
        sprintf(score10.player,"%d", save10.score);
        textDrawText(score10.player,775,882,comfortaaFont_52);
    }
}

// TP PONG SDL2

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "main.h"


#include <time.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 780






int main(int argc, char *argv[])
{
     balle_jeu balle;
     game myGame;
     gameState state;

     SDL_Rect joueur1;
     SDL_Rect joueur2;


    srand(time(NULL)); //on set l'aléatoire pour les déplacements

    //Pour les 60 fps
    unsigned int frameLimit = SDL_GetTicks() + 16;

    if(init("SDL_Pong",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&myGame, &joueur1, &joueur2, &balle)){
        state.g_bRunning=1;
    }else{
        return 1;//something's wrong
    }


    //Create texture for drawing in texture or load picture
    myGame.g_texture=SDL_CreateTexture(myGame.g_pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,SCREEN_WIDTH,SCREEN_HEIGHT);

    while(state.g_bRunning){

            handleEvents(&state, &joueur1, &joueur2, &myGame); //on appelle les fonctions tant que le jeu est en cours
            deplace_balle(&balle,joueur1,joueur2);



            SDL_SetRenderDrawColor(myGame.g_pRenderer,120,0,0,255); //on choisit la couleur du fond
            SDL_RenderClear(myGame.g_pRenderer);

            affiche_tout(&myGame,joueur1,joueur2,balle);


        // Gestion des 60 fps (1000ms/60 = 16.6 -> 16
            delay(frameLimit);
            frameLimit = SDL_GetTicks() + 16;

    }
    destroy(&myGame);


    SDL_Quit();

  return 0;
}



int init(char *title, int xpos,int ypos,int height, int width,int flags,game *myGame, SDL_Rect *joueur1, SDL_Rect *joueur2, balle_jeu *balle){

    //initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING)>=0)
    {
            //if succeeded create our window
            myGame->g_pWindow=SDL_CreateWindow(title,xpos,ypos,height,width,flags);
            //if succeeded create window, create our render
            if(myGame->g_pWindow!=NULL){
                myGame->g_pRenderer=SDL_CreateRenderer(myGame->g_pWindow,-1,SDL_RENDERER_ACCELERATED);
            }

    }else{
        return 0;
    }

    //initialize ttf




    //position de départ de la raquette du j1
    joueur1->x=20;
    joueur1->y=SCREEN_HEIGHT/2+10;
    joueur1->h=100;
    joueur1->w=20;
    //" du j2
    joueur2->x=SCREEN_WIDTH-40;
    joueur2->y=SCREEN_HEIGHT/2+10;
    joueur2->h=100;
    joueur2->w=20;



    //position de départ de la balle, sa taille et sa direction calculée aléatoirement
    balle->milieu.x=SCREEN_WIDTH/2;
    balle->milieu.y=SCREEN_HEIGHT/2;
    balle->direction=rand()%4+1;
    balle->rayon=10;

    return 1;
}



void handleEvents(gameState *state, SDL_Rect *joueur1, SDL_Rect *joueur2, game *myGame){
//BUT: Récupérer les inputs du joueur, set les nouvelles positions des raquettes
//ENTREE: La fenêtre du jeu, les raquettes des joueurs
//SORTIE: Les nouvelles coordonnées des raquettes suite à l'input.
    SDL_Event event;
    Test Pressed=Nothing;


    if(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
              state->g_bRunning=0;break;
        case SDL_KEYDOWN:
                        switch (event.key.keysym.sym)
                            {
                                case SDLK_z:
                                    Pressed=Z;
                                    if ((joueur1->y>=20) && (Pressed==Z)){ //on vérifie que le joueur ne soit pas trop haut et que la touche a bien été appuyée, puis on permet la mise à jour des coordonnées
                                        joueur1->y=joueur1->y-20;
                                    }
                                    break;
                                case SDLK_s:
                                    Pressed=S;
                                    if ((joueur1->y<SCREEN_HEIGHT-100)&&(Pressed==S)){ //on vérifie que le joueur ne soit pas trop bas cette fois, et si la touche a été appuyée.
                                        joueur1->y=joueur1->y+20;
                                    }
                                     break;
                                case SDLK_UP:
                                    Pressed=Up;
                                     if ((joueur2->y>=20)&&(Pressed==Up)){ //pareil qu'au dessus mais pour le joueur 2
                                        joueur2->y=joueur2->y-20;
                                    }
                                     break;
                                case SDLK_DOWN:
                                    Pressed=Down;
                                    if ((joueur2->y<SCREEN_HEIGHT-100)&&(Pressed==Down)){
                                        joueur2->y=joueur2->y+20;
                                    }
                                     break;
                            }
                            break;

        case SDL_KEYUP:;break;

        default:break;

        }
    }


}



void affiche_tout(game *myGame, SDL_Rect joueur1, SDL_Rect joueur2, balle_jeu balle) {
//BUT: Afficher tout les éléments de l'écran.
//ENTREE: On passe les données des raquettes et celles de la balle
//SORTIE: On affiche ces derniers à l'écran.


        //Affichage raquettes
        SDL_SetRenderDrawColor(myGame->g_pRenderer, 0, 0, 0, 255); //on choisi la couleur du pinceau
        SDL_RenderFillRect(myGame->g_pRenderer,&joueur1); //on fabrique les raquettes
        SDL_RenderFillRect(myGame->g_pRenderer,&joueur2);

        affiche_balle(myGame,balle.milieu.x,balle.milieu.y,balle.rayon); //on appelle la fonction qui affiche la balle

        //Affichage RENDERER
        SDL_RenderPresent(myGame->g_pRenderer);
}


void delay(unsigned int frameLimit){
    // Gestion des 60 fps (images/seconde)
    unsigned int ticks = SDL_GetTicks();

    if (frameLimit < ticks)
    {
        return;
    }

    if (frameLimit > ticks + 16)
    {
        SDL_Delay(16);
    }

    else
    {
        SDL_Delay(frameLimit - ticks);
    }
}



void destroy(game *myGame){




    //Destroy texture
    if(myGame->g_texture!=NULL)
            SDL_DestroyTexture(myGame->g_texture);


    //Destroy render
    if(myGame->g_pRenderer!=NULL)
        SDL_DestroyRenderer(myGame->g_pRenderer);


    //Destroy window
    if(myGame->g_pWindow!=NULL)
        SDL_DestroyWindow(myGame->g_pWindow);



}



void affiche_balle(game *myGame,int x0, int y0, int radius)
//BUT: On crée une balle (un cercle dans ce contexte)
//ENTREE: On envoie à la fonction les coordonnées du milieu de la balle, et son rayon
//SORTIE: On permet l'affichage de la balle.
{
    int x = radius;
    int y = 0;
    int pos = 0;

    while (x >= y)
    {
        SDL_RenderDrawPoint(myGame->g_pRenderer,x0+x,y0+y);
        SDL_RenderDrawPoint(myGame->g_pRenderer,x0+y,y0+x);
        SDL_RenderDrawPoint(myGame->g_pRenderer,x0-y,y0+x);
        SDL_RenderDrawPoint(myGame->g_pRenderer,x0-x,y0+y);
        SDL_RenderDrawPoint(myGame->g_pRenderer,x0-x,y0-y);
        SDL_RenderDrawPoint(myGame->g_pRenderer,x0-y,y0-x);
        SDL_RenderDrawPoint(myGame->g_pRenderer,x0+y,y0-x);
        SDL_RenderDrawPoint(myGame->g_pRenderer,x0+x,y0-y);

        y=y+1;
        if (pos <= 0)
        {
            pos += 2*y + 1;
        }
        if (pos > 0)
        {
            x -= 1;
            pos -= 2*x + 1;
        }
    }
}



void deplace_balle(balle_jeu *balle, SDL_Rect joueur1, SDL_Rect joueur2){
//BUT: Mettre à jour les coordonnées de la balle
//ENTREE: Les coordonnées de la balle et celles des raquettes (pour les rebonds)
//SORTIE: Les coordonnées mises à jour de la balle
        //deplacement balle
         if (balle->direction==1){
            balle->milieu.x=balle->milieu.x-2;
            balle->milieu.y=balle->milieu.y-2;
          }else if (balle->direction==2){
            balle->milieu.x=balle->milieu.x+2;
            balle->milieu.y=balle->milieu.y-2;
          }else if (balle->direction==3){
            balle->milieu.x=balle->milieu.x+2;
            balle->milieu.y=balle->milieu.y+2;
          }else if (balle->direction==4){
            balle->milieu.x=balle->milieu.x-2;
            balle->milieu.y=balle->milieu.y+2;
          }

        //rebond contre la raquette du joueur 1
          if ((balle->milieu.x==40+balle->rayon) && ((balle->milieu.y<=joueur1.y+joueur1.h) && (balle->milieu.y>=joueur1.y)) && (balle->direction==1)){
            balle->direction=2;
            }else if ((balle->milieu.x==40+balle->rayon) && ((balle->milieu.y<=joueur1.y+joueur1.h) && (balle->milieu.y>=joueur1.y)) && (balle->direction==4)){
                balle->direction=3;
        //rebond contre la raquette 2 du joueur 2
          }else if ((balle->milieu.x==SCREEN_WIDTH-40-balle->rayon) && ((balle->milieu.y<=joueur2.y+joueur2.h) && (balle->milieu.y>=joueur2.y)) && (balle->direction==3)){
            balle->direction=4;
          }else if ((balle->milieu.x==SCREEN_WIDTH-40-balle->rayon) && ((balle->milieu.y<=joueur2.y+joueur2.h) && (balle->milieu.y>=joueur2.y)) && (balle->direction==2)) {
            balle->direction=1;
          }

          //rebond contre le haut de l'écran
          if (balle->milieu.y==balle->rayon){
            if (balle->direction==1){
              balle->direction=4;
            }else{
              balle->direction=3;
            }
          }

        //rebond contre le bas de l'écran
          if (balle->milieu.y==SCREEN_HEIGHT-balle->rayon){
            if (balle->direction==4){
              balle->direction=1;
            }else{
              balle->direction=2;
            }
          }

         //On reset la balle au milieu et on recalcule sa direction quand un joueur marque un point.
          if (balle->milieu.x==10) {
            balle->milieu.x=SCREEN_WIDTH/2;
            balle->milieu.y=SCREEN_HEIGHT/2;
            balle->direction=rand()%4+1;

         }

          if (balle->milieu.x==SCREEN_WIDTH-10) {
            balle->milieu.x=SCREEN_WIDTH/2;
            balle->milieu.y=SCREEN_HEIGHT/2;
            balle->direction=rand()%4+1;

        }

}











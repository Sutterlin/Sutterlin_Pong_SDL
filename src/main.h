//fichier.h contenant les fonctions et la déclaration des types



typedef struct game{
     SDL_Window *g_pWindow;
     SDL_Renderer *g_pRenderer;
     SDL_Texture *g_texture;
     SDL_Surface *g_surface;
}game;

typedef struct gameState{
    int g_bRunning;
}gameState;

typedef enum Test Test;
enum Test
{
    Z,S,Up,Down,Nothing
};

typedef struct coord{
    int x;
    int y;
}coord;

typedef struct balle_jeu{
    coord milieu;
    int direction;
    int rayon;
}balle_jeu;












void handleEvents(gameState *state, SDL_Rect *joueur1, SDL_Rect *joueur2, game *myGame);
void delay(unsigned int frameLimit);
void destroy(game *myGame);
int init(char *title, int xpos,int ypos,int height, int width,int flags,game *myGame, SDL_Rect *joueur1, SDL_Rect *joueur2,balle_jeu *balle);
void affiche_raquette();
void deplace_balle(balle_jeu *balle, SDL_Rect joueur1, SDL_Rect joueur2);
void affiche_tout(game *myGame, SDL_Rect joueur1, SDL_Rect joueur2, balle_jeu balle);
void deplace_raquette();
void affiche_balle(game *myGame,int x0, int y0, int radius);



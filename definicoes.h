#define SCREEN_W 800
#define SCREEN_H 600

#define TRUE 1
#define FALSE 0
#define ERRO -1

#define STARTED 2
#define PAUSED 3
#define UNPAUSED 4
#define STOPPED 5
#define FRAMES_PER_SECOND 35

#define TRONCOS 6
#define CARROS 6
#define LIFES 3

extern SDL_Surface* screen;
extern Uint32 cor_fundo;
extern int nivel;
extern int score_player;
extern int volume;

typedef struct _SPRITE
{
	SDL_Surface* imagem;
	SDL_Rect posicao;
	int incx, incy;
} SPRITE;

typedef struct _FROG
{
    SPRITE sprite;
    int lifes;
    int score;
}FROG;

typedef struct _TIMER
{
	int startTicks;
	int pausedTicks;
	int status;
	int ticks;
	
}TIMER;

typedef struct _STRING_INPUT
{
	char *input;
	SDL_Surface* text;
}STRING_INPUT;

void menu();

void estagio1();

void estagio2();

void instrucoes();

int check_collision(SDL_Rect A, SDL_Rect B);

SDL_Surface *load_image (char *c);

void update_positions(SPRITE *b);

void apply_surface( SDL_Rect posicao, SDL_Surface* source, SDL_Surface* destination);

void screen_limit(FROG *frog);

void checa_sprite_right(SPRITE *tronco, int dist);

void checa_sprite_left(SPRITE *tronco, int dist);

void load_sprite (SPRITE *sprite, char* nome, int x, int y);

void init();

void startTicks(TIMER *t);

void pauseTicks(TIMER *t);

void unpauseTicks(TIMER *t);

void stopTicks(TIMER *t);

void getTicks ( TIMER *t );

void timeToString (int segundos, char time[6]);

void initTimer(TIMER *t);

void alocarMemoria (SPRITE *pont, int tam);

void initStrings(char tempo[], char lifes[], char score[], char level[]);

void transformaChar(int life, int score1, char lifes[], char score[], char level[]);

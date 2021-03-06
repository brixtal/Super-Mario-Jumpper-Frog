#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "definicoes.h"

extern SDL_Surface* screen;
extern Uint32 cor_fundo;
extern int nivel;
extern int score_player;
extern int volume;

void init()
{
	if (-1 == SDL_Init(SDL_INIT_EVERYTHING))
    {
    	printf("Nao consegui inicializar. SDL error=%s\n", SDL_GetError());
  		exit (ERRO);
  	}

	atexit(SDL_Quit);
	
	if( TTF_Init() == -1 ) 
	{ 
		printf("Nao consegui inicializar texto. SDL error=%s\n", SDL_GetError());
		exit (ERRO); 
	}
	
	if (-1 == Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096)) //inicializar SDL_mixer
	{
		printf("Nao consegui abrir audio. Mixer error = %s\n", Mix_GetError());
  		exit(ERRO);
	}
	
	if (0 == Mix_AllocateChannels(16))
	{
		printf("Nao consegui alocar canais\n");
  		exit(ERRO);
	}

	SDL_WM_SetCaption( "Mario Frog -- Comp 1 -- Vinicius Mendes Kastrup", NULL ); 

}

int check_collision(SDL_Rect A, SDL_Rect B)
{
	
	//If any of the sides from A are outside of B 
	if( (A.y + A.h) <= B.y ) 
	{ 
		return FALSE; 
	} 
	
	if( A.y >= (B.y + B.h) ) 
	{
		return FALSE;
	} 
	
	if( (A.x + A.w) <= B.x ) 
	{ 
		return FALSE; 
	} 
	
	if( A.x >= (B.x + B.w) ) 
	{ 
		return FALSE; 
	} 
	
	//If none of the sides from A are outside B 
	return TRUE;  
}

SDL_Surface *load_image (char *c)
{
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;
	Uint32 colorKey;
	
	loadedImage = IMG_Load(c);
	if (!loadedImage)	
	{
		printf("Nao consegui carregar imagem %s\n", IMG_GetError());
		exit(ERRO);
	}
	
	colorKey = SDL_MapRGB(loadedImage->format, 255, 0, 255);
	
	SDL_SetColorKey( loadedImage, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorKey );
	
	optimizedImage = SDL_DisplayFormat (loadedImage); 
	SDL_FreeSurface (loadedImage);
	
	return optimizedImage;
}

void update_positions(SPRITE *b)
{
	b->posicao.x += b->incx;
	b->posicao.y += b->incy;
}

void apply_surface( SDL_Rect posicao, SDL_Surface* source, SDL_Surface* destination) 
{ 
	SDL_Rect temp; 
	
	temp = posicao;
	
	if ( -1 == (SDL_BlitSurface( source, NULL, destination, &temp )))
	{
		printf("Sem blit. SDL error=%s\n", SDL_GetError());
		exit (ERRO);
	}
} 

void screen_limit(FROG *frog)
{
		if ((frog->sprite.posicao.x + frog->sprite.posicao.w == SCREEN_W) && (frog->sprite.incx == 1))
		{
			frog->sprite.incx = 0;
		}
		if ((frog->sprite.posicao.x == 0) && (frog->sprite.incx == -1))
		{
			frog->sprite.incx = 0;
		}
		
		if (frog->sprite.posicao.x + frog->sprite.posicao.w >= SCREEN_W)
		{
			frog->sprite.posicao.x = SCREEN_W - frog->sprite.posicao.w;			
		}
		
		if (frog->sprite.posicao.x < 0)
		{
			frog->sprite.posicao.x = 0;			
		}
		
		if (frog->sprite.posicao.y + frog->sprite.posicao.h > SCREEN_H)
		{
			frog->sprite.posicao.y = SCREEN_H - frog->sprite.posicao.h;			
		}
		
		if (frog->sprite.posicao.y < 0)
		{
			frog->sprite.posicao.y = 0;			
		}
}

void checa_sprite_right(SPRITE *tronco, int dist)
{
	int i;
	for (i = 0; i < TRONCOS; i++)
	{
		if (i == 0)
		{
			if ((tronco)->posicao.x > SCREEN_W)
			{
				(tronco)->posicao.x = (tronco+TRONCOS-1)->posicao.x - (rand() % dist + 141);
			}
		}
		else
		{
			if ((tronco+i)->posicao.x > SCREEN_W)
			{
				(tronco+i)->posicao.x = (tronco+i-1)->posicao.x - (rand() % dist + 141);
			}
		}	
	}
}

void checa_sprite_left(SPRITE *tronco, int dist)
{
	int i;
	for (i = 0; i < TRONCOS; i++)
	{
		if (i == 0)
		{
			if ((tronco->posicao.x + tronco->posicao.w) < 0)
			{
				tronco->posicao.x = (tronco+TRONCOS-1)->posicao.x + (rand() % dist + 141);
			}
		}
		else
		{
			if (((tronco+i)->posicao.x + (tronco+i)->posicao.w) < 0)
			{
				(tronco+i)->posicao.x = (tronco+i-1)->posicao.x + (rand() % dist + 141);
			}
		}
	}
}

void load_sprite (SPRITE *sprite, char* nome, int x, int y)
{
    sprite->imagem = load_image(nome);
    if (!sprite->imagem)	
    {
        printf("Nao consegui carregar imagem %s\n", nome);  		
        exit(ERRO);
    }	
        
    sprite->posicao.x = x; 
    sprite->posicao.y = y;
    sprite->posicao.w = sprite->imagem->w;
    sprite->posicao.h = sprite->imagem->h;
}

void alocarMemoria (SPRITE *pont, int tam)
{
	pont = (SPRITE *) calloc(tam, sizeof(SPRITE));
    if (!pont)
    {
        printf("Memoria insuficiente!\n");
        exit (ERRO);
    }
}

void initStrings(char tempo[], char lifes[], char score[], char level[])
{
	tempo[0] = 'T';
	tempo[1] = 'E';
	tempo[2] = 'M';
	tempo[3] = 'P';
	tempo[4] = 'O';
	tempo[5] = ':';
	tempo[6] = ' ';
	lifes[0] = 'V';
	lifes[1] = 'I';
	lifes[2] = 'D';
	lifes[3] = 'A';
	lifes[4] = 'S';
	lifes[5] = ':';
	lifes[6] = ' ';
	score[0] = 'S';
	score[1] = 'C';
	score[2] = 'O';
	score[3] = 'R';
	score[4] = 'E';
	score[5] = ':';
	score[6] = ' ';
	level[0] = 'N';
	level[1] = 'I';
	level[2] = 'V';
	level[3] = 'E';
	level[4] = 'L';
	level[5] = ':';
	level[6] = ' ';
}

void transformaChar(int life, int score1, char lifes[], char score[], char level[])
{
	lifes[7] = life + '0';
	lifes[8] = '\0';
	score[7] = (score1/100000) + '0';
	score[8] = ((score1%100000)/10000) + '0';
	score[9] = ((score1%10000)/1000) + '0';
	score[10] = ((score1%1000)/100) + '0';
	score[11] = ((score1%100)/10) + '0';
	score[12] = (score1%10) + '0';
	score[13] = '\0';
	level[7] = nivel + '0';
	level[8] = '\0';
}

/*
	Programa:	frog.c
	Autor:		Vinicius Kastrup
	Descrição:	Jogo frog.
*/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "definicoes.h"

SDL_Surface* screen;
Uint32 cor_fundo;
int nivel;
int score_player;
int volume;

int main(int argc, char** argv) 
{
    int quit = 0;  
	
	nivel = 0;
	
	volume = MIX_MAX_VOLUME/2;
	
	init();
		
	//criar uma janela 800x600x32bits
   	screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
   	if (!screen)
	{
		printf("Nao consegui iniciar modo de video. SDL error=%s\n", SDL_GetError());
  		exit (ERRO);
	}	

	cor_fundo = SDL_MapRGB(screen->format, 255, 255, 255);
	
	while(!quit)
	{
		switch(nivel)
		{
			case 0: menu(); break;
			case 1: estagio1(); break;
			case 2: estagio2();  break;
			case 10: quit = 1; break;
			default: break;
		}
	}
	
	Mix_CloseAudio();
	
	TTF_Quit();
	
	SDL_Quit();

	return 0;
}

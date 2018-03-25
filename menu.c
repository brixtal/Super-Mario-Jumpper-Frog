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

extern SDL_Surface* screen;
extern Uint32 cor_fundo;
extern int nivel;
extern int score_player;
extern int volume;

void menu() 
{
    SDL_Event event; 
    int quit = 0; 
	SDL_Surface* background;
	SDL_Rect temp;
	Mix_Music* music;
	SDL_Surface* menu;
	SPRITE cogumelo;
	int select = 0;
    	
	music = Mix_LoadMUS("teste.mp3");
	if (!music)
	{
		printf("Nao consegui abrir arquivo musica.\n");
  		exit(ERRO);
	}

	load_sprite(&cogumelo, "cogumelo.png", 380, 300);
	
	background = load_image("menu.jpg");
	
	menu = load_image("inicio.jpg");
	
	Mix_PlayMusic(music, -1);
	
	while(!quit)
	{
		while(SDL_PollEvent(&event)) 
		{
			switch(event.type)
			{
				case SDL_QUIT: quit = 1; nivel = 10; break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE: quit = 1; nivel = 10; break;
						case SDLK_UP: 
							if(select > 0)
							{
								select--;
							}
							else
							{
								select = 3;
							}
							break;
						case SDLK_DOWN: 
							if (select < 3)
							{
								select++;
							}
							else
							{
								select = 0;
							}
							break;
						case SDLK_RETURN:
							switch (select)
							{
								case 0: nivel = quit = 1; break;
								case 1: instrucoes(); Mix_PlayMusic(music, -1); break; 
								case 2: select = 3; break;
								case 3: quit = 1; nivel = 10; break;
								default: break;
							}
						case SDLK_a:
							if(volume < (MIX_MAX_VOLUME/2) - 10)
							{
								volume += 10;
								Mix_VolumeMusic(volume);
							}
							break;
						case SDLK_d:
							if (volume > 10)
							{
								volume -= 10;
								Mix_VolumeMusic(volume);
							}
							break;
						case SDLK_s:
							if (volume == 0)
							{
								volume = MIX_MAX_VOLUME/2;
								Mix_VolumeMusic(volume);
							}
							else
							{
								volume = 0;
								Mix_VolumeMusic(volume);
							}
							break;
						default: break;
					}
					break;
				default: break;
			}			
		}
		
		switch(select)
		{
			case 0: cogumelo.posicao.y = 304; break;
			case 1: cogumelo.posicao.y = 352; break;
			case 2: cogumelo.posicao.y = 400; break;
			case 3: cogumelo.posicao.y = 448; break;
			default: break;
		}
		
		if (-1 == SDL_FillRect(screen, NULL, cor_fundo))
		{
			printf("Nao consegui encher o retangulo. SDL error=%s\n", SDL_GetError());
			exit(ERRO);
		}
		
		temp.x = 0;
		temp.y = 0;
		apply_surface(temp, background, screen);

		apply_surface(cogumelo.posicao, cogumelo.imagem, screen);
		
		temp.x = 400;
		temp.y = 300;
		apply_surface(temp, menu, screen);
		
		if (-1 == SDL_Flip(screen))
		{
			printf("Nao consegui fazer flip. SDL error=%s\n", SDL_GetError());
			exit(ERRO);
		}
	}
	
	SDL_FreeSurface(background);
	SDL_FreeSurface(cogumelo.imagem);
	SDL_FreeSurface(menu);
	
	Mix_FreeMusic(music);
}

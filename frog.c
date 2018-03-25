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

int main(int argc, char** argv) 
{
	Uint32 cor_fundo;
    SDL_Event event; 
    int quit = 0; 
	SDL_Surface* screen;
	SDL_Surface* background;
	SDL_Surface* status;
	TTF_Font *font;
	Mix_Music* music;
	int volume = MIX_MAX_VOLUME/2;
	SDL_Color textColor = {0,0,0};
	SPRITE *tronco1, *tronco2, *tronco3, *tronco4;
	SPRITE *carro1, *carro2, *carro3, *carro4;
    FROG frog;
	SDL_Rect temp;
	TIMER timer, fps;
	char tempo[13], lifes[9], score[14];
    int i;
	int n, r, d, m;
	int select = 0;
	int gameover = FALSE;
    
	init();
		
	//criar uma janela 800x600x32bits
   	screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
   	if (!screen)
	{
		printf("Nao consegui iniciar modo de video. SDL error=%s\n", SDL_GetError());
  		exit (ERRO);
	}	

	cor_fundo = SDL_MapRGB(screen->format, 255, 255, 255);
		
	font = TTF_OpenFont( "avantgarde.ttf", 18 );
	if (!font)
	{
		printf("Nao consegui inicializar fonte. SDL erro=%s\n", SDL_GetError());
		return ERRO;
	}
	
	music = Mix_LoadMUS("teste.mp3");
	if (!music)
	{
		printf("Nao consegui abrir arquivo musica.\n");
  		exit(ERRO);
	}
	
	initTimer(&timer);
	initTimer(&fps);
	
	background = load_image("background.jpg");
    
	//alocar memoria
    tronco1 = (SPRITE *) calloc(TRONCOS, sizeof(SPRITE));
    if (!tronco1)
    {
        printf("Memoria insuficiente!\n");
        return ERRO;
    }
	
	tronco2 = (SPRITE *) calloc(TRONCOS, sizeof(SPRITE));
    if (!tronco2)
    {
        printf("Memoria insuficiente!\n");
        return ERRO;
    }
	
	tronco3 = (SPRITE *) calloc(TRONCOS, sizeof(SPRITE));
    if (!tronco3)
    {
        printf("Memoria insuficiente!\n");
        return ERRO;
    }
	
	tronco4 = (SPRITE *) calloc(TRONCOS, sizeof(SPRITE));
    if (!tronco4)
    {
        printf("Memoria insuficiente!\n");
        return ERRO;
    }
	
	carro1 = (SPRITE *) calloc(CARROS, sizeof(SPRITE));
    if (!carro1)
    {
        printf("Memoria insuficiente!\n");
        return ERRO;
    }
	
	carro2 = (SPRITE *) calloc(CARROS, sizeof(SPRITE));
    if (!carro2)
    {
        printf("Memoria insuficiente!\n");
        return ERRO;
    }
	
	carro3 = (SPRITE *) calloc(CARROS, sizeof(SPRITE));
    if (!carro3)
    {
        printf("Memoria insuficiente!\n");
        return ERRO;
    }
	
	carro4 = (SPRITE *) calloc(CARROS, sizeof(SPRITE));
    if (!carro4)
    {
        printf("Memoria insuficiente!\n");
        return ERRO;
    }
    
    srand(time(NULL));
	
	n = m = r = d = 400;
	
    for (i = 0; i < TRONCOS; i++)
    {
		load_sprite((tronco1+i), "tronco.jpg", n, 134);
        
		n = n - (rand() % 600 + 141);
        
        (tronco1+i)->incx = 1; (tronco1+i)->incy = 0;
		
		load_sprite((tronco2+i), "tronco.jpg", r, 186);
		
        r = r + (rand() % 600 + 141);
        
        (tronco2+i)->incx = -1; (tronco2+i)->incy = 0;
		
		load_sprite((tronco3+i), "tronco.jpg", d, 82);
		
        d = d + (rand() % 600 + 141);
        
        (tronco3+i)->incx = -1; (tronco3+i)->incy = 0;
		
		load_sprite((tronco4+i), "tronco.jpg", m, 238);
		
        m = m - (rand() % 600 + 141);
        
        (tronco4+i)->incx = 1; (tronco4+i)->incy = 0;
	}
	
	n = d = m = r = 400;

	for (i = 0; i < CARROS; i++)
    {
		load_sprite((carro1+i), "carro.jpg", n, 342);
        
		n = n - (rand() % 600 + 141);
        
        (carro1+i)->incx = 1; (carro1+i)->incy = 0;
		
		load_sprite((carro2+i), "carro.jpg", r, 394);
		
        r = r + (rand() % 600 + 141);
        
        (carro2+i)->incx = -1; (carro2+i)->incy = 0;
		
		load_sprite((carro3+i), "carro.jpg", d, 446);
		
        d = d - (rand() % 600 + 141);
        
        (carro3+i)->incx = 1; (carro3+i)->incy = 0;
		
		load_sprite((carro4+i), "carro.jpg", m, 498);
		
        m = m + (rand() % 600 + 141);
        
        (carro4+i)->incx = -1; (carro4+i)->incy = 0;
	}

	/* tratando do sapo */
	load_sprite(&frog.sprite, "sapo.jpg", 360, 550);
	
	frog.sprite.incx = 0; frog.sprite.incy = 0;
	frog.lifes = 5;
	frog.score = 0;
	
	/* Iniciar o timer */
	startTicks(&timer);
	startTicks(&fps);
	initStrings(tempo, lifes, score);
	
	/*iniciar musica*/
	Mix_PlayMusic(music, -1);
	
	while(!quit) 
   	{
   		if (gameover == TRUE)
		{
			while(SDL_PollEvent(&event)) 
			{
				switch(event.type)
				{
					case SDL_QUIT: quit = 1; break;
					case SDL_KEYDOWN:
						switch(event.key.keysym.sym)
						{
							case SDLK_ESCAPE: quit = 1; break;
							case SDLK_RIGHT: select = 1; break;
							case SDLK_LEFT: select = 0; break;
							case SDLK_RETURN:
								if (select == 1)
								{
									quit = 1;
								}
								else
								{
									gameover = FALSE;
									frog.lifes = 5; 
									frog.score = 0;
								}
								break;
							default: break;
						}
						break;
					default: break;
				}
				
			}
			if (select == 1)
			{
				status = load_image("quit1.jpg");
				temp.x = 250;
				temp.y = 225;
				apply_surface(temp, status, screen);
				
				if (-1 == SDL_Flip(screen))
				{	
					printf("Nao consegui fazer flip. SDL error=%s\n", SDL_GetError());
					return ERRO;

				}
			}
			else
			{
				status = load_image("quit0.jpg");
				temp.x = 250;
				temp.y = 225;
				apply_surface(temp, status, screen);
				
				if (-1 == SDL_Flip(screen))
				{	
					printf("Nao consegui fazer flip. SDL error=%s\n", SDL_GetError());
					return ERRO;

				}
			}
		}
		else
		{
			while(SDL_PollEvent(&event)) 
			{
				switch(event.type)
				{
					case SDL_QUIT: quit = 1; break;
					case SDL_KEYDOWN:
						switch(event.key.keysym.sym)
						{
							case SDLK_ESCAPE: quit = 1; break;
							case SDLK_UP: frog.sprite.posicao.y -= 52; break;
							case SDLK_DOWN: frog.sprite.posicao.y += 52; break;
							case SDLK_RIGHT: frog.sprite.posicao.x += 52; break;
							case SDLK_LEFT: frog.sprite.posicao.x -= 52; break;
							default: break;
						}
						break;
					default: break;
				}
				
			}
			
			if (frog.lifes == 0)
			{
				gameover = TRUE;
			}
			
			for (i = 0; i < TRONCOS; i++)
			{
				if((check_collision(frog.sprite.posicao, (tronco1+i)->posicao)) == TRUE)
				{
					frog.sprite.posicao.y = (tronco1+i)->posicao.y;
					frog.sprite.incx = (tronco1+i)->incx;
					break;
				}
				if((check_collision(frog.sprite.posicao, (tronco2+i)->posicao)) == TRUE)
				{
					frog.sprite.posicao.y = (tronco2+i)->posicao.y;
					frog.sprite.incx = (tronco2+i)->incx;
					break;
				}
				if((check_collision(frog.sprite.posicao, (tronco3+i)->posicao)) == TRUE)
				{
					frog.sprite.posicao.y = (tronco3+i)->posicao.y;
					frog.sprite.incx = (tronco3+i)->incx;
					break;
				}
				if((check_collision(frog.sprite.posicao, (tronco4+i)->posicao)) == TRUE)
				{
					frog.sprite.posicao.y = (tronco4+i)->posicao.y;
					frog.sprite.incx = (tronco4+i)->incx;
					break;
				}
				if((check_collision(frog.sprite.posicao, (carro1+i)->posicao)) == TRUE)
				{
					frog.sprite.posicao.y = 550;
					frog.sprite.posicao.x = 360;
					frog.lifes--;
					break;
				}
				if((check_collision(frog.sprite.posicao, (carro2+i)->posicao)) == TRUE)
				{
					frog.sprite.posicao.y = 550;
					frog.sprite.posicao.x = 360;
					frog.lifes--;
					break;
				}
				if((check_collision(frog.sprite.posicao, (carro3+i)->posicao)) == TRUE)
				{
					frog.sprite.posicao.y = 550;
					frog.sprite.posicao.x = 360;
					frog.lifes--;
					break;
				}
				if((check_collision(frog.sprite.posicao, (carro4+i)->posicao)) == TRUE)
				{
					frog.sprite.posicao.y = 550;
					frog.sprite.posicao.x = 360;
					frog.lifes--;
					break;
				}
				if ((i == TRONCOS-1) && ((frog.sprite.posicao.y + frog.sprite.posicao.h) < 288) && (frog.sprite.posicao.y > 80))
				{
					frog.sprite.posicao.y = 550;
					frog.sprite.posicao.x = 360;
					frog.sprite.incx = 0;
					frog.lifes--;
					break;
				}
				else
				{
					frog.sprite.incx = 0;
				}
			
			}
			
			checa_sprite_right(tronco1);
			checa_sprite_left(tronco2);
			checa_sprite_left(tronco3);
			checa_sprite_right(tronco4);
			checa_sprite_right(carro1);
			checa_sprite_left(carro2);
			checa_sprite_right(carro3);
			checa_sprite_left(carro4);
			
			/* Nao deixar o frog fugir da tela */
			screen_limit(&frog);
			
			/*Checar se entrou na casa*/
			if (((frog.sprite.posicao.x > 96) && (frog.sprite.posicao.x < 162) && (frog.sprite.posicao.y < 80) && (frog.sprite.posicao.y > 14) ) || ( (frog.sprite.posicao.x > 640) && (frog.sprite.posicao.x < 706) &&  (frog.sprite.posicao.y < 80) && (frog.sprite.posicao.y > 14)))
			{
				frog.sprite.posicao.y = 550;
				frog.sprite.posicao.x = 360;
				frog.score += 1000;
			}
			else if (frog.sprite.posicao.y < 80)
			{
				frog.sprite.posicao.y = 550;
				frog.sprite.posicao.x = 360;
				frog.lifes--;
			}

			/* pequena animacao */
			for (i = 0; i < TRONCOS; i++)
			{
				update_positions(tronco1+i);
				update_positions(tronco2+i);
				update_positions(tronco3+i);
				update_positions(tronco4+i);
				update_positions(carro1+i);
				update_positions(carro2+i);
				update_positions(carro3+i);
				update_positions(carro4+i);
			}
			update_positions(&frog.sprite);
			
			/* limpar a tela */
			if (-1 == SDL_FillRect(screen, NULL, cor_fundo))
				{
					printf("Nao consegui encher o retangulo. SDL error=%s\n", SDL_GetError());
					return ERRO;
				}
			temp.x = 0;
			temp.y = 0;
			apply_surface(temp, background, screen);
			
			/* copiar as imagens */
			for(i = 0; i < TRONCOS; i++)
			{
				apply_surface((tronco1+i)->posicao, (tronco1+i)->imagem, screen);
				apply_surface((tronco2+i)->posicao, (tronco2+i)->imagem, screen);
				apply_surface((tronco3+i)->posicao, (tronco3+i)->imagem, screen);
				apply_surface((tronco4+i)->posicao, (tronco4+i)->imagem, screen);
				apply_surface((carro1+i)->posicao, (carro1+i)->imagem, screen);
				apply_surface((carro2+i)->posicao, (carro2+i)->imagem, screen);
				apply_surface((carro3+i)->posicao, (carro3+i)->imagem, screen);
				apply_surface((carro4+i)->posicao, (carro4+i)->imagem, screen);
			}
			
			apply_surface(frog.sprite.posicao, frog.sprite.imagem, screen);
			
			//Pegar ticks
			getTicks(&timer);
			timeToString(timer.ticks/1000, tempo); 
			
			transformaChar(frog.lifes, frog.score, lifes, score);
			//Render the text 
			//lifes
			status = TTF_RenderText_Solid( font, lifes, textColor ); 
			if(!status) 
			{ 
				printf("Erro escrevendo texto. SDL error=%s\n", SDL_GetError());
				return ERRO;
			}
			temp.x = 10;
			temp.y = 550;
			apply_surface(temp, status, screen);
			//tempo
			status = TTF_RenderText_Solid( font, tempo, textColor ); 
			if(!status) 
			{ 
				printf("Erro escrevendo texto. SDL error=%s\n", SDL_GetError());
				return ERRO;
			}
			temp.x = 600;
			temp.y = 550;
			apply_surface(temp, status, screen);
			//score
			status = TTF_RenderText_Solid( font, score, textColor ); 
			if(!status) 
			{ 
				printf("Erro escrevendo texto. SDL error=%s\n", SDL_GetError());
				return ERRO;
			}
			temp.x = 210;
			temp.y = 550;
			apply_surface(temp, status, screen);
				
			
			if (-1 == SDL_Flip(screen))
			{
				printf("Nao consegui fazer flip. SDL error=%s\n", SDL_GetError());
				return ERRO;

			}
			
			getTicks(&fps);
			if (fps.ticks < 1000/FRAMES_PER_SECOND)
			{
				SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.ticks );
			}
		}

	}
	
	SDL_FreeSurface(frog.sprite.imagem);
	for (i = 0; i < TRONCOS; i++)
	{
		SDL_FreeSurface((tronco1+i)->imagem);
		SDL_FreeSurface((tronco2+i)->imagem);
		SDL_FreeSurface((tronco3+i)->imagem);
		SDL_FreeSurface((tronco4+i)->imagem);
		SDL_FreeSurface((carro1+i)->imagem);
		SDL_FreeSurface((carro2+i)->imagem);
		SDL_FreeSurface((carro3+i)->imagem);
		SDL_FreeSurface((carro4+i)->imagem);
	}
	
	SDL_FreeSurface( status );
	SDL_FreeSurface( background );

	TTF_CloseFont( font ); 
	TTF_Quit();

	Mix_FreeMusic(music);
	Mix_CloseAudio();
	
    SDL_Quit();

    return 0;
}
	

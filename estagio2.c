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

void estagio2() 
{
    SDL_Event event; 
    int quit = 0; 
	SDL_Surface* background;
	SDL_Surface* status;
	TTF_Font *font;
	Mix_Music* music;
	SDL_Color textColor = {0,0,0};
	SPRITE *tronco1, *tronco2, *tronco3, *tronco4;
	SPRITE *carro1, *carro2, *carro3, *carro4;
    FROG frog;
	SDL_Rect temp; 
	SPRITE casa1, casa2, casa3;
	TIMER timer;
	char tempo[13], lifes[9], score[14];
	char level[9];
    int i;
	int n, r, d, m;
	int select = 0;
	int checa_casa1 = FALSE;
	int checa_casa2 = FALSE;
	int checa_casa3 = FALSE;
	int gameover = FALSE;
	int andou_esquerda = 0;
	int andou_direita = 0;
	int andou_frente = 1;
	int exitt = FALSE;
    		
	font = TTF_OpenFont( "avantgarde.ttf", 18 );
	if (!font)
	{
		printf("Nao consegui inicializar fonte. SDL erro=%s\n", SDL_GetError());
		exit (ERRO);
	}
	
	music = Mix_LoadMUS("teste.mp3");
	if (!music)
	{
		printf("Nao consegui abrir arquivo musica.\n");
  		exit(ERRO);
	}
	
	initTimer(&timer);
	
	background = load_image("background2.jpg");
    
	//alocar memoria
    tronco1 = (SPRITE *) calloc(TRONCOS, sizeof(SPRITE));
    if (!tronco1)
    {
        printf("Memoria insuficiente!\n");
        exit (ERRO);
    }
	
	tronco2 = (SPRITE *) calloc(TRONCOS, sizeof(SPRITE));
    if (!tronco2)
    {
        printf("Memoria insuficiente!\n");
        exit (ERRO);
    }
	
	tronco3 = (SPRITE *) calloc(TRONCOS, sizeof(SPRITE));
    if (!tronco3)
    {
        printf("Memoria insuficiente!\n");
        exit (ERRO);
    }
	
	tronco4 = (SPRITE *) calloc(TRONCOS, sizeof(SPRITE));
    if (!tronco4)
    {
        printf("Memoria insuficiente!\n");
        exit (ERRO);
    }
	
	carro1 = (SPRITE *) calloc(CARROS, sizeof(SPRITE));
    if (!carro1)
    {
        printf("Memoria insuficiente!\n");
        exit (ERRO);
    }
	
	carro2 = (SPRITE *) calloc(CARROS, sizeof(SPRITE));
    if (!carro2)
    {
        printf("Memoria insuficiente!\n");
        exit (ERRO);
    }
	
	carro3 = (SPRITE *) calloc(CARROS, sizeof(SPRITE));
    if (!carro3)
    {
        printf("Memoria insuficiente!\n");
        exit (ERRO);
    }
	
	carro4 = (SPRITE *) calloc(CARROS, sizeof(SPRITE));
    if (!carro4)
    {
        printf("Memoria insuficiente!\n");
        exit (ERRO);
    }
    
    srand(time(NULL));
	
	n = m = r = d = 400;
	
    for (i = 0; i < TRONCOS; i++)
    {
		load_sprite((tronco1+i), "tronco.jpg", n, 134);
        
		n = n - (rand() % 700 + 141);
        
        (tronco1+i)->incx = 2; (tronco1+i)->incy = 0;
		
		load_sprite((tronco2+i), "tronco.jpg", r, 186);
		
        r = r + (rand() % 700 + 141);
        
        (tronco2+i)->incx = -2; (tronco2+i)->incy = 0;
		
		load_sprite((tronco3+i), "tronco.jpg", d, 82);
		
        d = d + (rand() % 700 + 141);
        
        (tronco3+i)->incx = -2; (tronco3+i)->incy = 0;
		
		load_sprite((tronco4+i), "tronco.jpg", m, 238);
		
        m = m - (rand() % 700 + 141);
        
        (tronco4+i)->incx = 2; (tronco4+i)->incy = 0;
	}
	
	n = d = m = r = 400;

	for (i = 0; i < CARROS; i++)
    {
		if (i % 3 == 1 || i % 3 == 0)
		{
			load_sprite((carro1+i), "carro.jpg", n, 342);
        }
		else
		{
			load_sprite((carro1+i), "carro2.jpg", n, 342);
        }
		n = n - (rand() % 500 + 141);
        
        (carro1+i)->incx = 2; (carro1+i)->incy = 0;
		
		if (i % 3 == 1 || i % 3 == 0)
		{
			load_sprite((carro2+i), "carro2.jpg", n, 394);
        }
		else
		{
			load_sprite((carro2+i), "carroleft.jpg", n, 394);
        }
		
        r = r + (rand() % 500 + 141);
        
        (carro2+i)->incx = -2; (carro2+i)->incy = 0;
		
		if (i % 3 == 1 || i % 3 == 0)
		{
			load_sprite((carro3+i), "carro2.jpg", n, 446);
        }
		else
		{
			load_sprite((carro3+i), "carro.jpg", n, 446);
        }
		
        d = d - (rand() % 500 + 141);
        
        (carro3+i)->incx = 2; (carro3+i)->incy = 0;
		
		if (i % 3 == 1 || i % 3 == 0)
		{
			load_sprite((carro4+i), "carroleft.jpg", n, 498);
        }
		else
		{
			load_sprite((carro4+i), "carro2.jpg", n, 498);
        }
		
        m = m + (rand() % 500 + 141);
        
        (carro4+i)->incx = -2; (carro4+i)->incy = 0;
	}

	/* tratando do sapo */
	load_sprite(&frog.sprite, "sapofrente0.png", 360, 550);
	
	frog.sprite.incx = 0; frog.sprite.incy = 0;
	frog.lifes = LIFES;
	frog.score = score_player;
	
	/*Casas*/
	load_sprite(&casa1, "frogwin.png", 106, 20);
	load_sprite(&casa2, "frogwin.png", 650, 20);
	load_sprite(&casa3, "frogwin.png", 364, 20);
	
	/* Iniciar o timer */
	startTicks(&timer);
	initStrings(tempo, lifes, score, level);
	
	/*iniciar musica*/
	Mix_PlayMusic(music, -1);
	
	while(!quit) 
   	{
		if (exitt == TRUE)
		{
			while(SDL_PollEvent(&event)) 
			{
				switch(event.type)
				{
					case SDL_KEYDOWN:
						switch(event.key.keysym.sym)
						{
							case SDLK_RIGHT: select = 0; break;
							case SDLK_LEFT: select = 1; break;
							case SDLK_RETURN:
								if (select == 1)
								{
									quit = 1;
									nivel = 10;
								}
								else
								{
									exitt = FALSE;
								}
								break;
							default: break;
						}
						break;
					default: break;
				}
				
			}
			if (select == 0)
			{
				status = load_image("exit1.jpg");
				temp.x = 250;
				temp.y = 225;
				apply_surface(temp, status, screen);
				
				if (-1 == SDL_Flip(screen))
				{	
					printf("Nao consegui fazer flip. SDL error=%s\n", SDL_GetError());
					exit (ERRO);

				}
			}
			else
			{
				status = load_image("exit0.jpg");
				temp.x = 250;
				temp.y = 225;
				apply_surface(temp, status, screen);
				
				if (-1 == SDL_Flip(screen))
				{	
					printf("Nao consegui fazer flip. SDL error=%s\n", SDL_GetError());
					exit (ERRO);

				}
			}
		}
   		else if (gameover == TRUE)
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
							case SDLK_RIGHT: select = 1; break;
							case SDLK_LEFT: select = 0; break;
							case SDLK_RETURN:
								if (select == 1)
								{
									quit = 1;
									nivel = 10;
								}
								else
								{
									quit = 1;
									nivel = 1;
								}
								break;
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
			if (select == 1)
			{
				status = load_image("quit1.jpg");
				temp.x = 250;
				temp.y = 225;
				apply_surface(temp, status, screen);
				
				if (-1 == SDL_Flip(screen))
				{	
					printf("Nao consegui fazer flip. SDL error=%s\n", SDL_GetError());
					exit (ERRO);

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
					exit (ERRO);

				}
			}
		}
		else
		{
			while(SDL_PollEvent(&event)) 
			{
				switch(event.type)
				{
					case SDL_QUIT: exitt = TRUE; break;
					case SDL_KEYDOWN:
						switch(event.key.keysym.sym)
						{
							case SDLK_ESCAPE: exitt = TRUE; break;
							case SDLK_UP: 
								frog.sprite.posicao.y -= 52; 
								if (andou_frente == 1)
								{
									frog.sprite.imagem = load_image("sapofrente1.png");
								}
								else
								{
									frog.sprite.imagem = load_image("sapofrente0.png");
								}
								andou_frente = 1 - andou_frente;
								break;
							case SDLK_DOWN: 
								frog.sprite.posicao.y += 52; 
								if (andou_frente == 1)
								{
									frog.sprite.imagem = load_image("frogbaixo1.png");
								}
								else
								{
									frog.sprite.imagem = load_image("frogbaixo0.png");
								}
								andou_frente = 1 - andou_frente;
								break;
							case SDLK_RIGHT: 
								frog.sprite.posicao.x += 52; 
								frog.sprite.imagem = load_image("pulo1direita.png");
								andou_direita = 1;
								break;
								
							case SDLK_LEFT: 
								frog.sprite.posicao.x -= 52; 
								frog.sprite.imagem = load_image("pulo1esquerda.png");
								andou_esquerda = 1;
								break;
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
			
			switch (andou_esquerda)
			{
				case 0: break;
				case 1: andou_esquerda = 2; break;
				case 2: frog.sprite.imagem = load_image("pulo2esquerda.png"); andou_esquerda = 3; break;
				case 3: frog.sprite.imagem = load_image("frogesquerda.png"); andou_esquerda = 0; break;
				default: break;
			}
			switch (andou_direita)
			{
				case 0: break;
				case 1: andou_direita = 2; break;
				case 2: frog.sprite.imagem = load_image("pulo2direita.png"); andou_direita = 3; break;
				case 3: frog.sprite.imagem = load_image("frogdireita.png"); andou_direita = 0; break;
				default: break;
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
			
			checa_sprite_right(tronco1, 700);
			checa_sprite_left(tronco2, 700);
			checa_sprite_left(tronco3, 700);
			checa_sprite_right(tronco4, 700);
			checa_sprite_right(carro1, 500);
			checa_sprite_left(carro2, 500);
			checa_sprite_right(carro3, 500);
			checa_sprite_left(carro4, 500);
			
			/* Nao deixar o frog fugir da tela */
			screen_limit(&frog);
			
			/*Checar se entrou na casa*/
			if (((frog.sprite.posicao.x > 72) && (frog.sprite.posicao.x < 162) && (frog.sprite.posicao.y < 80) && (frog.sprite.posicao.y > 14) ) && checa_casa1 == FALSE)
			{
				frog.sprite.posicao.y = 550;
				frog.sprite.posicao.x = 360;
				frog.score += 1000;
				checa_casa1 = TRUE;
			}
			if ( ((frog.sprite.posicao.x > 616) && (frog.sprite.posicao.x < 706) &&  (frog.sprite.posicao.y < 80) && (frog.sprite.posicao.y > 14)) && checa_casa2 == FALSE)
			{
				frog.sprite.posicao.y = 550;
				frog.sprite.posicao.x = 360;
				frog.score += 1000;
				checa_casa2 = TRUE;
			}
			if ( ((frog.sprite.posicao.x > 334) && (frog.sprite.posicao.x < 422) &&  (frog.sprite.posicao.y < 80) && (frog.sprite.posicao.y > 14)) && checa_casa3 == FALSE)
			{
				frog.sprite.posicao.y = 550;
				frog.sprite.posicao.x = 360;
				frog.score += 1000;
				checa_casa3 = TRUE;
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
					exit (ERRO);
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
			
			if(checa_casa1 == TRUE)
			{
				apply_surface(casa1.posicao, casa1.imagem, screen);
			}
			if(checa_casa2 == TRUE)
			{
				apply_surface(casa2.posicao, casa2.imagem, screen);
			}
			if(checa_casa3 == TRUE)
			{
				apply_surface(casa3.posicao, casa3.imagem, screen);
			}
			
			//Pegar ticks
			getTicks(&timer);
			timeToString((300 - timer.ticks/1000), tempo);
			if (timer.ticks/1000 == 300)
			{
				gameover = TRUE;
			}
			
			transformaChar(frog.lifes, frog.score, lifes, score, level);
			//Render the text 
			//lifes
			status = TTF_RenderText_Solid( font, lifes, textColor ); 
			if(!status) 
			{ 
				printf("Erro escrevendo texto. SDL error=%s\n", SDL_GetError());
				exit (ERRO);
			}
			temp.x = 10;
			temp.y = 550;
			apply_surface(temp, status, screen);
			//tempo
			status = TTF_RenderText_Solid( font, tempo, textColor ); 
			if(!status) 
			{ 
				printf("Erro escrevendo texto. SDL error=%s\n", SDL_GetError());
				exit (ERRO);
			}
			temp.x = 670;
			temp.y = 550;
			apply_surface(temp, status, screen);
			//score
			status = TTF_RenderText_Solid( font, score, textColor ); 
			if(!status) 
			{ 
				printf("Erro escrevendo texto. SDL error=%s\n", SDL_GetError());
				exit (ERRO);
			}
			temp.x = 130;
			temp.y = 550;
			apply_surface(temp, status, screen);
			//level
			status = TTF_RenderText_Solid( font, level, textColor ); 
			if(!status) 
			{ 
				printf("Erro escrevendo texto. SDL error=%s\n", SDL_GetError());
				exit (ERRO);
			}
			temp.x = 550;
			temp.y = 550;
			apply_surface(temp, status, screen);
				
			
			if (-1 == SDL_Flip(screen))
			{
				printf("Nao consegui fazer flip. SDL error=%s\n", SDL_GetError());
				exit (ERRO);

			}
			
			SDL_Delay( 1000 / FRAMES_PER_SECOND );
			
		}

	}
	
	SDL_FreeSurface(frog.sprite.imagem);
	SDL_FreeSurface(casa1.imagem);
	SDL_FreeSurface(casa2.imagem);
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
	
	free(tronco1);
	free(tronco2);
	free(tronco3);
	free(tronco4);
	free(carro1);
	free(carro2);
	free(carro3);
	free(carro4);
	
	SDL_FreeSurface( status );
	SDL_FreeSurface( background );

	TTF_CloseFont( font ); 
	
	Mix_FreeMusic(music);
}
	

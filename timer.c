#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "definicoes.h"

void initTimer(TIMER *t)
{
	t->startTicks = 0;
	t->pausedTicks = 0;
	t->status = STOPPED;
}

void startTicks(TIMER *t)
{
	t->startTicks = SDL_GetTicks();
	t->status = STARTED;
}

void pauseTicks(TIMER *t)
{	
	if (t->status == STARTED || t->status == UNPAUSED)
	{
		t->pausedTicks = SDL_GetTicks() - t->startTicks;
		t->status = PAUSED;
	}
}

void unpauseTicks(TIMER *t)
{
	if (t->status == PAUSED)
	{
		t->startTicks = SDL_GetTicks() - (t->pausedTicks);
		t->pausedTicks = 0;
		t->status = UNPAUSED;
	}
}

void stopTicks(TIMER *t)
{
	t->startTicks = 0;
	t->status = STOPPED;
}

void getTicks ( TIMER *t )
{
	if (t->status == PAUSED)
	{
		t->ticks = t->pausedTicks;
	}
	else if (t->status == STARTED || t->status == UNPAUSED)
	{
		t->ticks = (SDL_GetTicks() - t->startTicks);
	}
}

void timeToString (int segundos, char time[])
{
	int num[4];
	
	num[0] = (segundos/60)/10;
	num[1] = (segundos/60)%10;
	num[2] = (segundos%60)/10;
	num[3] = (segundos%60)%10;
	time[7] = num[0] + '0';
	time[8] = num[1] + '0';
	time[9] = ':';
	time[10] = num[2] + '0';
	time[11] = num[3] + '0';
	time[12] = '\0';
} 

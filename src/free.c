#include "../includes/doom.h"

static void	freeweapons(t_weapon *weap)
{
	int i;

	i = -1;
	while (i++ < 6)
	{
		if (i < 3)
			Mix_FreeChunk(weap->w_s.block[i]);
		if (i < 4)
			Mix_FreeChunk(weap->w_s.draw[i]);
		if (i < 6)
			Mix_FreeChunk(weap->w_s.swipe[i]);
		SDL_FreeSurface(weap->art[i]);
	}
}

static void	freeart(SDL_Surface *art[64], SDL_Surface *rart[7][8], t_map *map)
{
	int i;
	int j;

	i = -1;
	while (i++ < 63)
	{
		if (art[i])
		SDL_FreeSurface(art[i]);
	}
	i = -1;
	while (i++ < 6)
	{
		j = -1;
		while (j++ < 7)
		{
			if (rart[i][j])
			SDL_FreeSurface(rart[i][j]);
		}		
	}
	freeweapons(&map->weaplst[0]);
	
}

void		freeofdoom(t_param *p)
{
	freeart(p->art, p->ratart, p->map);
}

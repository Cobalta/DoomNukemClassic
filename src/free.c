#include "../includes/doom.h"

static void	freemap(t_map *map)
{
	int i;

	i = 0;
	while (i < map->ctsector)
	{
		free(map->sect[i].wall);
		i++;
	}
	free(map->sect);
	free(map);
}

static void	freeweapons(t_weapon *weap)
{
	int i;

	i = -1;
	while (i++ < 6)
	{
		if (i < 3)
			Mix_FreeChunk(weap->w_s.block[i]);
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
	freemap(p->map);
	SDL_FreeSurface(p->surf);
	SDL_DestroyTexture(p->texture);
	SDL_DestroyRenderer(p->ren);
	SDL_DestroyWindow(p->win);
	free_audio(p->s);
	free(p);
}

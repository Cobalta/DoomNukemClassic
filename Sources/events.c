/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   events.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tprzybyl <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/01 22:08:57 by tprzybyl     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/25 16:44:52 by tprzybyl    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void		acta(SDL_Event *e, t_param *p)
{
	if (e->key.keysym.sym == SDLK_a)
		p->eve.a = (e->key.type == SDL_KEYDOWN) ? 1 : 0;
	else if (e->key.keysym.sym == SDLK_d)
		p->eve.d = (e->key.type == SDL_KEYDOWN) ? 1 : 0;
	else if (e->key.keysym.sym == SDLK_w)
		p->eve.w = (e->key.type == SDL_KEYDOWN) ? 1 : 0;
	else if (e->key.keysym.sym == SDLK_s)
		p->eve.s = (e->key.type == SDL_KEYDOWN) ? 1 : 0;
	else if (e->key.keysym.sym == SDLK_r)
		p->eve.r = (e->key.type == SDL_KEYDOWN) ? 1 : 0;
}

void		drawminimap(t_param *p, t_map *map)
{
	t_dpos			dest;
	int i = 0;
	int j = 0;

	dest.x = p->map->pos.x + 7 * cos(p->map->ang);
	dest.y = p->map->pos.y + 7 * sin(p->map->ang);
	drawline(&map->pos, &dest, p);
	while (i < map->ctsector)
	{
		j = 0;
		while (j < map->sect[i].cwall)
		{
			drawline(&map->sect[i].wall[j].a, &map->sect[i].wall[j].b, p);
			j++;
		}
		i++;
	}
}

void		event_manager(SDL_Event *e, t_param *p)
{
	while (SDL_PollEvent(e))
	{
		if (e->type == SDL_QUIT)
		{
			p->quit--;
			return ;
		}
		acta(e, p);
	}
	if (p->eve.a)
		p->map->ang -= .05;
	if (p->eve.d)
		p->map->ang += .05;
	if (p->eve.w)
	{
		if (checkcolls(p->map, &p->map->sect[p->map->psct - 1], p->map->pos.x + cos(p->map->ang), p->map->pos.y + sin(p->map->ang)))
		{
			p->map->pos.y += sin(p->map->ang);
			p->map->pos.x += cos(p->map->ang);
		}
	}
	if (p->eve.s)
	{
		if (checkcolls(p->map, &p->map->sect[p->map->psct - 1], p->map->pos.x - cos(p->map->ang), p->map->pos.y - sin(p->map->ang)))
		{
			p->map->pos.y -= sin(p->map->ang);
			p->map->pos.x -= cos(p->map->ang);
		}
	}
	if (p->eve.r)
	{
	p->map->pos.y = p->map->basepos.y;
	p->map->pos.x = p->map->basepos.x;
	p->map->ang = p->map->baseang;
	p->map->psct = p->map->basepsct;
	}
	SDL_SetRenderDrawColor(p->ren, 0, 0, 0, 255);
	SDL_RenderClear(p->ren);
	SDL_SetRenderDrawColor(p->ren, 255, 255, 255, 255);
	p->diff = -5000 - p->map->sect[p->map->psct - 1].bot;
}

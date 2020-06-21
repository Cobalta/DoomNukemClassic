/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   videoloop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:30:56 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/12 17:36:59 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		drawminimap(t_param *p, t_map *map, t_dpos dest)
{
	int i = 0;
	int j = 0;
	t_dpos edst;

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
	i = 0;
	while (i < map->centities)
	{
		edst.x = map->entities[i].pos.x + 6*cos(map->entities[i].ang);
		edst.y = map->entities[i].pos.y + 6*sin(map->entities[i].ang);
		drawline(&map->entities[i].pos, &edst, p);
		i++;
	}

}

void			copyentities(t_map *map)
{
	int i;

	i = -1;
	while (i++ < map->centities)
	{
		map->sortentities[i] = map->entities[i];
	}
}

void			orderentities(t_entity *ent, int max, t_dpos pos)
{
	int			i;
	int			go;
	t_entity	tmp;
	t_ipos		speed;

	go = 1;
	while (go)
	{
		go = 0;
		i = -1;
		while (i++ < max - 2)
		{
			if (distent(ent[i].pos, pos) < distent(ent[i + 1].pos, pos))
			{
				go = 1;
				tmp = ent[i];
				ent[i] = ent [i + 1];
				ent[i + 1] = tmp;
			}
		}
	}
}

void			ratartpick(t_param *p, t_entity *ent, int max, t_dpos pos)
{
	int			i;
	double		sideangle;

	i = -1;
	while (i++ < max - 1)
	{
		if (ent[i].type == 1)
		{
			sideangle = fmod((acos((ent[i].pos.x - pos.x) * 1/(distent(ent[i].pos,
									pos)))), 6.2831);
			sideangle = (ent[i].pos.y < pos.y) ? 6.2831 - sideangle : sideangle;
			sideangle -= ent[i].ang;
			sideangle = (sideangle < 0) ? 6.2831 + sideangle : sideangle;
			if (sideangle > .3839 && sideangle <= 1.1693)
				ent[i].art = p->ratart[ent[i].state][7];
			else if (sideangle > 1.1693 && sideangle <= 1.9547)
				ent[i].art = p->ratart[ent[i].state][6];
			else if (sideangle > 1.9547 && sideangle <= 2.7401)
				ent[i].art = p->ratart[ent[i].state][5];
			else if (sideangle > 2.7401 && sideangle <= 3.5255)
				ent[i].art = p->ratart[ent[i].state][4];
			else if (sideangle > 3.5255 && sideangle <= 4.3109)
				ent[i].art = p->ratart[ent[i].state][3];
			else if (sideangle > 4.3109 && sideangle <= 5.0963)
				ent[i].art = p->ratart[ent[i].state][2];
			else if (sideangle > 5.0963 && sideangle <= 5.8817)
				ent[i].art = p->ratart[ent[i].state][1];
			else
				ent[i].art = p->ratart[ent[i].state][0];
		}
	}
}

void	drawsector(t_param *p, int actual, int min, int max, int ans)
{
	int			i;

	i = 0;
	while (i < p->map->sect[actual - 1].cwall)
	{
		p->actual = actual - 1;
		render(p, i,  min, max, ans);
		i++;
	}
	i = 0;
	while (i < p->map->centities)
	{
		if (p->map->sortentities[i].psct == actual)
		{
			renderentities(p, i, actual, min, max);
		}
		i++;
	}
}

void			setypix(t_map *map)
{
	int i;
	int j;
	int ypix;

	i = 0;
	while (i < map->ctsector)
	{
		ypix = 0.0128 * ((map->sect[i].top - map->sect[i].bot));
		j = 0;
		while (j < map->sect[i].cwall)
		{
			if (map->sect[i].wall[j].portal)
			{
				map->sect[i].wall[j].ypix = 0.0128 * ((map->sect[i].top - map->sect[map->sect[i].wall[j].portal - 1].top));
				map->sect[i].wall[j].botypix = 0.0128 * ((map->sect[map->sect[i].wall[j].portal - 1].bot - map->sect[i].bot));
			}
			else
				map->sect[i].wall[j].ypix = ypix;
			j++;
		}
		i++;
	}
}

void			videoloop(t_param *p)
{
	t_dpos		dest;

	p->map->ang = (p->map->ang < .005 && p->map->ang > -.005) ? 0 : p->map->ang;
	setcleanactmap(p);
	ratartpick(p, p->map->entities, p->map->centities, p->map->pos);
	copyentities(p->map);
	orderentities(p->map->sortentities, p->map->centities, p->map->pos);
	setypix(p->map);
	drawsector(p, p->map->psct, 0, WINL, p->map->psct);
	dest.x = p->map->pos.x + 7 * cos(p->map->ang);
	dest.y = p->map->pos.y + 7 * sin(p->map->ang);
	show_hud(p);
	setcolor(&p->col, 255, 255, 255);
	drawminimap(p, p->map, dest);
	SDL_RenderClear(p->ren);
	SDL_DestroyTexture(p->texture);
	p->texture = SDL_CreateTextureFromSurface(p->ren, p->surf);
	SDL_RenderCopy(p->ren, p->texture, NULL, NULL);
	SDL_RenderPresent(p->ren);
	SDL_SetRenderDrawColor(p->ren, 0, 0, 0, 255);
	SDL_RenderClear(p->ren);
	SDL_SetRenderDrawColor(p->ren, 255, 255, 255, 255);
	p->diff = -5000 + p->map->pcrouch - p->map->pz;
}

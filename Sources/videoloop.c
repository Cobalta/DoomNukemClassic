/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   videoloop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:30:56 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/02/20 17:36:34 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		drawminimap(t_param *p, t_map *map, t_dpos dest)
{
	int i = 0;
	int j = 0;

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

double			distent(t_dpos ent, t_dpos pos)
{
	return (sqrt(((ent.x - pos.x)*(ent.x - pos.x)
					+ ((ent.y - pos.y)*(ent.y - pos.y)))));
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

void			videoloop(t_param *p)
{
	t_dpos		dest;
	
	orderentities(p->map->entities, p->map->centities, p->map->pos);
	drawsector(p, p->map->psct, 0, WINL, p->map->psct);
	dest.x = p->map->pos.x + 7 * cos(p->map->ang);
	dest.y = p->map->pos.y + 7 * sin(p->map->ang);
	drawminimap(p, p->map, dest);
	SDL_RenderClear(p->ren);
	SDL_DestroyTexture(p->texture);
	p->texture = SDL_CreateTextureFromSurface(p->ren, p->surf);
	SDL_RenderCopy(p->ren, p->texture, NULL, NULL);
	SDL_RenderPresent(p->ren);
	SDL_SetRenderDrawColor(p->ren, 0, 0, 0, 255);
	SDL_RenderClear(p->ren);
	SDL_SetRenderDrawColor(p->ren, 255, 255, 255, 255);
	p->diff = -5000 - p->map->sect[p->map->psct - 1].bot;
}

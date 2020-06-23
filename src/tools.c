/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:32:28 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/10 17:01:02 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		put_pixel(SDL_Surface *surf, int x, int y, int color)
{
	Uint32	*pixels;

	pixels = (Uint32 *)surf->pixels;
	if (x >= 0 && y >= 0 && x < surf->w && y < surf->h)
		pixels[y * surf->w + x] = color;
}

t_sector	*sectaddr(void *addr, t_map *map)
{
	int i;

	i = 0;
	while (i < map->ctsector)
	{
		if (&map->sect[i] == addr)
			return (&map->sect[i]);
		i++;
	}
	return (0);
}

void		uxgettexturex(t_param *p, t_qdpos *coor, t_dpos ln, t_wall *w)
{
	t_dpos	tup;

	tup.y = (sectaddr(w->sect, p->map)->top + p->diff)
			/ (ln.y - (p->consty + WINH / 2));
	tup.x = ((ln.x - WINL / 2) * tup.y) / -900;
	if (coor->ta.y != coor->tb.y)
		p->dx = w->xpix * (tup.y - coor->ta.y) / (coor->tb.y - coor->ta.y);
	else
		p->dx = w->xpix * (tup.x - coor->ta.x) / (coor->tb.x - coor->ta.x);
	p->dx %= w->art->w;
}

void		xgettexturex(t_param *p, t_qdpos *coor, t_dpos ln, t_wall *w)
{
	t_dpos	tup;

	tup.y = (p->map->sect[p->actual].bot + p->diff)
			/ (ln.y - (p->consty + WINH / 2));
	tup.x = ((ln.x - WINL / 2) * tup.y) / -900;
	if (coor->ta.y != coor->tb.y)
		p->dx = w->xpix * (tup.y - coor->ta.y) / (coor->tb.y - coor->ta.y);
	else
		p->dx = w->xpix * (tup.x - coor->ta.x) / (coor->tb.x - coor->ta.x);
	p->dx %= w->art->w;
}

void		gettexturex(t_param *p, t_qdpos *coor, t_dpos ln, t_wall *w)
{
	t_dpos	tup;

	tup.y = (p->map->sect[p->actual].top + p->diff)
			/ (ln.y - (p->consty + WINH / 2));
	tup.x = ((ln.x - WINL / 2) * tup.y) / -900;
	if (coor->ta.y != coor->tb.y)
		p->dx = w->xpix * (tup.y - coor->ta.y) / (coor->tb.y - coor->ta.y);
	else
		p->dx = w->xpix * (tup.x - coor->ta.x) / (coor->tb.x - coor->ta.x);
	p->dx %= w->art->w;
}

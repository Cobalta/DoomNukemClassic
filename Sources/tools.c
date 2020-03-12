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

#include "doom.h"

void		put_pixel(SDL_Surface *surf, int x, int y, int color)
{
	Uint32	*pixels;

	pixels = (Uint32 *)surf->pixels;
	if (x >= 0 && y >= 0 && x < surf->w && y < surf->h)
		pixels[y * surf->w + x] = color;
}

void		gettexturex(t_param *p, t_qdpos *coor, t_dpos up, t_wall *w)
{
	t_dpos	tup;

	tup.y = (p->map->sect[p->actual].top + p->diff) / (up.y - (p->consty + WINH/2));
	tup.x = ((up.x - WINL/2) * tup.y) / -1000;
	if (coor->ta.y != coor->tb.y)
		p->dx = w->xpix * (tup.y - coor->ta.y)/(coor->tb.y - coor->ta.y);
	else
		p->dx = w->xpix * (tup.x - coor->ta.x)/(coor->tb.x - coor->ta.x);
	p->dx %= w->art->w;
}

void	setcleanactmap(t_param *p)
{
	int i;
	int j;
	i = 0;
	while (i < WINL)
	{
		j = 0;
		while (j < WINH)
		{
			p->actmap[i][j].data = NULL;
			j++;
		}
		i++;
	}
}

int			getwall(int ow, t_sector *os, t_sector *ns)
{
	int i;

	i = 0;
	while (i < ns->cwall)
	{
		if ((ns->wall[i].a.x == os->wall[ow].a.x &&
					ns->wall[i].a.y == os->wall[ow].a.y &&
					ns->wall[i].b.x == os->wall[ow].b.x &&
					ns->wall[i].b.y == os->wall[ow].b.y) ||
				(ns->wall[i].a.x == os->wall[ow].b.x &&
				 ns->wall[i].a.y == os->wall[ow].b.y &&
				 ns->wall[i].b.x == os->wall[ow].a.x &&
				 ns->wall[i].b.y == os->wall[ow].a.y))
			return (i);
		i++;
	}
	error_func(0);
	return (0);
}
//coor->a.x = WINL/2 + (-(amov.x) * 1000 / (amov.y));
//coor->a.y = p->consty + WINH/2 + ((p->map->sect[k].top + p->diff) / (amov.y));

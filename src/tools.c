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

void		setcolor(SDL_Color *col, int r, int g, int b)
{
	col->r = r;
	col->g = g;
	col->b = b;
}

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
	tup.y = (sectaddr(w->sect, p->map)->top + p->diff) / (ln.y - (p->consty + WINH/2));
	tup.x = ((ln.x - WINL/2) * tup.y) / -900;
	if (coor->ta.y != coor->tb.y)
		p->dx = w->xpix * (tup.y - coor->ta.y)/(coor->tb.y - coor->ta.y);
	else
		p->dx = w->xpix * (tup.x - coor->ta.x)/(coor->tb.x - coor->ta.x);
	p->dx %= w->art->w;
}

void		xgettexturex(t_param *p, t_qdpos *coor, t_dpos ln, t_wall *w)
{
	t_dpos	tup;

	tup.y = (p->map->sect[p->actual].bot + p->diff) / (ln.y - (p->consty + WINH/2));
	tup.x = ((ln.x - WINL/2) * tup.y) / -900;
	if (coor->ta.y != coor->tb.y)
		p->dx = w->xpix * (tup.y - coor->ta.y)/(coor->tb.y - coor->ta.y);
	else
		p->dx = w->xpix * (tup.x - coor->ta.x)/(coor->tb.x - coor->ta.x);
	p->dx %= w->art->w;
}

void		gettexturex(t_param *p, t_qdpos *coor, t_dpos ln, t_wall *w)
{
	t_dpos	tup;

	tup.y = (p->map->sect[p->actual].top + p->diff) / (ln.y - (p->consty + WINH/2));
	tup.x = ((ln.x - WINL/2) * tup.y) / -900;
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
	i = -1;
	while (i++ < p->map->centities)
	p->map->entities[i].lock = 1;
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

int				angark(double ang, double relang, double fov)
{
	fov /= 2;
	if (ang + fov >= 6.28 && ((relang >= ang - fov && relang <= 6.28) ||
	(relang >= 0 && relang <= (ang + fov - 6.28))))
		return (1);
	else if (ang - fov <= 0 && ((relang >= 0 && relang <= ang + fov) ||
	(relang >= 6.28 + (ang - fov) && relang <= 6.28)))
		return (1);
	else if (relang >= ang - fov && relang <= ang + fov)
		return (1);
	return (0);
}

double			distentz(t_entity *ent, t_map *map)
{
	double	z;
	double	l;

	z = (ent->pz - map->pz) / 1000;
	l = (sqrt(((ent->pos.x - map->pos.x)*(ent->pos.x - map->pos.x)
					+ ((ent->pos.y - map->pos.y)*(ent->pos.y - map->pos.y)))));
	return (sqrt(l*l + z*z));
}

double			distent(t_dpos ent, t_dpos pos)
{
	return (sqrt(((ent.x - pos.x)*(ent.x - pos.x)
					+ ((ent.y - pos.y)*(ent.y - pos.y)))));
}
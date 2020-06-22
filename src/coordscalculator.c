/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordscalculator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:31:42 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/12 17:40:21 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		ordercoords(t_qdpos *coor)
{
	t_dpos tmp;

	if (coor->a.x > coor->c.x)
	{
		tmp = coor->c;
		coor->c = coor->a;
		coor->a = tmp;
		tmp = coor->d;
		coor->d = coor->b;
		coor->b = tmp;
	}
}

void		getcoor(t_qdpos *coor, t_param *p, int i, int s)
{
	t_dpos		amov;
	t_dpos		bmov;
	t_dpos		zmov;

	amov.x = p->map->sect[s].wall[i].a.x - p->map->pos.x;
	zmov.x = p->map->sect[s].wall[i].a.y - p->map->pos.y;
	bmov.x = p->map->sect[s].wall[i].b.x - p->map->pos.x;
	zmov.y = p->map->sect[s].wall[i].b.y - p->map->pos.y;
	amov.y = amov.x * -cos(p->map->ang) + zmov.x * -sin(p->map->ang);
	bmov.y = bmov.x * -cos(p->map->ang) + zmov.y * -sin(p->map->ang);
	amov.x = amov.x * -sin(p->map->ang) - zmov.x * -cos(p->map->ang);
	bmov.x = bmov.x * -sin(p->map->ang) - zmov.y * -cos(p->map->ang);
	coor->ta = amov;
	coor->tb = bmov;

	if (0 < bmov.y && 0 >= amov.y)
	{
		bmov.x += (amov.x - bmov.x) * (-bmov.y / (amov.y - bmov.y));
		bmov.y = -.001;
	}
	else if (0 < amov.y && 0 >= bmov.y)
	{
		amov.x += (bmov.x - amov.x) * (-amov.y / (bmov.y - amov.y));
		amov.y = -.001;
	}
	coor->a.x = WINL/2 + (-(amov.x) * 900 / (amov.y));
	coor->b.x = coor->a.x;
	coor->a.y = p->consty + WINH/2 + ((p->map->sect[s].top + p->diff) / (amov.y));
	coor->b.y = p->consty + WINH/2 + ((p->map->sect[s].bot + p->diff) / (amov.y));
	coor->c.x = WINL/2 + (-(bmov.x) * 900 / (bmov.y));
	coor->d.x = coor->c.x;
	coor->c.y = p->consty + WINH/2 + ((p->map->sect[s].top + p->diff) / (bmov.y));
	coor->d.y = p->consty + WINH/2 + ((p->map->sect[s].bot + p->diff) / (bmov.y));
	ordercoords(coor);
	if (0 >= amov.y || 0 >= bmov.y)
		coor->go = 1;
	else
		coor->go = 0;
}

void		getentitycoor(t_qdpos *coor, t_param *p, t_entity e, int floor)
{
	t_dpos		amov;
	double		zmov;
	int			diff;

	amov.x = e.pos.x - p->map->pos.x;
	zmov = e.pos.y - p->map->pos.y;
	amov.y = (amov.x * -cos(p->map->ang) + zmov * -sin(p->map->ang));
	amov.x = (amov.x * -sin(p->map->ang) - zmov * -cos(p->map->ang));

	coor->a.x = WINL/2 + (-(amov.x) * 900 / (amov.y));
	coor->a.y = p->consty + WINH/2 + ((e.scale + floor + p->diff) / (amov.y));
	coor->b.y = p->consty + WINH/2 + ((floor + p->diff) / (amov.y));
	coor->c.y = coor->a.y;
	coor->d.y = coor->b.y;
	diff = e.art->w * ((coor->b.y - coor->a.y) / e.art->h) * 0.5;
	coor->c.x = coor->a.x + diff;
	coor->a.x -= diff;
	coor->b.x = coor->a.x;
	coor->d.x = coor->c.x;
	if (0 >= amov.y)
		coor->go = 1;
	else
		coor->go = 0;
}

void	renderentities(t_param *p, int i, int actual, int min, int max)
{
	t_qdpos		coor;

	getentitycoor(&coor, p, p->map->sortentities[i], p->map->sortentities[i].pz);
	if (coor.a.x < max && coor.c.x > min && coor.go)
	{
		coor.min = min;
		coor.max = max;
		wewillbuildanentity(&coor, p, &p->map->sortentities[i]);
	}
}

void		render(t_param *p, int i, int min, int max, int ans)
{
	t_qdpos		coor;
	t_qdpos		newcoor;

	getcoor(&coor, p, i, p->actual);
	if (coor.a.x < max && coor.c.x > min && coor.go)
	{
		coor.min = min;
		coor.max = max;
		if (p->map->sect[p->actual].wall[i].portal && p->map->sect[p->actual].wall[i].portal != ans)
		{
			ans = p->actual + 1;
			drawsector(p, p->map->sect[p->actual].wall[i].portal,(coor.a.x < min)
			? min : (int)coor.a.x, (coor.c.x > max)? max : (int)coor.c.x, ans);
			getcoor(&newcoor, p, getwall(i, &p->map->sect[ans - 1], &p->map->sect[p->actual]), p->map->sect[ans - 1].wall[i].portal - 1);
			wewillbuildaportal(coor, p, newcoor, &p->map->sect[ans - 1].wall[i]);
		}
		else if (p->map->sect[p->actual].wall[i].portal != ans)
			wewillbuildawall(&coor, p, &p->map->sect[p->actual].wall[i]);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordscalculator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <tprzybyl@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:31:42 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/06/25 20:08:40 by tprzybyl         ###   ########.fr       */
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

void		assigncoor(t_param *p, t_dpos amov, t_dpos bmov, t_qdpos *coor)
{
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
	coor->a.x = WINL / 2 + (-(amov.x) * 900 / (amov.y));
	coor->b.x = coor->a.x;
	coor->a.y = p->consty + WINH / 2 +
				((p->map->sect[coor->go].top + p->diff) / (amov.y));
	coor->b.y = p->consty + WINH / 2 +
				((p->map->sect[coor->go].bot + p->diff) / (amov.y));
	coor->c.x = WINL / 2 + (-(bmov.x) * 900 / (bmov.y));
	coor->d.x = coor->c.x;
	coor->c.y = p->consty + WINH / 2 +
				((p->map->sect[coor->go].top + p->diff) / (bmov.y));
	coor->d.y = p->consty + WINH / 2 +
				((p->map->sect[coor->go].bot + p->diff) / (bmov.y));
	ordercoords(coor);
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
	coor->go = s;
	assigncoor(p, amov, bmov, coor);
	if (0 >= amov.y || 0 >= bmov.y)
		coor->go = 1;
	else
		coor->go = 0;
}

void		getentitycoor(t_qdpos *coor, t_param *p, t_entity e, int i)
{
	t_dpos		amov;
	double		zmov;
	int			diff;

	amov.x = e.pos.x - p->map->pos.x;
	zmov = e.pos.y - p->map->pos.y;
	amov.y = (amov.x * -cos(p->map->ang) + zmov * -sin(p->map->ang));
	amov.x = (amov.x * -sin(p->map->ang) - zmov * -cos(p->map->ang));
	coor->a.x = WINL / 2 + (-(amov.x) * 900 / (amov.y));
	coor->a.y = p->consty + WINH / 2 + ((e.scale + i + p->diff) / (amov.y));
	coor->b.y = p->consty + WINH / 2 + ((i + p->diff) / (amov.y));
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

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

void		entaccel(t_entity *ent, int y, int x)
{
	if (y)
		ent->speed.y += (ent->speed.y == ent->maxspeed) ? y : 1 + y;
	if (ent->speed.y != 0)
	{
		ent->speed.y += (ent->speed.y > 0) ? -1 : 1;
	}
	if (x)
		ent->speed.x += (ent->speed.x == ent->maxspeed) ? x : 1 + x;
	if (ent->speed.x != 0)
	{
		ent->speed.x += (ent->speed.x > 0) ? -1 : 1;
	}
}

void		behavewander(t_entity *ent, int id)
{
	static int timer[256];
	static int wtimer[256];

	if (!timer[id])
	{
		timer[id] = rand() % 400;
		wtimer[id] = rand() % 60 + 20;
	}
	else
	{
		timer[id]--;
		wtimer[id] = (wtimer[id] > 0) ? wtimer[id] -= 1 : 0;
	}
	printf("id = %d , timer/wtimer for id = %d, %d ang %f, tgtang %f\n", id, timer[id], wtimer[id], ent->ang, ent->tgtang);
	if (!timer[id])
		ent->tgtang = (double)(rand() % 628) / 100;
	if (wtimer[id])
		entaccel(ent, 1, 0);
	else
		entaccel(ent, 0, 0);
}

void			entitymovement(t_param *p, t_entity *ent, int id)
{
	static int timer[256];

	timer[id] = (!timer[id]) ? 6 : timer[id];
	ent->ang += (ent->ang > ent->tgtang) ? -.05 : .05;
	if (ent->speed.y != 0)
	{
		if (aicheckcolls(p->map, ent, ent->pos.x
					+ ent->speed.y * .20 * cos(ent->ang),
					ent->pos.y + ent->speed.y * .20 * sin(p->map->ang)))
		{
			timer[id]--;
			if (!timer[id])
				ent->state = (ent->state != 1) ? 1 : 2;
			ent->pos.y += ent->speed.y * .20 * sin(ent->ang);
			ent->pos.x += ent->speed.y * .20 * cos(ent->ang);
		}
	}
	else
		ent->state = 0;
	if (ent->speed.x != 0)
	{
		if (aicheckcolls(p->map, ent, ent->pos.x
					+ ent->speed.x * .20 * sin(ent->ang),
					ent->pos.y - ent->speed.x * .20 * cos(ent->ang)))
		{
			ent->pos.y -= ent->speed.x * .20 * cos(ent->ang);
			ent->pos.x += ent->speed.x * .20 * sin(ent->ang);
		}
	}
}

void		ai(t_param *p)
{
	int i;

	i = -1;
	while (i++ < p->map->centities - 1)
	{
		if (p->map->entities[i].type == 1)
		{
			//if (p->map->ent[i].spot == 1)
			//behaviormove
			//else
			behavewander(&p->map->entities[i], i);
		}
		entitymovement(p, &p->map->entities[i], i);
	}
}

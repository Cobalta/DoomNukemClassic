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
		wtimer[id] = rand() % 60;
	}
	else
	{
		timer[id]--;
		wtimer[id] = (wtimer[id] > 0) ? wtimer[id] -= 1 : 0;
	}
	if (!timer[id])
		ent->tgtang = (double)(rand() % 628) / 100;
	if (wtimer[id])
		entaccel(ent, 1, 0);
	else
		entaccel(ent, 0, 0);
}

void		behavespot(t_entity *ent, int id, t_map *map)
{
	if (distent(map->pos, ent->pos) < 30)
		ent->spot = 1;
}

int		pathfinding(t_entity *ent, t_map *map, t_sector sct, int rec)
{
	int			i;
	double		fact;

	i = -1;
//	fact = 1/(rand() % 99 + 1);
	fact = .5;
	while (i++ < sct.cwall - 1)
	{
		if (sct.wall[i].portal == map->psct && sct.wall[i].portal != rec)
		{
			if (rec)
				return (1);
			else
			{
				ent->tgtpos.x = sct.wall[i].a.x + (sct.wall[i].b.x - sct.wall[i].a.x) * fact;
				ent->tgtpos.y = sct.wall[i].a.y + (sct.wall[i].b.y - sct.wall[i].a.y) * fact;
				return (1);
			}
		}
	}
	i = -1;
	while (i++ < sct.cwall - 1)
	{
		if (sct.wall[i].portal && sct.wall[i].portal != rec)
		{
			if (pathfinding(ent,map, map->sect[sct.wall[i].portal - 1], sct.id))
			{
				if (rec)
					return (1);
				else
				{
					ent->tgtpos.x = sct.wall[i].a.x + (sct.wall[i].b.x - sct.wall[i].a.x) * fact;
					ent->tgtpos.y = sct.wall[i].a.y + (sct.wall[i].b.y - sct.wall[i].a.y) * fact;
					return (1);
				}
			}
		}
	}
	return (0);
}

void		behavemove(t_entity *ent, int id, t_map *map)
{
	if (ent->psct == map->psct)
		ent->tgtpos = map->pos;
	else
		pathfinding(ent, map, map->sect[ent->psct -1], 0);
	ent->tgtang = fmod((acos((ent->tgtpos.x - ent->pos.x ) * 1/(distent(ent->pos,
							ent->tgtpos)))), 6.2831);
	ent->tgtang = (ent->pos.y < ent->tgtpos.y) ? ent->tgtang : 6.2831 - ent->tgtang;
	(distent(map->pos, ent->pos) > 10) ? entaccel(ent, 1, 0) : entaccel(ent, 0, 0);
}

void			entitymovement(t_param *p, t_entity *ent, int id)
{
	static int timer[256];

	timer[id] = (!timer[id]) ? 6 : timer[id];
	if (fabs(ent->ang - ent->tgtang) < 3.14)
		ent->ang += (ent->ang > ent->tgtang) ? -ent->rotspeed : ent->rotspeed;
	else 
		ent->ang += (ent->ang > ent->tgtang) ? ent->rotspeed : -ent->rotspeed;
	ent->ang -= (ent->ang > 6.14) ? 6.14 : 0;
	ent->ang += (ent->ang < 0) ? 6.14 : 0;
	if (ent->speed.y != 0)
	{
		if (aicheckcolls(p->map, ent,
		ent->pos.x + ent->speed.y * .20 * cos(ent->ang),
		ent->pos.y + ent->speed.y * .20 * sin(ent->ang)))
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
		if (aicheckcolls(p->map, ent, 
		ent->pos.x + ent->speed.x * .20 * sin(ent->ang),
		ent->pos.y - ent->speed.x * .20 * cos(ent->ang)))
		{
			ent->pos.y -= ent->speed.x * .20 * cos(ent->ang);
			ent->pos.x += ent->speed.x * .20 * sin(ent->ang);
		}
	}
/*
	if (ent->speed.y != 0)
	{
		if (aicheckcolls(p->map, ent,
					ent->pos.x + ent->speed.y * .20 * cos(ent->ang),
					ent->pos.y + ent->speed.y * .20 * sin(ent->ang)))
		{
			timer[id]--;
			if (!timer[id])
				ent->state = (ent->state != 1) ? 1 : 2;
				printf("moving! %f-%f INTO %f-%f\n",ent->pos.x,ent->pos.y,ent->pos.x += ent->speed.y * .20 * cos(ent->ang),ent->pos.y + ent->speed.y * .20 * sin(ent->ang));
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
	}*/
}

void		ai(t_param *p)
{
	int i;

	i = -1;
	while (i++ < p->map->centities - 1)
	{
		if (p->map->entities[i].type == 1)
		{
			if (p->map->entities[i].spot)
				behavemove(&p->map->entities[i], i, p->map);
			else
			{
				behavespot(&p->map->entities[i], i, p->map);
				behavewander(&p->map->entities[i], i);
			}
		}
		entitymovement(p, &p->map->entities[i], i);
	}
}

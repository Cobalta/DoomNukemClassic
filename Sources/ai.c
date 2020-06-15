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

void		ratsspacing(t_entity *ent, t_map *map)
{
	int		i;
	double	ang;

	i = 0;
	while (i < map->centities)
	{
		if (ent != &map->entities[i] && distent(ent->pos, map->entities[i].pos) < 3 && map->entities[i].type == 1)
		{
			ang = fmod((acos((ent->pos.x - map->entities[i].pos.x) * 1/(distent(ent->pos,
									map->entities[i].pos)))), 6.2831);
			ang = (map->entities[i].pos.y < ent->pos.y) ? ang : 6.2831 - ang;
			ang -= ent->ang;
			entaccel(ent, 3 * cos(ang), 3 * -sin(ang));
		}
		i++;
	}
	if (distent(ent->pos, map->pos) < 5)
	{
		ang = fmod((acos((map->pos.x - ent->pos.x) * 1/(distent(ent->pos,
								map->pos)))), 6.2831);
		ang = (ent->pos.y < map->pos.y) ? ang : 6.2831 - ang;
		ang -= ent->ang;
		entaccel(ent, 3 * -cos(ang), 3 * sin(ang));
	}
}

void		entaccel(t_entity *ent, int y, int x)
{
	if (y)
		ent->speed.y += (ent->speed.y >= ent->maxspeed + ent->boost) ? y : 1 + y;
	if (ent->speed.y != 0)
	{
		ent->speed.y += (ent->speed.y > 0) ? -1 : 1;
	}
	if (x)
		ent->speed.x += (ent->speed.x >= ent->maxspeed + ent->boost) ? x : 1 + x;
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
	double		tgt;
	double		dist;

	dist = distent(map->pos, ent->pos);
	tgt = fmod((acos((map->pos.x - ent->pos.x ) * 1/(distent(ent->pos,
							map->pos)))), 6.2831);
	tgt = (ent->pos.y < map->pos.y) ? tgt : 6.2831 - tgt;
	if ((dist < 60 && angark(ent->ang, tgt, 2)) || dist < 20)
	{
		ent->spot = 1;
		ent->maxspeed += 2;
	}
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
	(distent(map->pos, ent->pos) > 8) ? entaccel(ent, 1, 0) : entaccel(ent, 0, 0);
}

void		behaverecover(t_entity *ent, int id, t_map *map, int t)
{
	static int timer[256];

	if (t)
	{
		ent->state = 5;
		if (!timer[id])
			ent->rotspeed *= -1;
		timer[id] = t + 1;
		ent->boost = 0;
	}
	entaccel(ent, 0, 0);
	//			printf("recovering.. T=%d ID=%d  %d loops left\n", t,id, timer[id]);
	timer[id]--;
	if (!timer[id])
	{
		if (ent->hp > 0)
		{
			ent->state = 0;
			ent->rotspeed *= -1;
		}
		else
			ent->state = 6;
	}
}

void		ratstrike(t_entity *ent, t_map *map)
{
	double		tgt;
	double		dist;

	dist = distent(map->pos, ent->pos);
	tgt = fmod((acos((map->pos.x - ent->pos.x ) * 1/(distent(ent->pos,
							map->pos)))), 6.2831);
	tgt = (ent->pos.y < map->pos.y) ? tgt : 6.2831 - tgt;
	if (dist <= 10 && angark(ent->ang, tgt, 0.5))
	{
		printf("hp %d defence = %d\n", map->hp, map->defence);
		if (map->status > 4 && map->defence > 0)
		{
			printf("boink!\n");
			map->defence -= (angark(map->ang, tgt, 3)) ? 1 : 2;
			defregen(map, 20);
		}
		else
		{
		map->status = (map->status = 5) ? 4 : map->status;
			map->hp -= 5;
		}
	}
}

void		behaveattack(t_entity *ent, int id, t_map *map)
{
	static int timer[256];

	if (distent(map->pos, ent->pos) <= 10 && !timer[id] && angark(ent->ang, ent->tgtang, .5))
	{
		timer[id] = 20;
		ent->rotspeed *= .5;
		ent->boost = 2;
	}
	(timer[id] == 5) ? ratstrike(ent,map) : 0;
	(timer[id] == 5) ? ent->boost = 0 : 0;
	if (timer[id] > 5)
		ent->state = 3;
	else if (timer[id] > 0)
		ent->state = 4;
	if (timer[id])
	{
		timer[id]--;
		if (!timer[id])
		{
			ent->rotspeed *= 2;
			ent->state = 0;
		}
	}
}

void			entitymovement(t_param *p, t_entity *ent, int id)
{
	static int timer[256];

	timer[id] = (!timer[id]) ? 6 : timer[id];
	if (ent->rotspeed > 0)
	{
		if (fabs(ent->ang - ent->tgtang) < 3.14 && 
				fabs(ent->ang - ent->tgtang) > ent->rotspeed)
			ent->ang += (ent->ang > ent->tgtang) ? -ent->rotspeed : ent->rotspeed;
		else if (fabs(ent->ang - ent->tgtang) > ent->rotspeed)
			ent->ang += (ent->ang > ent->tgtang) ? ent->rotspeed : -ent->rotspeed;
		ent->ang -= (ent->ang > 6.14) ? 6.14 : 0;
		ent->ang += (ent->ang < 0) ? 6.14 : 0;
	}
	if (ent->speed.y != 0)
	{
		if (aicheckcolls(p->map, ent,
					ent->pos.x + ent->speed.y * .20 * cos(ent->ang),
					ent->pos.y + ent->speed.y * .20 * sin(ent->ang)))
		{
			timer[id]--;
			if (!timer[id] && ent->state < 3)
				ent->state = (ent->state != 1) ? 1 : 2;
			ent->pos.y += ent->speed.y * .20 * sin(ent->ang);
			ent->pos.x += ent->speed.y * .20 * cos(ent->ang);
		}
	}
	else if (ent->state < 3)
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
}

void		spawnrat(t_entity *ent, t_param *p, int id)
{
	static int	timer[256];

	if (ent->hp <= 0)
	{
		ent->state = 1;
		ent->art = p->art[21];
	}
	if (!timer[id] && p->map->centities < 256)
	{
		timer[id] = 5 * distent(p->map->pos, ent->pos) + (rand() % 200) ;
		p->map->entities[p->map->centities].pos.x = ent->pos.x;
		p->map->entities[p->map->centities].pos.y = ent->pos.y;
		p->map->entities[p->map->centities].ang = (double)(rand() % 628) / 100;
		p->map->entities[p->map->centities].tgtang =
		p->map->entities[p->map->centities].ang;
		p->map->entities[p->map->centities].psct = ent->psct;
		p->map->entities[p->map->centities].scale = 5000;
		p->map->entities[p->map->centities].type = 1;
		p->map->entities[p->map->centities].hp = 100;
		p->map->entities[p->map->centities].maxspeed = 4;
		p->map->entities[p->map->centities].pz = p->map->sect[ent->psct - 1].bot;
		p->map->entities[p->map->centities].speed.x = 0;
		p->map->entities[p->map->centities].speed.y = 0;
		p->map->entities[p->map->centities].boost = 0;
		p->map->entities[p->map->centities].state = 0;
		p->map->entities[p->map->centities].maxspeed = 2;
		p->map->entities[p->map->centities].rotspeed = .15;
		p->map->entities[p->map->centities].addr =
			&p->map->entities[p->map->centities];
		p->map->centities += 1;
	}
	else
		timer[id]--;
}

void		ai(t_param *p)
{
	int i;

	i = -1;
	while (i++ < p->map->centities - 1)
	{
		if (p->map->entities[i].type == 21)
//			printf("%x %d rhole %d, state %d!\n", p->map->entities[i].addr ,p->map->entities[i].type, p->map->entities[i].hp,p->map->entities[i].state);
		if (p->map->entities[i].type == 21 && !p->map->entities[i].state)
		{
			spawnrat(&p->map->entities[i], p, i);
		}
		if (p->map->entities[i].type == 1 && p->map->entities[i].state != 6)
		{
			//			printf("%d is state %d and SPOOD (%d + %d)\n ", i, p->map->entities[i].state,p->map->entities[i].maxspeed,p->map->entities[i].boost);
			if (p->map->entities[i].state == 5)
				//			{printf("recovering\n");
				behaverecover(&p->map->entities[i], i, p->map, 0);
			else if (p->map->entities[i].spot)
			{
				//			printf("moving and attacking\n");
				behavemove(&p->map->entities[i], i, p->map);
				behaveattack(&p->map->entities[i], i, p->map);
			}
			else
			{
				//			printf("clueless\n");
				behavespot(&p->map->entities[i], i, p->map);
				behavewander(&p->map->entities[i], i);
			}
			ratsspacing(&p->map->entities[i], p->map);
			entcollision(&p->map->entities[i], i, p->map);
			entitymovement(p, &p->map->entities[i], i);
		}
		}
		//		printf("//////////////\n");
	}

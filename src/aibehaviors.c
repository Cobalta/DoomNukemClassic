
#include "../includes/doom.h"

void		behavewander(t_entity *ent, int id)
{
	static int	timer[512];
	static int	wtimer[512];

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
		entaccel(ent, 1, 0, 0);
	else
		entaccel(ent, 0, 0, 0);
}

void		behavespot(t_entity *ent, t_map *map)
{
	double		tgt;
	double		dist;

	dist = distent(map->pos, ent->pos);
	tgt = fmod((acos((map->pos.x - ent->pos.x) * 1
	/ (distent(ent->pos, map->pos)))), 6.2831);
	tgt = (ent->pos.y < map->pos.y) ? tgt : 6.2831 - tgt;
	if (((dist < 70 && angark(ent->ang, tgt, 2)) || dist < 20))
	{
		if (checklos(ent, map))
			return ;
		ent->spot = 1;
		ent->maxspeed += 2;
	}
}

void		behavemove(t_entity *ent, t_map *map)
{
	if (ent->psct == map->psct)
		ent->tgtpos = map->pos;
	else
		pthfind(ent, map, &map->sect[ent->psct - 1], 0);
	abssectids(map);
	ent->tgtang = fmod((acos((ent->tgtpos.x - ent->pos.x) * 1
	/ (distent(ent->pos, ent->tgtpos)))), 6.2831);
	ent->tgtang = (ent->pos.y < ent->tgtpos.y) ?
	ent->tgtang : 6.2831 - ent->tgtang;
	(distent(map->pos, ent->pos) > 8) ?
	entaccel(ent, 1, 0, 0) : entaccel(ent, 0, 0, 0);
}

void		behaverecover(t_entity *ent, int id, t_param *p, int t)
{
	static int	timer[512];

	if (t)
	{
		ent->state = 5;
		if (!timer[id])
			ent->rotspeed *= -1;
		timer[id] = t + 1;
		ent->boost = 0;
		if (ent->hp <= 0)
		{
			Mix_PlayChannel(-1, p->s.skaven[2], 0);
			ent->state = 6;
			return ;
		}
		else
			behaveaudio(p, 5);
	}
	entaccel(ent, 0, 0, 0);
	timer[id]--;
	if (!timer[id])
	{
		ent->state = 0;
		ent->rotspeed *= -1;
	}
}

void		behaveattack(t_entity *ent, int id, t_param *p)
{
	static int	timer[512];

	if (distentz(ent, p->map) <= 10 && !timer[id]
	&& angark(ent->ang, ent->tgtang, .5))
	{
		timer[id] = 25;
		ent->rotspeed *= .5;
		ent->boost = 2;
		behaveaudio(p, 3);
	}
	(timer[id] == 5) ? ratstrike(ent, p) : 0;
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

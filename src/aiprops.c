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

#include "../includes/doom.h"

static void	spawnrat(t_entity *ent, t_entity *dst, int bot)
{
	dst->pos.x = ent->pos.x;
	dst->pos.y = ent->pos.y;
	dst->ang = (double)(rand() % 628) / 100;
	dst->tgtang =
	dst->ang;
	dst->psct = ent->psct;
	dst->scale = 5000;
	dst->type = 1;
	dst->hp = 100;
	dst->maxspeed = 1;
	dst->pz = bot + 250;
	dst->speed.x = 0;
	dst->speed.y = 0;
	dst->speed.z = 0;
	dst->boost = 0;
	dst->spot = 0;
	dst->state = 0;
	dst->maxspeed = 2;
	dst->rotspeed = .15;
	dst->addr = dst;
}

void		burrow(t_entity *ent, t_param *p, int id)
{
	static int	timer[512];

	if (ent->hp <= 0)
	{
		ent->state = 1;
		ent->art = p->art[21];
	}
	if (!timer[id] && p->map->centities < 511)
	{
		spawnrat(ent, &p->map->entities[p->map->centities],
		p->map->sect[ent->psct - 1].bot);
		timer[id] = (6 - p->diflvl) *
		(distent(p->map->pos, ent->pos) + (rand() % (600 / p->diflvl)));
		p->map->centities += 1;
	}
	else
		timer[id]--;
}

void		lever(t_entity *e, t_map *map)
{
	t_sector *s;

	s = &map->sect[e->lever.z - 1];
	if (e->state == 1)
	{
		if (s->bot > e->lever.y)
			s->bot = (s->bot - e->lever.y > 250) ? s->bot - 250 : e->lever.y;
		else if (s->bot < e->lever.y)
			s->bot = (e->lever.y - s->bot < 250) ? e->lever.y : s->bot + 250;
		if (s->top > e->lever.x)
			s->top = (s->top - e->lever.x > 250) ? s->top - 250 : e->lever.x;
		else if (s->top < e->lever.x)
			s->top = (e->lever.x - s->top < 250) ? e->lever.x : s->top + 250;
	}
	else if (!s->levs)
	{
		if (s->bot > s->bbot)
			s->bot = (s->bot - s->bbot > 250) ? s->bot - 250 : s->bbot;
		else if (s->bot < s->bbot)
			s->bot = (s->bbot - s->bot < 250) ? s->bbot : s->bot + 250;
		if (s->top > s->btop)
			s->top = (s->top - s->btop > 250) ? s->top - 250 : s->btop;
		else if (s->top < s->btop)
			s->top = (s->btop - s->top < 250) ? s->btop : s->top + 250;
	}
}

void		adrenaline(t_entity *ent, t_param *p)
{
	if (distentz(ent, p->map) < 2)
	{
		ent->type = -15;
		ent->art = p->art[60];
		p->map->power = 1;
		Mix_PlayChannel(-1, p->s.player[2], 0);
	}
}

void		potion(t_entity *ent, t_param *p)
{
	if (distentz(ent, p->map) < 2 && p->map->hp < 100)
	{
		ent->type = -10;
		ent->art = p->art[23];
		if (p->map->hp > 50)
			p->map->hp = 100;
		else
			p->map->hp += 50;
	}
}

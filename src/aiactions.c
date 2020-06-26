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

static void		socialspacing(t_entity *ent, t_entity *rat)
{
	double dist;
	double ang;

	dist = distent(ent->pos, rat->pos);
	dist = (!dist) ? 1 : dist;
	ang = fmod((acos((ent->pos.x - rat->pos.x) *
	1 / dist)), 6.2831);
	ang = (rat->pos.y < ent->pos.y) ? ang : 6.2831 - ang;
	ang -= ent->ang;
	entaccel(ent, 3 * cos(ang), 3 * -sin(ang), 0);
}

void			ratsspacing(t_entity *ent, t_map *map)
{
	int		i;
	double	ang;
	double	dist;

	i = 0;
	while (i < map->centities)
	{
		if (ent != &map->entities[i] && distent(ent->pos, map->entities[i].pos)
		< 3 && map->entities[i].type == 1 && map->entities[i].state != 6)
			socialspacing(ent, &map->entities[i]);
		i++;
	}
	if (distentz(ent, map) < 5 && ent->state < 5)
	{
		dist = distentz(ent, map);
		dist = (!dist) ? 1 : dist;
		ang = fmod((acos((map->pos.x - ent->pos.x) * 1 / dist)), 6.2831);
		ang = (ent->pos.y < map->pos.y) ? ang : 6.2831 - ang;
		ang -= ent->ang;
		entaccel(ent, 3 * -cos(ang), 3 * sin(ang), 0);
	}
	if (map->sect[ent->psct - 1].bot >= map->sect[ent->psct - 1].top)
		ent->hp = 0;
}

void			ratstrike(t_entity *ent, t_param *p)
{
	double		tgt;
	double		dist;

	dist = distentz(ent, p->map);
	tgt = fmod((acos((p->map->pos.x - ent->pos.x) *
	1 / (distent(ent->pos, p->map->pos)))), 6.2831);
	tgt = (ent->pos.y < p->map->pos.y) ? tgt : 6.2831 - tgt;
	if (dist <= 10 && angark(ent->ang, tgt, 0.5))
	{
		if (p->map->status > 4 && p->map->defence > 0)
		{
			p->map->defence -= (angark(p->map->ang, tgt, 3)) ? 1 : 2;
			Mix_PlayChannel(-1, p->map->weaplst[0].w_s.block[rand() % 2], 0);
			defregen(p->map, 25);
		}
		else
		{
			p->map->status = (p->map->status == 5) ? 4 : p->map->status;
			p->map->hp -= 3 * p->diflvl;
			Mix_PlayChannel(-1, p->s.player[0], 0);
		}
	}
}

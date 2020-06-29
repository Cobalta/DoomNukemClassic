/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <tprzybyl@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:30:56 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/06/25 22:25:50 by tprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void	switchlever(t_entity *ent, t_param *p)
{
	p->map->sect[ent->lever.z - 1].levs += (ent->state) ? -1 : 1;
	ent->state = (ent->state) ? 0 : 1;
	ent->art = (ent->state) ? p->art[25] : p->art[26];
}

static int	precalcstrike(double *ang, t_param *p, t_entity *ent, t_weapon *wp)
{
	int timer;

	*ang = fmod((acos((p->map->pos.x - ent->pos.x) * 1 / (distent(ent->pos,
	p->map->pos)))), 6.2831);
	*ang = (ent->pos.y < p->map->pos.y) ? *ang : 6.2831 - *ang;
	*ang -= ent->ang;
	ent->hp -= wp->damage[wp->tmpstrike] * wp->tmpmass / 100;
	timer = wp->impact[wp->tmpstrike] * wp->tmpmass / 100;
	return (timer);
}

void		strikedeliver(t_param *p, t_entity *ent, t_weapon *wp)
{
	int		id;
	int		timer;
	double	ang;

	ent->lock = 0;
	id = 0;
	wp->tmpmass -= wp->mass[wp->tmpstrike];
	if (wp->tmpmass > 0 && ent->hp > 0)
	{
		timer = precalcstrike(&ang, p, ent, wp);
		while (&p->map->entities[id] != ent)
			id++;
		if (ent->type == 1)
		{
			entaccel(ent, sqrt(4 * timer) * -cos(ang),
			sqrt(4 * timer) * sin(ang), 400);
			behaverecover(ent, id, p, timer);
			Mix_PlayChannel(-1, p->s.player[1], 0);
		}
		else
			Mix_PlayChannel(-1, p->s.dig[rand() % 3], 0);
	}
}

void		pushdeliver(t_param *p, t_entity *ent)
{
	int		id;
	double	ang;

	ent->lock = 0;
	id = 0;
	if (ent->type == 11)
		switchlever(ent, p);
	if (ent->hp > 0)
	{
		ang = fmod((acos((p->map->pos.x - ent->pos.x) * 1 / (distent(ent->pos,
								p->map->pos)))), 6.2831);
		ang = (ent->pos.y < p->map->pos.y) ? ang : 6.2831 - ang;
		ang -= ent->ang;
		while (&p->map->entities[id] != ent)
			id++;
		if (ent->type == 1)
		{
			entaccel(ent, 15.0 * -cos(ang), 15.0 * sin(ang), 1000);
			behaverecover(ent, id, p, 30);
		}
	}
}

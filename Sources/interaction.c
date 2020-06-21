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

void		strikedeliver(t_param *p, t_entity *ent, t_weapon *wp)
{
	int id;
	int timer;
	double ang;

	ent->lock = 0;
	id = 0;
	wp->tmpmass -= wp->mass[wp->tmpstrike];
	if (ent->type == 11)
	{
	ent->state = (ent->state) ? 0 : 1;
	ent->art = (ent->state) ? p->art[25] : p->art[26];
	}
	if (wp->tmpmass > 0 && ent->hp > 0)
	{
		ang = fmod((acos((p->map->pos.x - ent->pos.x) * 1/(distent(ent->pos,
								p->map->pos)))), 6.2831);
		ang = (ent->pos.y < p->map->pos.y) ? ang : 6.2831 - ang;
		ang -= ent->ang;
	while (&p->map->entities[id] != ent)
		id++;
	timer = wp->impact[wp->tmpstrike] * wp->tmpmass/100;
	ent->hp -= wp->damage[wp->tmpstrike] * wp->tmpmass/100;
	if (ent->type == 1)
	{
	entaccel(ent, sqrt(4 * timer) *-cos(ang), sqrt(4 * timer)*sin(ang), 400);
	behaverecover(ent, id, p, timer);
	}
	}
}

void		pushdeliver(t_param *p, t_entity *ent)
{
	int id;
	double ang;

	ent->lock = 0;
	id = 0;
	if (ent->type == 11)
	{
	ent->state = (ent->state) ? 0 : 1;
	ent->art = (ent->state) ? p->art[25] : p->art[26];
	}
	if (ent->hp > 0)
	{
		ang = fmod((acos((p->map->pos.x - ent->pos.x) * 1/(distent(ent->pos,
								p->map->pos)))), 6.2831);
		ang = (ent->pos.y < p->map->pos.y) ? ang : 6.2831 - ang;
		ang -= ent->ang;
		while (&p->map->entities[id] != ent)
			id++;
		if (ent->type == 1)
		{
		entaccel(ent, 15.0 *-cos(ang), 15.0 * sin(ang), 1000);
		behaverecover(ent, id, p, 30);
		}
	}
}

void		entcollision(t_entity *ent, int id, t_map *map)
{
	double dist;
	double tgt;

	dist = distentz(ent, map);
	if (dist < 4 && ent->state < 5)
	{
		if (map->speed.x)
			map->speed.x += (map->speed.x > 0) ? -2 : 2;
		if (map->speed.y)
			map->speed.y += (map->speed.y > 0) ? -2 : 2;
	}
}

static void	firstcase(t_dpos *src, t_param *p, t_weapon *wp)
{
	int	i;
	int	xinc;
	int	yinc;
	int	cumul;

	xinc = (p->dx > 0) ? 1 : -1;
	yinc = (p->dy > 0) ? 1 : -1;
	p->dx = ft_abs(p->dx);
	p->dy = ft_abs(p->dy);
	cumul = p->dx / 2;
	i = 1;
	while (i <= p->dx)
	{
		src->x += xinc;
		cumul += p->dy;
		if (cumul >= p->dx)
		{
			cumul -= p->dx;
			src->y += yinc;
		}
		if (p->actmap[(int)src->x][(int)src->y].data)
		{
						if (p->actmap[(int)src->x][(int)src->y].data->lock && distentz
					(p->actmap[(int)src->x][(int)src->y].data, p->map) < wp->range)
			{
			strikedeliver(p, p->actmap[(int)src->x][(int)src->y].data, wp);
			}
		}
		i++;
	}
}

static void	secondcase(t_dpos *src, t_param *p, t_weapon *wp)
{
	int	i;
	int	xinc;
	int	yinc;
	int	cumul;

	xinc = (p->dx > 0) ? 1 : -1;
	yinc = (p->dy > 0) ? 1 : -1;
	p->dx = ft_abs(p->dx);
	p->dy = ft_abs(p->dy);
	cumul = p->dy / 2;
	i = 1;
	while (i <= p->dy)
	{
		src->y += yinc;
		cumul += p->dx;
		if (cumul >= p->dy)
		{
			cumul -= p->dy;
			src->x += xinc;
		}
		if (p->actmap[(int)src->x][(int)src->y].data)
		{
			if (p->actmap[(int)src->x][(int)src->y].data->lock && distentz
					(p->actmap[(int)src->x][(int)src->y].data, p->map) < wp->range)
			{
			strikedeliver(p, p->actmap[(int)src->x][(int)src->y].data, wp);
			}
		}
		i++;
	}
}

void		lineactmap(t_dpos *src, t_dpos *dst, t_param *p, t_weapon *wp)
{
	t_dpos	ssrc;

	ssrc.x = src->x;
	ssrc.y = src->y;
	p->dx = dst->x - src->x;
	p->dy = dst->y - src->y;
	if (p->actmap[(int)src->x][(int)src->y].data)
	{
		if (p->actmap[(int)src->x][(int)src->y].data->lock && distentz
				(p->actmap[(int)src->x][(int)src->y].data, p->map) < wp->range)
		{
			strikedeliver(p, p->actmap[(int)src->x][(int)src->y].data, wp);
		}
	}
	(ft_abs(p->dx) > ft_abs(p->dy)) ? firstcase(src, p, wp) :
		secondcase(src, p, wp);
	src->x = ssrc.x;
	src->y = ssrc.y;
}

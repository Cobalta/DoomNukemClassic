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

void		strikedeliver(t_map *map, t_entity *ent, t_weapon *wp)
{
	int id;
	int timer;
	double ang;

	ent->lock = 0;
	id = 0;
	wp->tmpmass -= wp->mass[wp->tmpstrike];
	if (wp->tmpmass > 0 && ent->hp > 0)
	{
		ang = fmod((acos((map->pos.x - ent->pos.x) * 1/(distent(ent->pos,
								map->pos)))), 6.2831);
		ang = (ent->pos.y < map->pos.y) ? ang : 6.2831 - ang;
		ang -= ent->ang;
	while (&map->entities[id] != ent)
		id++;
	timer = wp->impact[wp->tmpstrike] * wp->tmpmass/100;
	entaccel(ent, sqrt(4 * timer) *-cos(ang), sqrt(4 * timer)*sin(ang));
	ent->hp -= wp->damage[wp->tmpstrike] * wp->tmpmass/100;
	printf("///////////////HELTH %d\n",ent->hp);
	behaverecover(ent, id, map, timer);
	}
}

void		pushdeliver(t_map *map, t_entity *ent)
{
	int id;
	double ang;

	ent->lock = 0;
	id = 0;
	if (ent->hp > 0)
	{
	ang = fmod((acos((map->pos.x - ent->pos.x) * 1/(distent(ent->pos,
							map->pos)))), 6.2831);
	ang = (ent->pos.y < map->pos.y) ? ang : 6.2831 - ang;
	ang -= ent->ang;
	while (&map->entities[id] != ent)
		id++;
	entaccel(ent, sqrt(200) *-cos(ang), sqrt(200)*sin(ang));
	behaverecover(ent, id, map, 30);
	}
}

void		entcollision(t_entity *ent, int id, t_map *map)
{
	double dist;
	double tgt;

	dist = distent(map->pos, ent->pos);
	//	tgt = fmod((acos((map->pos.x - ent->pos.x ) * 1/(distent(ent->pos,
	//							map->pos)))), 6.2831);
	//	tgt = (ent->pos.y < map->pos.y) ? tgt : 6.2831 - tgt;
	if (dist < 4 && ent->state != 6)
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
			if (p->actmap[(int)src->x][(int)src->y].data->lock && distent
			(p->actmap[(int)src->x][(int)src->y].data->pos, p->map->pos) < wp->range)
			{
			strikedeliver(p->map, p->actmap[(int)src->x][(int)src->y].data, wp);
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
			if (p->actmap[(int)src->x][(int)src->y].data->lock && distent
					(p->actmap[(int)src->x][(int)src->y].data->pos, p->map->pos) < wp->range)
			{
			strikedeliver(p->map, p->actmap[(int)src->x][(int)src->y].data, wp);
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
		if (p->actmap[(int)src->x][(int)src->y].data->lock && distent
				(p->actmap[(int)src->x][(int)src->y].data->pos, p->map->pos) < wp->range)
		{
			strikedeliver(p->map, p->actmap[(int)src->x][(int)src->y].data, wp);
		}
	}
	(ft_abs(p->dx) > ft_abs(p->dy)) ? firstcase(src, p, wp) :
		secondcase(src, p, wp);
	src->x = ssrc.x;
	src->y = ssrc.y;
}

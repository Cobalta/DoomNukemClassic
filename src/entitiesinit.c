/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entitiesinit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 17:33:47 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/02 13:43:37 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

/*
** ALL TYPES OF ENTITIES LISTED HERE! =
** TYPE 1 = Basic ennemy
** TYPE 21 = Basic ennemy spawner
** TYPE 10 = Health thing
** TYPE 15 = Adrenaline
** TYPE 11 = Lever
*/

void				setart(t_entity *e, t_param *p)
{
	if (e->type == 1)
		e->art = p->art[60];
	if (e->type == 21)
		e->art = p->art[27];
	if (e->type == 10)
		e->art = p->art[24];
	if (e->type == 11)
		e->art = p->art[26];
	if (e->type == 15)
		e->art = p->art[28];
}

void				sethitpoints(t_entity *e)
{
	if (e->type == 1)
		e->hp = 100;
	if (e->type == 21)
		e->hp = 300;
	if (e->type == 10 || e->type == 11 || e->type == 15)
		e->hp = 0;
}

void				setmaxspeed(t_entity *e)
{
	if (e->type == 1)
		e->maxspeed = 1;
	if (e->type == 21)
		e->maxspeed = -1;
	if (e->type == 10 || e->type == 11 || e->type == 15)
		e->maxspeed = 0;
}

static void			readentity(t_entity *e, t_param *p)
{
	sethitpoints(e);
	setmaxspeed(e);
	setart(e, p);
	e->pz = p->map->sect[e->psct - 1].bot;
	e->speed.x = 0;
	e->speed.y = 0;
	e->speed.z = 0;
	e->spot = 0;
	e->boost = 0;
	e->state = 0;
	e->rotspeed = .15;
	e->addr = e;
}

void				entitiesinit(t_param *p)
{
	int i;

	i = 0;
	while (i < p->map->centities)
	{
		readentity(&p->map->entities[i], p);
		i++;
	}
}

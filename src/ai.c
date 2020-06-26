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

static void	ratai(t_entity *ent, t_param *p, int i)
{
	if (ent->state == 5)
		behaverecover(ent, i, p, 0);
	else if (ent->spot)
	{
		behavemove(ent, p->map);
		behaveattack(ent, i, p);
	}
	else
	{
		behavespot(ent, p->map);
		behavewander(ent, i);
	}
	ratsspacing(ent, p->map);
	entcollision(ent, p->map);
	entitymovement(p, ent, i);
	behaveaudio(p, 0);
}

void		ai(t_param *p)
{
	int i;

	i = -1;
	while (i++ < p->map->centities - 1)
	{
		if (p->map->entities[i].type == 11)
			lever(&p->map->entities[i], p->map);
		if (p->map->entities[i].type == 10)
			potion(&p->map->entities[i], p);
		if (p->map->entities[i].type == 15)
			adrenaline(&p->map->entities[i], p);
		if (p->map->entities[i].type == 21 && !p->map->entities[i].state)
			burrow(&p->map->entities[i], p, i);
		if (p->map->entities[i].type == 1 && p->map->entities[i].state != 6)
			ratai(&p->map->entities[i], p, i);
		gravity(p, &p->map->entities[i]);
	}
}

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

static void	entitymovx(t_param *p, t_entity *ent)
{
	if (aicheckcolls(p->map, ent,
				ent->pos.x + ent->speed.x * .20 * sin(ent->ang),
				ent->pos.y - ent->speed.x * .20 * cos(ent->ang)))
	{
		ent->pos.y -= ent->speed.x * .20 * cos(ent->ang);
		ent->pos.x += ent->speed.x * .20 * sin(ent->ang);
	}
}

static void	reverse(t_entity *ent)
{
	ent->ang += (ent->ang > 3.14) ? -3.14 : 3.14;
	ent->tgtang += (ent->tgtang > 3.14) ? -3.14 : 3.14;
}

static void	rotation(t_entity *ent)
{
	if (fabs(ent->ang - ent->tgtang) < 3.14 &&
		fabs(ent->ang - ent->tgtang) > ent->rotspeed)
		ent->ang += (ent->ang > ent->tgtang) ?
		-ent->rotspeed : ent->rotspeed;
	else if (fabs(ent->ang - ent->tgtang) > ent->rotspeed)
		ent->ang += (ent->ang > ent->tgtang) ?
		ent->rotspeed : -ent->rotspeed;
	ent->ang -= (ent->ang > 6.28) ? 6.28 : 0;
	ent->ang += (ent->ang < 0) ? 6.28 : 0;
}

void		entitymovement(t_param *p, t_entity *ent, int id)
{
	static int timer[512];

	timer[id] = (!timer[id]) ? 6 : timer[id];
	if (ent->rotspeed > 0)
		rotation(ent);
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
		else if (!ent->spot)
			reverse(ent);
	}
	else if (ent->state < 3)
		ent->state = 0;
	if (ent->speed.x != 0)
		entitymovx(p, ent);
}

void		gravity(t_param *p, t_entity *ent)
{
	if (ent->pz > p->map->sect[ent->psct - 1].bot)
	{
		if (ent->speed.z > -4000)
			ent->speed.z += -200;
	}
	if (ent->pz < p->map->sect[ent->psct - 1].bot)
	{
		ent->speed.z = 0;
		ent->pz = p->map->sect[ent->psct - 1].bot;
	}
	ent->pz += ent->speed.z;
}

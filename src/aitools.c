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

int		pathfirstroom(t_entity *ent, t_map *map, t_sector sct, int rec)
{
	int			i;

	i = -1;
	while (i++ < sct.cwall - 1)
	{
		if (sct.wall[i].portal == map->psct && sct.wall[i].portal != rec)
		{
			if (rec)
				return (1);
			else
			{
				ent->tgtpos.x = sct.wall[i].a.x +
				(sct.wall[i].b.x - sct.wall[i].a.x) * .5;
				ent->tgtpos.y = sct.wall[i].a.y +
				(sct.wall[i].b.y - sct.wall[i].a.y) * .5;
				return (1);
			}
		}
	}
}

int		pthfind(t_entity *ent, t_map *map, t_sector sct, int rec)
{
	int	i;

	if (pathfirstroom(ent, map, sct, rec))
		return (1);
	i = -1;
	while (i++ < sct.cwall - 1)
	{
		if (sct.wall[i].portal && sct.wall[i].portal != rec)
		{
			if (pthfind(ent, map, map->sect[sct.wall[i].portal - 1], sct.id))
			{
				if (rec)
					return (1);
				else
				{
					ent->tgtpos.x = sct.wall[i].a.x +
					(sct.wall[i].b.x - sct.wall[i].a.x) * .5;
					ent->tgtpos.y = sct.wall[i].a.y +
					(sct.wall[i].b.y - sct.wall[i].a.y) * .5;
					return (1);
				}
			}
		}
	}
	return (0);
}

int		checklos(t_entity *ent, t_map *map)
{
	int i;

	i = 0;
	while (map->sect[ent->psct - 1].cwall > i)
	{
		if (crossline(ent->pos, map->pos, map->sect[ent->psct - 1].wall[i].a,
					map->sect[ent->psct - 1].wall[i].a) &&
				!map->sect[ent->psct - 1].wall[i].portal)
			return (1);
		i++;
	}
	while (map->sect[map->psct - 1].cwall > i)
	{
		if (crossline(ent->pos, map->pos, map->sect[map->psct - 1].wall[i].a,
					map->sect[map->psct - 1].wall[i].a) &&
				!map->sect[map->psct - 1].wall[i].portal)
			return (1);
		i++;
	}
	return (0);
}

void	entaccel(t_entity *ent, int y, int x, int z)
{
	if (y)
		ent->speed.y += (ent->speed.y >=
		ent->maxspeed + ent->boost) ? y : 1 + y;
	if (ent->speed.y != 0)
		ent->speed.y += (ent->speed.y > 0) ? -1 : 1;
	if (x)
		ent->speed.x += (ent->speed.x >=
		ent->maxspeed + ent->boost) ? x : 1 + x;
	if (ent->speed.x != 0)
		ent->speed.x += (ent->speed.x > 0) ? -1 : 1;
	if (z)
	{
		ent->speed.z += z;
		ent->speed.z += (ent->speed.x > 0) ? -1 : 1;
	}
}
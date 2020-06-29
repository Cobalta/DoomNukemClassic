/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <tprzybyl@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:31:28 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/06/25 20:06:44 by tprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		portalcoll(t_map *map, t_sector *sect, t_dpos dest, int i)
{
	if (!sect->wall[i].portal)
		return (0);
	if (sect->wall[i].portal)
	{
		if (map->pz + 5000 - map->pcrouch >
		map->sect[sect->wall[i].portal - 1].top ||
				map->pz + 3000 < map->sect[sect->wall[i].portal - 1].bot)
			return (0);
		if (!reccolls(map, sect, dest, i))
			return (0);
		else if (map->psct > 0)
		{
			map->psct = -sect->wall[i].portal;
			map->pz = (map->pz < map->sect[sect->wall[i].portal - 1].bot)
				? map->sect[sect->wall[i].portal - 1].bot : map->pz;
		}
	}
	return (1);
}

int		reccolls(t_map *map, t_sector *os, t_dpos dest, int ow)
{
	int			i;
	t_sector	*sect;

	sect = &map->sect[os->wall[ow].portal - 1];
	i = 0;
	while (i < sect->cwall)
	{
		if (crossline(map->pos, dest, sect->wall[i].a, sect->wall[i].b) &&
				i != getwall(ow, os, sect))
			return (portalcoll(map, sect, dest, i));
		i++;
	}
	return (1);
}

int		checkcolls(t_map *map, t_sector *sect, double x, double y)
{
	int			i;
	t_dpos		dest;

	dest.x = x;
	dest.y = y;
	i = 0;
	while (i < sect->cwall)
	{
		if (crossline(map->pos, dest, sect->wall[i].a, sect->wall[i].b))
			return (portalcoll(map, sect, dest, i));
		i++;
	}
	return (1);
}

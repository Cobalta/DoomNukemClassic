/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:31:28 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/10 19:04:12 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int			verttwo(t_dpos i, t_dpos j, t_dpos k, t_dpos l)
{
	double a;
	double b;
	double y;

	if (i.y == j.y && 1 == ft_isbetween(i.x, j.x, k.x))
		return (1);
	if (i.y == j.y && 1 != ft_isbetween(i.x, j.x, k.x))
		return (0);
	a = (j.y - i.y) / (j.x - i.x);
	b = i.y - (a * i.x);
	y = a * k.x + b;

	if (ft_isbetween(i.y, j.y, y) && ft_isbetween(k.y, l.y, y))
		return (1);
	else
		return (0);
}

static int			vertone(t_dpos i, t_dpos j, t_dpos k, t_dpos l)
{
	double a;
	double b;
	double y;

	a = (l.y - k.y) / (l.x - k.x);
	b = k.y - (a * k.x);
	y = a * i.x + b
		;
	if (ft_isbetween(i.y, j.y, y) && ft_isbetween(k.y, l.y, y))
		return (1);
	else
		return (0);
}

static int			crossline(t_dpos i, t_dpos j, t_dpos k, t_dpos l)
{
	t_dpos a;
	t_dpos b;
	double x;

	if (i.x == j.x)
		return (vertone(i, j, k, l));
	if (k.x == l.x)
		return (verttwo(i, j, k, l));
	a.x = (j.y - i.y) / (j.x - i.x);
	a.y = (l.y - k.y) / (l.x - k.x);
	if (a.x == a.y)
		return (0);
	b.x = i.y - (a.x * i.x);
	b.y = k.y - (a.y * k.x);
	x = (b.y - b.x) / (a.x - a.y);
	if (ft_isbetween(i.x, j.x, x) && ft_isbetween(k.x, l.x, x))
		return (1);
	else
		return (0);
}

static int			reccolls(t_map *map, t_sector *os, t_dpos dest, int ow)
{
	int i;
	t_sector *sect;

	sect = &map->sect[os->wall[ow].portal - 1];
	i = 0;
	while (i < sect->cwall)
	{
		if (crossline(map->pos, dest, sect->wall[i].a, sect->wall[i].b) &&
				i != getwall(ow, os, sect))
		{
			if (!sect->wall[i].portal)
				return (0);
			if (sect->wall[i].portal)
			{
				if (map->pz + 5000 - map->pcrouch >
				map->sect[sect->wall[i].portal - 1].top ||
						map->pz + 3000 < map->sect[sect->wall[i].portal - 1].bot)
					return(0);
				if (!reccolls(map, sect, dest, i))
					return (0);
				map->psct = sect->wall[i].portal;
				map->pz = (map->pz < map->sect[sect->wall[i].portal - 1].bot)
					? map->sect[sect->wall[i].portal - 1].bot : map->pz;
			}
			return (1);
		}
		i++;
	}
	return (1);
}

int				checkcolls(t_map *map, t_sector *sect, double x, double y)
{
	int i;
	t_dpos dest;

	dest.x = x;
	dest.y = y;
	i = 0;
	while (i < sect->cwall)
	{
		if (crossline(map->pos, dest, sect->wall[i].a, sect->wall[i].b))
		{
			if (!sect->wall[i].portal)
			{
				return (0);
				}
			if (sect->wall[i].portal)
			{
				if (map->pz + 5000 - map->pcrouch> map->sect[sect->wall[i].portal - 1].top ||
						map->pz + 3000 < map->sect[sect->wall[i].portal - 1].bot)
						{
					return(0);
					}
				if (!reccolls(map, sect, dest, i))
				{
				printf("no\n");
					return (0);
					}
				map->psct = sect->wall[i].portal;
				map->pz = (map->pz < map->sect[sect->wall[i].portal - 1].bot)
					? map->sect[sect->wall[i].portal - 1].bot : map->pz;
			}
			return (1);
		}
		i++;
	}
	return (1);
}

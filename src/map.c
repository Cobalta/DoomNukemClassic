/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:32:18 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/11 17:48:27 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void		xpixlensandart(t_wall *w, char **str, t_param *p)
{
	int a;
	int b;
	int c;

	a = w->a.x - w->b.x;
	a *= a;
	b = w->a.y - w->b.y;
	b *= b;
	c = a + b;
	w->xpix = sqrt(c);
	w->xpix *= 12.8;
	w->art = p->art[nextatoi(str)];
	if (w->portal)
	w->botart = p->art[nextatoi(str)];
}

static void		readsector(char **str, t_sector *s, t_param *p)
{
	int		i;
	int		ypix;

	s->cwall = nextatoi(str);
	s->top = nextatoi(str) * 100;
	s->bot = nextatoi(str) * 100;
	s->btop = s->top;
	s->bbot = s->bot;
	ypix = 0.0128 * ((s->top - s->bot));
	s->wall = malloc(sizeof(t_wall) * s->cwall);
	i = 0;
	while (i < s->cwall)
	{
		s->wall[i].a.x = nextatoi(str);
		s->wall[i].a.y = nextatoi(str);
		s->wall[i].b.x = nextatoi(str);
		s->wall[i].b.y = nextatoi(str);
		s->wall[i].portal = nextatoi(str);
		s->wall[i].ypix = ypix;
		s->wall[i].sect = s;
		xpixlensandart(&s->wall[i], str, p);
		i++;
	}
}

static void		readentities(char **str, t_entity *e, t_param *p, t_map *map)
{
	int tmp;

	e->pos.x = nextatoi(str);
	e->pos.y = nextatoi(str);
	e->ang = nextatoi(str);
	e->psct = nextatoi(str);
	e->scale = nextatoi(str) * 1000;
	e->type = nextatoi(str);
	if (e->type == 11)
	{
	e->lever.z = nextatoi(str);
	e->lever.x = nextatoi(str) * 100;
	e->lever.y = nextatoi(str) * 100;
	}
	readentity(p, e, map);
}

static void		correct_portals_ypix(t_map *map)
{
	int i;
	int j;

	i = -1;
	while (++i < map->ctsector)
	{
		j = -1;
		while (++j < map->sect[i].cwall)
		{
			if (map->sect[i].wall[j].portal)
			{
				map->sect[i].wall[j].ypix = 0.0128 * ((map->sect[i].top - map->sect[map->sect[i].wall[j].portal - 1].top));
				map->sect[i].wall[j].botypix = 0.0128 * ((map->sect[map->sect[i].wall[j].portal - 1].bot - map->sect[i].bot));
			}
		}
	}
}

void			readmap(int fd, t_param *param)
{
	char		*str;
	char		*tmp;
	int			i;
	t_map		*map;

	if (!(map = malloc(sizeof(t_map))))
		error_func(-1);
	if (!(str = ft_strdup("")))
		error_func(-1);
	if (!(ft_strgetfrom(fd, &str)))
		error_func(-1);
	tmp = str;
	nextatoi(&str);
	map->hp = 100;
	map->status = 4;
	map->speed.x = 0;
	map->speed.y = 0;
	map->speed.z = 0;
	map->pcrouch = 0;
	map->defence = 0;
	map->alock = 0;
	map->pos.x = nextatoi(&str);
	map->pos.y = nextatoi(&str);
	map->ang = nextatoi(&str);
	map->psct = nextatoi(&str);
	map->basepos.y = map->pos.y;
	map->basepos.x = map->pos.x;
	map->baseang = map->ang;
	map->basepsct = map->psct;
	map->ctsector = nextatoi(&str);
	map->sect = malloc(sizeof(t_sector) * map->ctsector);
	i = 0;
	while (i < map->ctsector)
	{
		map->sect[i].id = i + 1;
		readsector(&str, &map->sect[i], param);
		i++;
	}
	map->pz = map->sect[map->psct - 1].bot;
	map->centities = nextatoi(&str);
	if (map->centities > 512)
		error_func(-1);
	i = 0;
	while (i < map->centities)
	{
		readentities(&str, &map->entities[i], param, map);
		i++;
	}
	checkend(&str);
	ft_strdel(&tmp);
	correct_portals_ypix(map);
	createweapon_2hsword(&map->weaplst[0]);
	param->map = map;
}

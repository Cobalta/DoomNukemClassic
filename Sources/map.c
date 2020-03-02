/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:32:18 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/02 13:46:47 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		getpixlens(t_wall *w)
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
}

static void		readsector(char **str, t_sector *s, t_param *p)
{
	int		i;
	int		ypix;

	s->cwall = ft_atoinext(str);
	s->top = ft_atoinext(str) * 100;
	s->bot = ft_atoinext(str) * 100;
	ypix = 0.0128 * ((s->top - s->bot));
	s->wall = malloc(sizeof(t_wall) * s->cwall);
	i = 0;
	while (i < s->cwall)
	{
		s->wall[i].a.x = ft_atoinext(str);
		s->wall[i].a.y = ft_atoinext(str);
		s->wall[i].b.x = ft_atoinext(str);
		s->wall[i].b.y = ft_atoinext(str);
		s->wall[i].portal = ft_atoinext(str);
		s->wall[i].ypix = ypix;
		getpixlens(&s->wall[i]);
		i++;
	}
}

static void		readentities(char **str, t_entity *e, t_param *p)
{
	int tmp;

	e->pos.x = ft_atoinext(str);
	e->pos.y = ft_atoinext(str);
	e->ang = ft_atoinext(str);
	e->esct = ft_atoinext(str);
	e->scale = ft_atoinext(str) * 1000;
	tmp = ft_atoinext(str);
	readentity(p, e, tmp);
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
	ft_atoinext(&str);
	map->pspeed.x = 0;
	map->pspeed.y = 0;
	map->pspeed.z = 0;
	map->pcrouch = 0;
	map->pos.x = ft_atoinext(&str);
	map->pos.y = ft_atoinext(&str);
	map->ang = ft_atoinext(&str);
	map->psct = ft_atoinext(&str);
	map->basepos.y = map->pos.y;
	map->basepos.x = map->pos.x;
	map->baseang = map->ang;
	map->basepsct = map->psct;
	map->ctsector = ft_atoinext(&str);
	map->sect = malloc(sizeof(t_sector) * map->ctsector);
	i = 0;
	while (i < map->ctsector)
	{
		readsector(&str, &map->sect[i], param);
		i++;
	}
	map->pz = map->sect[map->psct - 1].bot;
	map->centities = ft_atoinext(&str);
	if (map->centities > 512)
		error_func(-1);
	i = 0;
	while (i < map->centities)
	{
		readentities(&str, &map->entities[i], param);
		i++;
	}
	ft_strdel(&tmp);
	param->map = map;
}

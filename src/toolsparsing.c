/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolsparsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:19:37 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/11 17:51:05 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		checkend(char **str)
{
	while ((**str))
	{
		if (**str == '-' || **str == '+' || (**str > 47 && **str < 58))
			error_func(6);
		*str += 1;
	}
}

int			nextatoi(char **str, int i, int neg)
{
	long	nb;

	if (!(**str))
		error_func(6);
	nb = 0;
	i = 0;
	neg = 0;
	while ((*str)[i] == '\f' || (*str)[i] == ' ' || (*str)[i] == '\t' ||
			(*str)[i] == '\n' || (*str)[i] == '\r' || (*str)[i] == '\v')
		i++;
	if ((*str)[i] == '-')
		neg = 1;
	if ((*str)[i] == '-' || (*str)[i] == '+')
		i++;
	while ((*str)[i] > 47 && (*str)[i] < 58)
	{
		nb = nb * 10 + ((*str)[i] - 48);
		i++;
	}
	if (neg == 1)
		nb = -nb;
	*str += i;
	while (!ft_isdigit(**str) && **str && **str != '-')
		*str += 1;
	return ((int)nb);
}

void		setcolor(SDL_Color *col, int r, int g, int b)
{
	col->r = r;
	col->g = g;
	col->b = b;
}

void		readsector(char **str, t_sector *s, t_param *p)
{
	int		i;
	int		ypix;

	s->cwall = nextatoi(str, 0, 0);
	s->top = nextatoi(str, 0, 0) * 100;
	s->bot = nextatoi(str, 0, 0) * 100;
	s->btop = s->top;
	s->bbot = s->bot;
	ypix = 0.0128 * ((s->top - s->bot));
	s->wall = malloc(sizeof(t_wall) * s->cwall);
	i = 0;
	while (i < s->cwall)
	{
		s->wall[i].a.x = nextatoi(str, 0, 0);
		s->wall[i].a.y = nextatoi(str, 0, 0);
		s->wall[i].b.x = nextatoi(str, 0, 0);
		s->wall[i].b.y = nextatoi(str, 0, 0);
		s->wall[i].portal = nextatoi(str, 0, 0);
		s->wall[i].ypix = ypix;
		s->wall[i].sect = s;
		xpixlensandart(&s->wall[i], str, p);
		i++;
	}
}

void		readentities(char **str, t_entity *e, t_param *p, t_map *map)
{
	int tmp;

	e->pos.x = nextatoi(str, 0, 0);
	e->pos.y = nextatoi(str, 0, 0);
	e->ang = nextatoi(str, 0, 0);
	e->psct = nextatoi(str, 0, 0);
	e->scale = nextatoi(str, 0, 0) * 1000;
	e->type = nextatoi(str, 0, 0);
	if (e->type == 11)
	{
		e->lever.z = nextatoi(str, 0, 0);
		e->lever.x = nextatoi(str, 0, 0) * 100;
		e->lever.y = nextatoi(str, 0, 0) * 100;
	}
	readentity(p, e, map);
}

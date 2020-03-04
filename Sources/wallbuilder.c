/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallbuilder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:32:34 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/04 19:40:42 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		wewillbuildupper(t_qdpos *coor, t_param *p, t_wall *w)
{
	double	i;
	t_dpos	up;
	t_dpos	down;

	i = coor->a.x;
	while (i < coor->c.x)
	{
		if (i < coor->min)
			i = coor->min;
		up.x = i;
		down.x = i;
		down.y = 0;
		up.y = coor->a.y + (i - coor->a.x) * (coor->c.y - coor->a.y) / (coor->c.x - coor->a.x);
		drawline(&up, &down, p);
		down.y = coor->b.y + (i - coor->b.x) * (coor->d.y - coor->b.y) / (coor->c.x - coor->a.x);
		gettexturex(p, coor, down, w);
		drawtexedline(&up, &down, p, w);
		i++;
		if (i > coor->max)
			break;
	}
}

void		wewillbuildlower(t_qdpos *coor, t_param *p, t_wall *w)
{
	double	i;
	t_dpos	up;
	t_dpos	down;

	i = coor->a.x;
	while (i < coor->c.x)
	{
		if (i < coor->min)
			i = coor->min;
		up.x = i;
		down.x = i;
		up.y = coor->a.y + (i - coor->a.x) * (coor->c.y - coor->a.y) / (coor->c.x - coor->a.x);
		down.y = coor->b.y + (i - coor->b.x) * (coor->d.y - coor->b.y) / (coor->c.x - coor->a.x);
		gettexturex(p, coor, down, w);
		drawtexedline(&up, &down, p, w);
		up.y = WINH;
		drawline(&up, &down, p);
		i++;
		if (i > coor->max)
			break;
	}
}

void		wewillbuildaportal(t_qdpos coor, t_param *p, t_qdpos newcoor, t_wall *w)
{
	t_qdpos tmp;

	tmp = coor;
		tmp.b = newcoor.a;
		tmp.d = newcoor.c;
		wewillbuildupper(&tmp, p, w);
		tmp.b = coor.b;
		tmp.d = coor.d;
		tmp.a = newcoor.b;
		tmp.c = newcoor.d;
		wewillbuildlower(&tmp, p, w);
}

void		wewillbuildawall(t_qdpos *coor, t_param *p, t_wall *w)
{
	double	i;
	t_dpos	up;
	t_dpos	down;

	i = coor->a.x;
	while (i < coor->c.x)
	{
		if (i < coor->min)
			i = coor->min;
		up.x = i;
		down.x = i;
		down.y = 0;
		up.y = coor->a.y + (i - coor->a.x) * (coor->c.y - coor->a.y) / (coor->c.x - coor->a.x);
//		SDL_SetRenderDrawColor(p->ren, 100, 100, 100, 255);
		drawline(&up, &down, p);
		down.y = coor->b.y + (i - coor->b.x) * (coor->d.y - coor->b.y) / (coor->c.x - coor->a.x);
		gettexturex(p, coor, up, w);
		drawtexedline(&up, &down, p, w);
		up.y = WINH;
//		SDL_SetRenderDrawColor(p->ren, 50, 100, 100, 255);
		drawline(&up, &down, p);
		i++;
		if (i > coor->max)
			break;
	}
}

void		wewillbuildanentity(t_qdpos *coor, t_param *p, t_entity *e)
{
	int i;
	t_dpos	up;
	t_dpos	down;

	i = coor->a.x;
	while (i < coor->c.x)
	{
		if (i < coor->min)
			i = coor->min;
		up.x = i;
		down.x = i;
		up.y = coor->a.y + (i - coor->a.x) * (coor->c.y - coor->a.y) / (coor->c.x - coor->a.x);
		down.y = coor->b.y + (i - coor->b.x) * (coor->d.y - coor->b.y) / (coor->c.x - coor->a.x);
		p->dx = ((up.x - coor->a.x) / (coor->c.x - coor->a.x)) * e->art->w;
		drawspritedline(&up, &down, p, e);
		i++;
		if (i > coor->max)
			break;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallbuilder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:32:34 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/06 18:29:10 by ebourgeo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		wewillbuildupper(t_qdpos *coor, t_param *p, t_wall *w)
{
	double	i;
	t_dpos	up;
	t_dpos	down;
	int		c;

	c = sctnb(w, p);
	i = (coor->a.x < coor->min) ? coor->min : coor->a.x;
	while (i < coor->c.x && i < coor->max)
	{
		startingvalues(coor, &up, &down, i);
		if (up.y > down.y)
			drawcline(&up, &down, p, -c);
		down.y = coor->b.y + (i - coor->b.x) * (coor->d.y - coor->b.y) /
		(coor->c.x - coor->a.x);
		(down.y == p->consty + WINH / 2) ? uxgettexturex(p, coor, up, w) :
		gettexturex(p, coor, down, w);
		drawtexedline(&up, &down, p, w);
		i++;
	}
}

void		wewillbuildlower(t_qdpos *coor, t_param *p, t_wall *w, t_qdpos *oc)
{
	double	i;
	t_dpos	up;
	t_dpos	down;
	int		c;

	c = sctnb(w, p);
	i = (coor->a.x < coor->min) ? coor->min : coor->a.x;
	while (i < coor->c.x && i < coor->max)
	{
		lowerstartingvalues(coor, &up, &down, i);
		down.y = oc->a.y + (i - oc->a.x) * (oc->c.y - oc->a.y) /
		(oc->c.x - oc->a.x);
		(down.y == p->consty + WINH / 2) ? xgettexturex(p, coor, up, w) :
		gettexturex(p, coor, down, w);
		p->dy = -66;
		down.y = coor->b.y + (i - coor->b.x) * (coor->d.y - coor->b.y) /
		(coor->c.x - coor->a.x);
		drawtexedline(&up, &down, p, w);
		p->dy = 1;
		up.y = WINH;
		if (up.y > down.y)
			drawcline(&up, &down, p, c);
		i++;
	}
}

void		buildaportal(t_qdpos coor, t_param *p, t_qdpos newcoor, t_wall *w)
{
	t_qdpos	tmp;

	tmp = coor;
	tmp.b = newcoor.a;
	tmp.d = newcoor.c;
	wewillbuildupper(&tmp, p, w);
	tmp.b = coor.b;
	tmp.d = coor.d;
	tmp.a = newcoor.b;
	tmp.c = newcoor.d;
	wewillbuildlower(&tmp, p, w, &newcoor);
}

void		wewillbuildawall(t_qdpos *coor, t_param *p, t_wall *w)
{
	double	i;
	t_dpos	up;
	t_dpos	down;
	int		c;

	c = sctnb(w, p);
	i = (coor->a.x < coor->min) ? coor->min : coor->a.x;
	while (i < coor->c.x && i < coor->max)
	{
		startingvalues(coor, &up, &down, i);
		if (up.y > down.y)
			drawcline(&up, &down, p, -c);
		down.y = coor->b.y + (i - coor->b.x) * (coor->d.y - coor->b.y) /
		(coor->c.x - coor->a.x);
		(up.y == p->consty + WINH / 2) ? xgettexturex(p, coor, down, w) :
		gettexturex(p, coor, up, w);
		drawtexedline(&up, &down, p, w);
		up.y = WINH;
		if (up.y > down.y)
			drawcline(&up, &down, p, c);
		i++;
	}
}

void		wewillbuildanentity(t_qdpos *coor, t_param *p, t_entity *e)
{
	int		i;
	t_dpos	up;
	t_dpos	down;

	i = (coor->a.x < coor->min) ? coor->min : coor->a.x;
	while (i < coor->c.x && i < coor->max)
	{
		up.x = i;
		down.x = i;
		up.y = coor->a.y + (i - coor->a.x) *
		(coor->c.y - coor->a.y) / (coor->c.x - coor->a.x);
		down.y = coor->b.y + (i - coor->b.x) *
		(coor->d.y - coor->b.y) / (coor->c.x - coor->a.x);
		p->dx = ((up.x - coor->a.x) / (coor->c.x - coor->a.x)) * e->art->w;
		p->dx = (p->dx < 0) ? -p->dx : p->dx;
		drawspritedline(&up, &down, p, e);
		i++;
	}
}

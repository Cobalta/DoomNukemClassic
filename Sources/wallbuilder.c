/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallbuilder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:32:34 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/02/20 17:32:46 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		wewillbuildupper(t_qdpos *coor, t_param *p)
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
		SDL_SetRenderDrawColor(p->ren, 100, 100, 100, 255);
		if (up.y < 0)
			up.y = 0;
		drawline(&up, &down, p);
		down.y = coor->b.y + (i - coor->b.x) * (coor->d.y - coor->b.y) / (coor->c.x - coor->a.x);
		if (down.y > WINH)
			down.y = WINH;
		drawline(&up, &down, p);
		i++;
		if (i > coor->max)
			break;
	}
}

void		wewillbuildlower(t_qdpos *coor, t_param *p)
{
	double	i;
	t_dpos	up;
	t_dpos	down;

	i = coor->a.x;
	while (i < coor->c.x)
	{
		if (i < coor->min)
		{
			i = coor->min;
		}
		up.x = i;
		down.x = i;
		up.y = coor->a.y + (i - coor->a.x) * (coor->c.y - coor->a.y) / (coor->c.x - coor->a.x);
		down.y = coor->b.y + (i - coor->b.x) * (coor->d.y - coor->b.y) / (coor->c.x - coor->a.x);
		SDL_SetRenderDrawColor(p->ren, 50, 100, 100, 255);
		if (up.y < 0)
			up.y = 0;
		if (down.y > WINH)
			down.y = WINH;
		drawline(&up, &down, p);
		up.y = WINH;
		drawline(&up, &down, p);
		i++;
		if (i > coor->max)
		{
			break;
		}
	}

}

void		wewillbuildaportal(t_qdpos *coor, t_param *p, int port, int i)
{
	t_qdpos		upper;
	t_qdpos		lower;
	double		tmp1;
	double		tmp2;

	upper = *coor;
	getcoor(&upper, p, i, port - 1);
	lower = upper;
	tmp1 = upper.b.y;
	tmp2 = upper.d.y;
	upper.b.y = upper.a.y;
	upper.d.y = upper.c.y;
	upper.a.y = coor->a.y;
	upper.c.y = coor->c.y;

	lower.a.y = tmp1;
	lower.c.y = tmp2;
	lower.b.y = coor->b.y;
	lower.d.y = coor->d.y;
	wewillbuildupper(&upper, p);
	wewillbuildlower(&lower, p);
	SDL_SetRenderDrawColor(p->ren, 255, 255, 255, 255);
	if (upper.c.y < upper.d.y)
	{
		drawline(&upper.d, &upper.b, p);
//	drawline(&upper.a, &upper.c, p);
//	drawline(&upper.a, &upper.b, p);
//	drawline(&upper.d, &upper.c, p);
//	drawline(&lower.a, &lower.c, p);
//	drawline(&lower.b, &lower.a, p);
//	drawline(&lower.d, &lower.c, p);
//	drawline(&lower.b, &lower.d, p);
	}
	if (lower.c.y < lower.d.y)
		drawline(&lower.a, &lower.c, p);
}

void		wewillbuildawall(t_qdpos *coor, t_param *p, t_wall *w)
{
	double	i;
	t_dpos	up;
	t_dpos	down;
	double	ang;

	//	ang = getangle(w->a, w->b, p->map->pos);
	i = coor->a.x;
	while (i < coor->c.x)
	{
		if (i < coor->min)
			i = coor->min;
		up.x = i;
		down.x = i;
		down.y = 0;
		up.y = coor->a.y + (i - coor->a.x) * (coor->c.y - coor->a.y) / (coor->c.x - coor->a.x);
		SDL_SetRenderDrawColor(p->ren, 100, 100, 100, 255);
		drawline(&up, &down, p);
		down.y = coor->b.y + (i - coor->b.x) * (coor->d.y - coor->b.y) / (coor->c.x - coor->a.x);
		p->dx = ((up.x - coor->a.x) / (coor->c.x - coor->a.x) * (w->xpix));
		p->dx %= p->xxx->w;
		//		SDL_SetRenderDrawColor(p->ren, 244, 244, 244, 255);
		//		drawline(&up, &down, p);
		drawtexedline(&up, &down, p, w);
		up.y = WINH;
		SDL_SetRenderDrawColor(p->ren, 50, 100, 100, 255);
		drawline(&up, &down, p);
		i++;
		if (i > coor->max)
			break;
	}
}

void		wewillbuildanentity(t_qdpos *coor, t_param *p, t_entity e)
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
		p->dx = ((up.x - coor->a.x) / (coor->c.x - coor->a.x)) * e.art->w;
		drawspritedline(&up, &down, p, e);
		i++;
		if (i > coor->max)
			break;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changesector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:31:22 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/02 18:00:38 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			refreshportals(t_param *p)
{
}void		drawtexedline(t_dpos *src, t_dpos *dst, t_param *p, t_wall *w)
{
	SDL_Color	col;
	double		i;
	int			ty;

	i = (src->y < 0) ? -src->y : 0.0;
	while (src->y + i < dst->y && src->x >= 0 && src->x < WINL)
	{
		p->dy = ((src->y + i - src->y) / (dst->y - src->y) * w->ypix);
		p->dy %= p->xxx->h;
		SDL_GetRGBA(GetPixel(p->xxx, p->dx, p->dy), p->xxx->format, &col.r, &col.g, &col.b, &col.a);
		//			SDL_SetRenderDrawColor(p->ren, col.r, col.g, col.b, col.a);
		put_pixel(p->surf, src->x, src->y + i, SDL_MapRGB(p->surf->format, col.r, col.g, col.b));
		i++;
		if (src->y + i > WINH)
			break ;
	}
}

void		drawspritedline(t_dpos *src, t_dpos *dst, t_param *p, t_entity *e)
{
	SDL_Color	col;
	double		i;
	int			ty;

	i = (src->y < 0) ? -src->y : 0.0;
	while (src->y + i < dst->y && src->x >= 0 && src->x < WINL)
	{
		p->dy = ((i) / (dst->y - src->y) * e->art->h);
		SDL_GetRGBA(GetPixel(e->art, p->dx, p->dy), e->art->format, &col.r, &col.g, &col.b, &col.a);
		//			SDL_SetRenderDrawColor(p->ren, col.r, col.g, col.b, col.a);
		p->actmap[(int)src->x][(int)(src->y + i)].data = e;
		put_pixel(p->surf, src->x, src->y + i, SDL_MapRGB(p->surf->format, col.r, col.g, col.b));
		i++;
		if (src->y + i > WINH)
			break ;
	}
}

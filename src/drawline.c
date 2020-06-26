/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:31:53 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/11 18:02:53 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void	firstcase(t_dpos *src, t_param *p)
{
	int	i;
	int	xinc;
	int	yinc;
	int	cumul;

	xinc = (p->dx > 0) ? 1 : -1;
	yinc = (p->dy > 0) ? 1 : -1;
	p->dx = ft_abs(p->dx);
	p->dy = ft_abs(p->dy);
	cumul = p->dx / 2;
	i = 1;
	while (i <= p->dx)
	{
		src->x += xinc;
		cumul += p->dy;
		if (cumul >= p->dx)
		{
			cumul -= p->dx;
			src->y += yinc;
		}
		if (src->x >= 0 && src->x < WINL && src->y >= 0 && src->y < WINH)
			put_pixel(p->surf, src->x, src->y,
					SDL_MapRGB(p->surf->format, p->col.r, p->col.g, p->col.b));
		i++;
	}
}

static void	secondcase(t_dpos *src, t_param *p)
{
	int	i;
	int	xinc;
	int	yinc;
	int	cumul;

	xinc = (p->dx > 0) ? 1 : -1;
	yinc = (p->dy > 0) ? 1 : -1;
	p->dx = ft_abs(p->dx);
	p->dy = ft_abs(p->dy);
	cumul = p->dy / 2;
	i = 1;
	while (i++ <= p->dy)
	{
		src->y += yinc;
		cumul += p->dx;
		if (cumul >= p->dy)
		{
			cumul -= p->dy;
			src->x += xinc;
		}
		if (src->x >= 0 && src->x < WINL
		&& src->y >= 0 && src->y < WINH)
			put_pixel(p->surf, src->x, src->y,
					SDL_MapRGB(p->surf->format, p->col.r, p->col.g, p->col.b));
	}
}

void		drawline(t_dpos *src, t_dpos *dst, t_param *p)
{
	t_dpos	ssrc;

	ssrc.x = src->x;
	ssrc.y = src->y;
	p->dx = dst->x - src->x;
	p->dy = dst->y - src->y;
	if (src->x >= 0 && src->x < WINL && src->y >= 0 && src->y < WINH)
		put_pixel(p->surf, src->x, src->y,
				SDL_MapRGB(p->surf->format, p->col.r, p->col.g, p->col.b));
	(ft_abs(p->dx) > ft_abs(p->dy)) ? firstcase(src, p) :
	secondcase(src, p);
	src->x = ssrc.x;
	src->y = ssrc.y;
}

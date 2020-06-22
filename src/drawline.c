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

static Uint32		GetPixel(SDL_Surface *surface, int x, int y)
{
	int			bpp;
	Uint8		*p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 1)
		return (*p);
	else if (bpp == 2)
		return (*(Uint16 *)p);
	else if (bpp == 3)
		return (p[0] | p[1] << 8 | p[2] << 16);
	else if (bpp == 4)
		return (*(Uint32 *)p);
	return (0);
}

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
			put_pixel(p->surf, src->x, src->y, SDL_MapRGB(p->surf->format, p->col.r, p->col.g, p->col.b));
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
	while (i <= p->dy)
	{
		src->y += yinc;
		cumul += p->dx;
		if (cumul >= p->dy)
		{
			cumul -= p->dy;
			src->x += xinc;
		}
		if (src->x >= 0 && src->x < WINL && src->y >= 0 && src->y < WINH)
		put_pixel(p->surf, src->x, src->y, SDL_MapRGB(p->surf->format, p->col.r, p->col.g, p->col.b));
		i++;
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
		put_pixel(p->surf, src->x, src->y, SDL_MapRGB(p->surf->format, p->col.r, p->col.g, p->col.b));
	(ft_abs(p->dx) > ft_abs(p->dy)) ? firstcase(src, p) :
		secondcase(src, p);
	src->x = ssrc.x;
	src->y = ssrc.y;
}

void		drawtexedline(t_dpos *src, t_dpos *dst, t_param *p, t_wall *w)
{
	SDL_Color	col;
	double		i;
	int			bot;

	bot = (p->dy == -66) ? 0 : 1;
	i = (src->y < 0) ? -src->y : 0.0;
	while (src->y + i < dst->y && src->y + i < WINH)
	{
		if (src->x >= 0 && src->x < WINL && src->y + i >= 0)
		{
			//			SDL_GetRGBA(GetPixel(w->art, abs(p->dx), p->dy), w->art->format, &col.r, &col.g, &col.b, &col.a);
			p->dy = (bot) ? ((src->y + i - src->y) / (dst->y - src->y) * w->ypix) : ((src->y + i - src->y) / (dst->y - src->y) * w->botypix) ;
			p->dy %= (bot) ? w->art->h : w->botart->h;
			(bot) ? SDL_GetRGBA(GetPixel(w->art, abs(p->dx), p->dy), w->art->format, &col.r, &col.g, &col.b, &col.a) : SDL_GetRGBA(GetPixel(w->botart, abs(p->dx), p->dy), w->botart->format, &col.r, &col.g, &col.b, &col.a);
			if (col.r != 255 || col.g != 0 || col.b != 255)
				put_pixel(p->surf, src->x, src->y + i, SDL_MapRGB(p->surf->format, col.r, col.g, col.b));
		}
		i++;
	}
}

void		hudelement(t_param *p, SDL_Surface *elem)
{
	double x;
	double y;
	SDL_Color col;
	double	tmpw;
	double	tmph;

	x = -1;
	while (x++ < WINL)
	{
		y = -1;
		tmpw = x / WINL;
		while (y++ < WINH)
		{
			tmph = y / WINH;
			SDL_GetRGBA(GetPixel(elem, elem->w * tmpw, elem->h * tmph), elem->format, &col.r, &col.g, &col.b, &col.a);
			if (col.r != 255 || col.g != 0 || col.b != 255)
				put_pixel(p->surf, x, y, SDL_MapRGB(p->surf->format, col.r, col.g, col.b));
		}
	}
}

void		drawspritedline(t_dpos *src, t_dpos *dst, t_param *p, t_entity *e)
{
	SDL_Color	col;
	double		i;

	i = (src->y < 0) ? -src->y : 0.0;
	while (src->y + i < dst->y && src->x >= 0 && src->x < WINL && src->y + i < WINH)
	{
		if (src->x >= 0 && src->x < WINL && src->y + i >= 0 &&
				src->y + i < WINH)
		{
			p->dy = ((i) / (dst->y - src->y) * e->art->h);
			SDL_GetRGBA(GetPixel(e->art, p->dx, p->dy), e->art->format, &col.r, &col.g, &col.b, &col.a);
			if (col.r != 255 || col.g != 0 || col.b != 255)
			{
				p->actmap[(int)src->x][(int)(src->y + i)].data = e->addr;
				put_pixel(p->surf, src->x, src->y + i, SDL_MapRGB(p->surf->format, col.r, col.g, col.b));
			}
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:31:53 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/02 17:29:41 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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

static void	firstcase(t_dpos *src, t_param *param)
{
	int	i;
	int	xinc;
	int	yinc;
	int	cumul;

	xinc = (param->dx > 0) ? 1 : -1;
	yinc = (param->dy > 0) ? 1 : -1;
	param->dx = ft_abs(param->dx);
	param->dy = ft_abs(param->dy);
	cumul = param->dx / 2;
	i = 1;
	while (i <= param->dx)
	{
		src->x += xinc;
		cumul += param->dy;
		if (cumul >= param->dx)
		{
			cumul -= param->dx;
			src->y += yinc;
		}
		if (src->x >= 0 && src->x < WINL && src->y >= 0 && src->y < WINH)
			put_pixel(param->surf, src->x, src->y, SDL_MapRGB(param->surf->format, 255, 255, 255));
		i++;
	}
}

static void	secondcase(t_dpos *src, t_param *param)
{
	int	i;
	int	xinc;
	int	yinc;
	int	cumul;

	xinc = (param->dx > 0) ? 1 : -1;
	yinc = (param->dy > 0) ? 1 : -1;
	param->dx = ft_abs(param->dx);
	param->dy = ft_abs(param->dy);
	cumul = param->dy / 2;
	i = 1;
	while (i <= param->dy)
	{
		src->y += yinc;
		cumul += param->dx;
		if (cumul >= param->dy)
		{
			cumul -= param->dy;
			src->x += xinc;
		}
		if (src->x >= 0 && src->x < WINL && src->y >= 0 && src->y < WINH)
			put_pixel(param->surf, src->x, src->y, SDL_MapRGB(param->surf->format, 255, 255, 255));
		i++;
	}
}

void		drawline(t_dpos *src, t_dpos *dst, t_param *param)
{
	t_dpos	ssrc;

	ssrc.x = src->x;
	ssrc.y = src->y;
	//	printf("Line (%f,%f);(%f,%f)\n", src->x, src->y, dst->x, dst->y),fflush(stdout);
	param->dx = dst->x - src->x;
	param->dy = dst->y - src->y;
	//	(dst->z > src->z) ? select_color(param, dst) : select_color(param, src);
	if (src->x >= 0 && src->x < WINL && src->y >= 0 && src->y < WINH)
		put_pixel(param->surf, src->x, src->y, SDL_MapRGB(param->surf->format, 255, 255, 255));
	(ft_abs(param->dx) > ft_abs(param->dy)) ? firstcase(src, param) :
		secondcase(src, param);
	src->x = ssrc.x;
	src->y = ssrc.y;
}

void		drawtexedline(t_dpos *src, t_dpos *dst, t_param *p, t_wall *w)
{
	SDL_Color	col;
	double		i;
	int			ty;

	i = 0.0;
	while (src->y + i < dst->y)
	{
		if (src->x >= 0 && src->x < WINL && src->y + i >= 0 &&
		src->y + i < WINH)
		{
			p->dy = ((src->y + i - src->y) / (dst->y - src->y) * w->ypix);
			p->dy %= p->xxx->h;
			SDL_GetRGBA(GetPixel(p->xxx, p->dx, p->dy), p->xxx->format, &col.r, &col.g, &col.b, &col.a);
//			SDL_SetRenderDrawColor(p->ren, col.r, col.g, col.b, col.a);
			put_pixel(p->surf, src->x, src->y + i, SDL_MapRGB(p->surf->format, col.r, col.g, col.b));
		}
		i++;
	}
}

void		drawspritedline(t_dpos *src, t_dpos *dst, t_param *p, t_entity *e)
{
	SDL_Color	col;
	double		i;
	int			ty;

	i = 0.0;
	while (src->y + i < dst->y)
	{
		if (src->x >= 0 && src->x < WINL && src->y + i >= 0 &&
		src->y + i < WINH)
		{
			p->dy = ((i) / (dst->y - src->y) * e->art->h);
			SDL_GetRGBA(GetPixel(e->art, p->dx, p->dy), e->art->format, &col.r, &col.g, &col.b, &col.a);
//			SDL_SetRenderDrawColor(p->ren, col.r, col.g, col.b, col.a);
			p->actmap[(int)src->x][(int)(src->y + i)].data = e;
			put_pixel(p->surf, src->x, src->y + i, SDL_MapRGB(p->surf->format, col.r, col.g, col.b));
		}
		i++;
	}
}

#include "../includes/doom.h"

static void	checkdata(t_param *p, t_weapon *wp, t_dpos *src)
{
	if (p->actmap[(int)src->x][(int)src->y].data->lock && distentz(
		p->actmap[(int)src->x][(int)src->y].data, p->map) < wp->range)
		strikedeliver(p, p->actmap[(int)src->x][(int)src->y].data, wp);
}

static void	firstcase(t_dpos *src, t_param *p, t_weapon *wp)
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
		if (p->actmap[(int)src->x][(int)src->y].data)
			checkdata(p, wp, src);
		i++;
	}
}

static void	secondcase(t_dpos *src, t_param *p, t_weapon *wp)
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
		if (p->actmap[(int)src->x][(int)src->y].data)
			checkdata(p, wp, src);
		i++;
	}
}

void		lineactmap(t_dpos *src, t_dpos *dst, t_param *p, t_weapon *wp)
{
	t_dpos	ssrc;

	ssrc.x = src->x;
	ssrc.y = src->y;
	p->dx = dst->x - src->x;
	p->dy = dst->y - src->y;
	if (p->actmap[(int)src->x][(int)src->y].data)
	{
		if (p->actmap[(int)src->x][(int)src->y].data->lock && distentz(
			p->actmap[(int)src->x][(int)src->y].data, p->map) < wp->range)
			strikedeliver(p, p->actmap[(int)src->x][(int)src->y].data, wp);
	}
	(ft_abs(p->dx) > ft_abs(p->dy)) ? firstcase(src, p, wp) :
		secondcase(src, p, wp);
	src->x = ssrc.x;
	src->y = ssrc.y;
}

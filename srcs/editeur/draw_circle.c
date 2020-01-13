/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw_circle.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nrivoire <nrivoire@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/12 15:04:07 by nrivoire     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/13 09:19:01 by nrivoire    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editeur.h"

void		display_point_octant(t_env *v, int x, int y, t_rgb color)
{
    pixel_put(v, v->center.x + x, v->center.y + y, color);
	pixel_put(v, v->center.x - x, v->center.y + y, color);
	pixel_put(v, v->center.x + x, v->center.y - y, color);
	pixel_put(v, v->center.x - x, v->center.y - y, color);
	pixel_put(v, v->center.x + y, v->center.y + x, color);
	pixel_put(v, v->center.x - y, v->center.y + x, color);
	pixel_put(v, v->center.x + y, v->center.y - x, color);
	pixel_put(v, v->center.x - y, v->center.y - x, color);
}

void		draw_void_circle(t_env *v, int x, int y, t_rgb color)
{
	int				j;
	int				i;
	int				d;

	v->center.x = x;
	v->center.y = y;
	i = -1;
	j = RADIUS;
	d = 3 - 2 * RADIUS;
	while (++i <= j)
	{
		if (d > 0)
		{
			j--;
			d = d + 4 * (i - j) + 10;
		}
		else
			d = d + 4 * i + 6;
		display_point_octant(v, i, j, color);
	}
}

void		display_line_octant(t_env *v, int x, int y, t_rgb color)
{
	drawline(make_point(v->center.x + x, v->center.y + y), 
			make_point(v->center.x, v->center.y), color, v);
	drawline(make_point(v->center.x - x, v->center.y + y), 
			make_point(v->center.x, v->center.y), color, v);
	drawline(make_point(v->center.x + x, v->center.y - y), 
			make_point(v->center.x, v->center.y), color, v);
	drawline(make_point(v->center.x - x, v->center.y - y), 
			make_point(v->center.x, v->center.y), color, v);
	drawline(make_point(v->center.x + y, v->center.y + x), 
			make_point(v->center.x, v->center.y), color, v);
	drawline(make_point(v->center.x - y, v->center.y + x), 
			make_point(v->center.x, v->center.y), color, v);
	drawline(make_point(v->center.x + y, v->center.y - x), 
			make_point(v->center.x, v->center.y), color, v);
	drawline(make_point(v->center.x - y, v->center.y - x), 
			make_point(v->center.x, v->center.y), color, v);
}

void		draw_full_circle(t_env *v, int x, int y, t_rgb color)
{
	int		j;
	int		i;
	int		d;

	v->center.x = x;
	v->center.y = y;
	i = -1;
	j = RADIUS;
	d = 3 - 2 * RADIUS;
	while (++i <= j)
	{
		if (d > 0)
		{
			j--;
			d = d + 4 * (i - j) + 10;
		}
		else
			d = d + 4 * i + 6;
		display_line_octant(v, i, j, color);
	}
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw_circle.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nrivoire <nrivoire@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/12 15:04:07 by nrivoire     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/13 09:41:27 by nrivoire    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editeur.h"

void		draw_void_circle(t_env *v, int x, int y, t_rgb color)
{
	int		j;
	int		i;
	int		d;

	v->center.x = x;
	v->center.y = y;
	j = -RADIUS - 1;
	while (++j <= RADIUS)
	{
		i = -RADIUS - 1;
		while (++i < RADIUS + 1)
		{
			if (sqrt(i * i + j * j) >= RADIUS -1 && 
					sqrt(i * i + j * j) <= RADIUS + 1)
				pixel_put(v, x + i, y + j, color);
		}
	}
}

void		draw_full_circle(t_env *v, int x, int y, t_rgb color)
{
	int		j;
	int		i;
	int		d;

	v->center.x = x;
	v->center.y = y;
	j = -RADIUS - 1;
	while (++j <= RADIUS)
	{
		i = -RADIUS - 1;
		while (++i < RADIUS)
		{
			if (sqrt(i * i + j * j) <= RADIUS)
				pixel_put(v, x + i, y + j, color);
		}
	}
}
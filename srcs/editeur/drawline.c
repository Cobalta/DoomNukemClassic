/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   drawline.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nrivoire <nrivoire@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/12 13:46:28 by nrivoire     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/13 09:23:17 by nrivoire    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editeur.h"

t_rgb			make_rgb(int r, int g, int b, int a)
{
	t_rgb		content;

	content.r = r;
	content.g = g;
	content.b = b;
	content.a = a;
	return (content);
}

t_point			make_point(int x, int y)
{
	t_point		content;

	content.x = x;
	content.y = y;
	return (content);
}

t_bressen		init_bresen(t_point m1, t_point m2)
{
	t_bressen	b;

	b.dx = ft_absolu(m2.x - m1.x);
	b.dy = ft_absolu(m2.y - m1.y);
	b.sx = (m1.x < m2.x ? 1 : -1);
	b.sy = (m1.y < m2.y ? 1 : -1);
	b.err = (b.dx > b.dy ? b.dx : -b.dy) / 2;
	return (b);
}

void			drawline(t_point m1, t_point m2, t_rgb color, t_env *v)
{
	t_bressen	b;

	if ((m1.x < 0 && m1.y < 0 && m2.y < 0 && m2.x < 0) ||
			(m1.x > WIDTH && m1.y > HEIGHT && m2.y > HEIGHT && m2.x > WIDTH))
		return ;
	b = init_bresen(m1, m2);
	while (1)
	{
		pixel_put(v, m1.x, m1.y, color);
		if (m1.x == m2.x && m1.y == m2.y)
			break ;
		b.e2 = b.err;
		if (b.e2 > -b.dx)
		{
			b.err -= b.dy;
			m1.x += b.sx;
		}
		if (b.e2 < b.dy)
		{
			b.err += b.dx;
			m1.y += b.sy;
		}
	}
}

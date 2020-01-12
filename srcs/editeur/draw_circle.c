/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw_circle.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nrivoire <nrivoire@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/12 15:04:07 by nrivoire     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/12 15:04:17 by nrivoire    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editeur.h"

void		display_each_octant(t_env *v, int x_center, int y_center, int x, int y)
{
	SDL_RenderDrawPoint(v->render, x_center + x, y_center + y);
	SDL_SetRenderDrawColor(v->render, 255, 255, 255, 255);
	SDL_RenderDrawPoint(v->render, x_center - x, y_center + y);
	SDL_SetRenderDrawColor(v->render, 255, 255, 255, 255);
	SDL_RenderDrawPoint(v->render, x_center + x, y_center - y);
	SDL_SetRenderDrawColor(v->render, 255, 255, 255, 255);
	SDL_RenderDrawPoint(v->render, x_center - x, y_center - y);
	SDL_SetRenderDrawColor(v->render, 255, 255, 255, 255);
	SDL_RenderDrawPoint(v->render, x_center + y, y_center + x);
	SDL_SetRenderDrawColor(v->render, 255, 255, 255, 255);
	SDL_RenderDrawPoint(v->render, x_center - y, y_center + x);
	SDL_SetRenderDrawColor(v->render, 255, 255, 255, 255);
	SDL_RenderDrawPoint(v->render, x_center + y, y_center - x);
	SDL_SetRenderDrawColor(v->render, 255, 255, 255, 255);
	SDL_RenderDrawPoint(v->render, x_center - y, y_center - x);
	SDL_SetRenderDrawColor(v->render, 255, 255, 255, 255);
}

void		draw_circle(t_env *v, int x, int y)
{
	int		j;
	int		i;
	int		d;

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
		display_each_octant(v, x, y, i, j);
	}
}

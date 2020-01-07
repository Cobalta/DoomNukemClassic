/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   line_tracer.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ebourgeo <ebourgeo@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/27 16:43:00 by ebourgeo     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/27 16:43:00 by ebourgeo    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h"

static void	linewriter1(t_line *line, t_seg *seg, t_env *env)
{
	int i;
	int px1;
	int py1;

	i = 0;
	px1 = line->px;
	py1 = line->py;

	while (i <= px1)
	{
		SDL_RenderDrawPoint(env->render, round(seg->x1), round(seg->y1));
		i++;
		seg->x1 += line->x_incr;
		line->px -= line->dy;
		if (line->px < 0)
		{
			seg->y1 += line->y_incr;
			line->px += line->dx;
		}
	}
	return ;
}

static void	linewriter2(t_line *line, t_seg *seg, t_env *env)
{
	int i;
	int px1;
	int py1;

	i = 0;
	px1 = line->px;
	py1 = line->py;
	while (i <= py1)
	{
		SDL_RenderDrawPoint(env->render, round(seg->x1), round(seg->y1));
		i++;
		seg->y1 += line->y_incr;
		line->py -= line->dx;
		if (line->py < 0)
		{
			seg->x1 += line->x_incr;
			line->py += line->dy;
		}
	}
	return ;
}

void	line_tracer(t_seg *seg, t_env *env)
{
	t_line line;

	line.px = fabsf(seg->x2 - seg->x1);
	line.py = fabsf(seg->y2 - seg->y1);
	line.x_incr = 1;
	line.y_incr = 1;
	if (seg->x1 > seg->x2)
		line.x_incr = -1;
	if (seg->y1 > seg->y2)
		line.y_incr = -1;
	line.dx = 2 * line.px;
	line.dy = 2 * line.py;

	if (line.dx > line.dy)
		linewriter1(&line, seg, env);
	else //if (line.dx < line.dy)
		linewriter2(&line, seg, env);
	return ;
} 

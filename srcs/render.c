/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ebourgeo <ebourgeo@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/03 17:11:43 by ebourgeo     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/03 17:11:43 by ebourgeo    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h"


float	distCircle(t_pt *pt, t_circle *c)
{
	return (fabs(sqrt((pt->x - c->x) * (pt->x - c->x)
					+ (pt->y - c->y) * (pt->y - c->y)) - c->r));
}

void	drawCircle(t_env *env, t_circle *c)
{
	int x, y, m;
	x = 0;
	y = c->r;
	m = 5 - 4*c->r;
	while (x <= y)
	{
		SDL_RenderDrawPoint(env->render, x+c->x, y+c->y);
		SDL_RenderDrawPoint(env->render, y+c->x, x+c->y);
		SDL_RenderDrawPoint(env->render, -x+c->x, y+c->y);
		SDL_RenderDrawPoint(env->render, -y+c->x, x+c->y);
		SDL_RenderDrawPoint(env->render, x+c->x, -y+c->y);
		SDL_RenderDrawPoint(env->render, y+c->x, -x+c->y);
		SDL_RenderDrawPoint(env->render, -x+c->x, -y+c->y);
		SDL_RenderDrawPoint(env->render, -y+c->x, -x+c->y);
		if (m > 0)
		{
			y--;
			m = m - 8*y;
		}
		x++;
		m = m + 8*x + 4;
	}
}

void	render(t_env *env)
{
	t_pt ro, vec;
	t_circle c1, c2, c3, c4, c5;
	int mpx, mpy;
	float angle, mag, mindist;
	t_seg ray;

	SDL_GetMouseState(&mpx, &mpy);
	SDL_SetRenderDrawColor(env->render, 0, 0, 255, 255);
	angle = 0;
	ro.x = env->width / 2;
	ro.y = env->height / 2;
	ray.x1 = ro.x;
	ray.y1 = ro.y;
	ray.x2 = mpx;
	ray.y2 = mpy;
	vec.x = ray.x2 - ray.x1;
	vec.y = ray.y2 - ray.y1;


	c1.x = env->width / 3;
	c1.y = env->height / 2;
	c1.r = 50;

	c2.x = env->width - 200;
	c2.y = env->height / 3;
	c2.r = 70;

	c3.x = 800;
	c3.y = 800;
	c3.r = 35;

	c4.x = 442;
	c4.y = 218;
	c4.r = 80;


	drawCircle(env, &c1);
	drawCircle(env, &c2);
	drawCircle(env, &c3);
	drawCircle(env, &c4);
	t_circle minc;
	minc.x = ro.x;
	minc.y = ro.y;
	mindist = 3;

	int i = 0;
	while (mindist > 2)
	{
		mag = sqrt(vec.x * vec.x + vec.y * vec.y);
		vec.x /= mag;
		vec.y /= mag;
		mindist = distCircle(&ro, &c1);
		if (mindist > distCircle(&ro, &c2))
			mindist = distCircle(&ro, &c2);
		if (mindist > distCircle(&ro, &c3))
			mindist = distCircle(&ro, &c3);
		if (mindist > distCircle(&ro, &c4))
			mindist = distCircle(&ro, &c4);
		vec.x *= mindist;
		vec.y *= mindist;
		minc.r = mindist;
		SDL_SetRenderDrawColor(env->render, 255, 0, 0, 255);
		drawCircle(env, &minc);
		SDL_SetRenderDrawColor(env->render, 0, 255, 0, 255);
		ray.x2 = ray.x1 + vec.x;
		ray.y2 = ray.y1 + vec.y;
		line_tracer(&ray, env);
		ray.x1 = ray.x2;
		ray.y1 = ray.y2;
		if (ray.x1 > env->width || ray.x1 < 0 || ray.y1 > env->height || ray.y1 < 0)
			break;
		minc.x = ray.x1;
		minc.y = ray.y1;
		ro.x = ray.x1;
		ro.y = ray.y1;
		i++;
	}
	printf("%d x %d y \n", mpx, mpy);
}
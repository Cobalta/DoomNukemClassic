/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   wallbuilder.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tprzybyl <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/18 14:49:06 by tprzybyl     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/18 16:33:57 by tprzybyl    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"
/*double		getangle(t_dpos a, t_dpos b, t_dpos c)
{
}*/

void		wewillbuildupper(t_qdpos *coor, t_param *p, int w)
{
	double	i;
	t_dpos	up;
	t_dpos	down;

	i = coor->a.x;
	while (i < coor->c.x)
	{
		if (i < coor->min)
			i = coor->min;
		up.x = i;
		down.x = i;
		down.y = 0;
		up.y = coor->a.y + (i - coor->a.x) * (coor->c.y - coor->a.y) / (coor->c.x - coor->a.x);
		SDL_SetRenderDrawColor(p->ren, 100, 100, 100, 255);
		if (up.y < 0)
			up.y = 0;
		drawline(&up, &down, p);
		down.y = coor->b.y + (i - coor->b.x) * (coor->d.y - coor->b.y) / (coor->c.x - coor->a.x);
		if (down.y > WINH)
			down.y = WINH;
		drawline(&up, &down, p);
		i++;
		if (i > coor->max)
			break;
	}
}

void		wewillbuildlower(t_qdpos *coor, t_param *p, int w)
{
	double	i;
	t_dpos	up;
	t_dpos	down;

	i = coor->a.x;
	while (i < coor->c.x)
	{
		if (i < coor->min)
		{
			i = coor->min;
		}
		up.x = i;
		down.x = i;
		up.y = coor->a.y + (i - coor->a.x) * (coor->c.y - coor->a.y) / (coor->c.x - coor->a.x);
		down.y = coor->b.y + (i - coor->b.x) * (coor->d.y - coor->b.y) / (coor->c.x - coor->a.x);
		SDL_SetRenderDrawColor(p->ren, 50, 100, 100, 255);
		if (up.y < 0)
			up.y = 0;
		if (down.y > WINH)
			down.y = WINH;
		drawline(&up, &down, p);
		up.y = WINH;
		drawline(&up, &down, p);
		i++;
		if (i > coor->max)
		{
			break;
		}
	}

}

void		wewillbuildaportal(t_qdpos *coor, t_param *p, int port, int i)
{
	t_qdpos		upper;
	t_qdpos		lower;
	double		tmp1;
	double		tmp2;

	upper = *coor;
	getcoor(&upper, p, i, port - 1);
	lower = upper;
	tmp1 = upper.b.y;
	tmp2 = upper.d.y;
	upper.b.y = upper.a.y;
	upper.d.y = upper.c.y;
	upper.a.y = coor->a.y;
	upper.c.y = coor->c.y;

	lower.a.y = tmp1;
	lower.c.y = tmp2;
	lower.b.y = coor->b.y;
	lower.d.y = coor->d.y;
	wewillbuildupper(&upper, p, 0);
	wewillbuildlower(&lower, p, 0);
	SDL_SetRenderDrawColor(p->ren, 255, 255, 255, 255);
	if (upper.c.y < upper.d.y)
		drawline(&upper.d, &upper.b, p);
	//	drawline(&upper.a, &upper.c, p);
	//	drawline(&upper.a, &upper.b, p);
	//	drawline(&upper.d, &upper.c, p);
	//	drawline(&lower.b, &lower.a, p);
	//	drawline(&lower.d, &lower.c, p);
	//	drawline(&lower.b, &lower.d, p);
	if (lower.c.y < lower.d.y)
		drawline(&lower.a, &lower.c, p);
}

void		wewillbuildawall(t_qdpos *coor, t_param *p, t_wall *w)
{
	double	i;
	t_dpos	up;
	t_dpos	down;
	double	ang;

//	ang = getangle(w->a, w->b, p->map->pos);
	i = coor->a.x;
	while (i < coor->c.x)
	{
		if (i < coor->min)
			i = coor->min;
		up.x = i;
		down.x = i;
		down.y = 0;
		up.y = coor->a.y + (i - coor->a.x) * (coor->c.y - coor->a.y) / (coor->c.x - coor->a.x);
		SDL_SetRenderDrawColor(p->ren, 100, 100, 100, 255);
//		if (up.y < 0)
//			up.y = 0;
		drawline(&up, &down, p);
		down.y = coor->b.y + (i - coor->b.x) * (coor->d.y - coor->b.y) / (coor->c.x - coor->a.x);
//		if (down.y > WINH)
//			down.y = WINH;
		p->dx = ((up.x - coor->a.x) / (coor->c.x - coor->a.x) * (w->xpix));
		p->dx %= p->xxx->h;
//		SDL_SetRenderDrawColor(p->ren, 244, 244, 244, 255);
//		drawline(&up, &down, p);
		drawtexedline(&up, &down, p, w);
		up.y = WINH;
		SDL_SetRenderDrawColor(p->ren, 50, 100, 100, 255);
		drawline(&up, &down, p);
		i++;
		if (i > coor->max)
			break;
	}
}

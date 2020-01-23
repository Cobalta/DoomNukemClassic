/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   coordscalculator.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tprzybyl <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/18 14:50:09 by tprzybyl     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/18 14:52:32 by tprzybyl    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

void		ordercoords(t_qdpos *coor)
{
	t_dpos tmp;

	if (coor->a.x > coor->c.x)
	{
		tmp = coor->c;
		coor->c = coor->a;
		coor->a = tmp;
		tmp = coor->d;
		coor->d = coor->b;
		coor->b = tmp;
	}
}

void		getcoor(t_qdpos *coor, t_param *p, int i, int k)
{
	t_dpos		plaim;
	t_dpos		amov;
	t_dpos		bmov;
	t_dpos		zmov;

	double		perc;
	double		x1;
	double		x2;
	double		y1a;
	double		y2a;
	double		y1b;
	double		y2b;

	plaim.x = 750; plaim.y = 550;
	amov.x = p->map->sect[k].wall[i].a.x - p->map->pos.x;
	zmov.x = p->map->sect[k].wall[i].a.y - p->map->pos.y;
	bmov.x = p->map->sect[k].wall[i].b.x - p->map->pos.x;
	zmov.y = p->map->sect[k].wall[i].b.y - p->map->pos.y;
	amov.y = 550 - (amov.x * cos(p->map->ang) + zmov.x * sin(p->map->ang));
	bmov.y = 550 - (bmov.x * cos(p->map->ang) + zmov.y * sin(p->map->ang));
	amov.x = 750 - (amov.x * sin(p->map->ang) - zmov.x * cos(p->map->ang));
	bmov.x = 750 - (bmov.x * sin(p->map->ang) - zmov.y * cos(p->map->ang));

	if (plaim.y < bmov.y && plaim.y >= amov.y)
	{
		perc = percent(amov.y, bmov.y, plaim.y);
		bmov.y = plaim.y - 1;
		bmov.x = 750 + (seekpercent(amov.x - 750, bmov.x - 750, perc));
	}
	else if (plaim.y < amov.y && plaim.y >= bmov.y)
	{
		perc = percent(bmov.y, amov.y, plaim.y);
		amov.y = plaim.y - 1;
		amov.x = 750 + (seekpercent(bmov.x - 750, amov.x - 750, perc));
	}
	x1 = -(amov.x - 750) * 1000 / (amov.y - 550);
	x2 = -(bmov.x - 750) * 1000 / (bmov.y - 550);
	y1a = (p->map->sect[k].top + p->diff) / (amov.y - 550);
	y1b = (p->map->sect[k].bot + p->diff) / (amov.y - 550);
	y2a = (p->map->sect[k].top + p->diff) / (bmov.y - 550);
	y2b = (p->map->sect[k].bot + p->diff) / (bmov.y - 550);
	coor->a.x = WINL/2 + x1;
	coor->a.y = WINH/2 + y1a;
	coor->b.x = WINL/2 + x1;
	coor->b.y = WINH/2 + y1b;
	coor->c.x = WINL/2 + x2;
	coor->c.y = WINH/2 + y2a;
	coor->d.x = WINL/2 + x2;
	coor->d.y = WINH/2 + y2b;
	ordercoords(coor);
	if (plaim.y >= amov.y || plaim.y >= bmov.y)
		coor->go = 1;
	else
		coor->go = 0;
}

int			getwall(t_param *p, int ow, int os, int ns)
{
	int i;

	ns--;
	i = 0;
	while (i < p->map->sect[ns].cwall)
	{
		if ((p->map->sect[ns].wall[i].a.x == p->map->sect[os].wall[ow].a.x &&
					p->map->sect[ns].wall[i].a.y == p->map->sect[os].wall[ow].a.y &&
					p->map->sect[ns].wall[i].b.x == p->map->sect[os].wall[ow].b.x &&
					p->map->sect[ns].wall[i].b.y == p->map->sect[os].wall[ow].b.y) ||
				(p->map->sect[ns].wall[i].a.x == p->map->sect[os].wall[ow].b.x &&
				 p->map->sect[ns].wall[i].a.y == p->map->sect[os].wall[ow].b.y &&
				 p->map->sect[ns].wall[i].b.x == p->map->sect[os].wall[ow].a.x &&
				 p->map->sect[ns].wall[i].b.y == p->map->sect[os].wall[ow].a.y))
			return (i);
		i++;
	}
	return (0);
}

void		tiny_function(t_param *p, int i, int min, int max, int ans)
{
	t_qdpos		coor;

	getcoor(&coor, p, i, p->actual);
	if (coor.go)
	{
		if (coor.a.x < max && coor.c.x > min)
		{
			if (p->map->sect[p->actual].wall[i].portal && p->map->sect[p->actual].wall[i].portal != ans)
			{
				ans = p->actual + 1;
				drawsector(p, p->map->sect[p->actual].wall[i].portal,(coor.a.x < min) ? min : (int)coor.a.x, (coor.c.x > max)? max : (int)coor.c.x, ans);
				coor.min = min;
				coor.max = max;
				wewillbuildaportal(&coor, p, p->map->sect[ans-1].wall[i].portal, getwall(p, i, ans - 1, p->map->sect[ans-1].wall[i].portal));
				SDL_SetRenderDrawColor(p->ren, 255, 255, 255, 255);
				drawline(&coor.a, &coor.b, p);
				drawline(&coor.a, &coor.c, p);
				drawline(&coor.d, &coor.b, p);
				drawline(&coor.c, &coor.d, p);
			}
			else if (p->map->sect[p->actual].wall[i].portal != ans)
			{
				coor.min = min;
				coor.max = max;
				wewillbuildawall(&coor, p, &p->map->sect[p->actual].wall[i]);
				SDL_SetRenderDrawColor(p->ren, 255, 255, 255, 255);
				drawline(&coor.a, &coor.b, p);
				drawline(&coor.a, &coor.c, p);
				drawline(&coor.d, &coor.b, p);
				drawline(&coor.c, &coor.d, p);
			}
		}
	}
}

#include "../includes/doom.h"

void		renderentities(t_param *p, int max[2], int w)
{
	t_qdpos		coor;

	getentitycoor(&coor, p, p->map->sortentities[w],
	p->map->sortentities[w].pz);
	if (coor.a.x < max[1] && coor.c.x > max[0] && coor.go)
	{
		coor.min = max[0];
		coor.max = max[1];
		wewillbuildanentity(&coor, p, &p->map->sortentities[w]);
	}
}

static void	drawportal(t_param *p, int max[2], int ans, t_qdpos coor)
{
	t_qdpos		newcoor;
	int			w;
	int			tmp[2];

	w = coor.go;
	ans = p->actual + 1;
	tmp[0] = (coor.a.x < max[0]) ? max[0] : (int)coor.a.x;
	tmp[1] = (coor.c.x > max[1]) ? max[1] : (int)coor.c.x;
	drawsector(p, p->map->sect[p->actual].wall[w].portal, tmp, ans);
	getcoor(&newcoor, p, getwall(w,
	&p->map->sect[ans - 1], &p->map->sect[p->actual]),
	p->map->sect[ans - 1].wall[w].portal - 1);
	buildaportal(coor, p, newcoor,
	&p->map->sect[ans - 1].wall[w]);
}

void		render(t_param *p, int w, int max[2], int ans)
{
	t_qdpos		coor;

	getcoor(&coor, p, w, p->actual);
	if (coor.a.x < max[1] && coor.c.x > max[0] && coor.go)
	{
		coor.min = max[0];
		coor.max = max[1];
		if (p->map->sect[p->actual].wall[w].portal &&
		p->map->sect[p->actual].wall[w].portal != ans)
		{
			coor.go = w;
			drawportal(p, max, ans, coor);
		}
		else if (p->map->sect[p->actual].wall[w].portal != ans)
		{
			wewillbuildawall(&coor, p,
			&p->map->sect[p->actual].wall[w]);
		}
	}
}

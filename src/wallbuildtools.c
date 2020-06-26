#include "../includes/doom.h"

int			sctnb(t_wall *w, t_param *p)
{
	int		i;

	i = -1;
	while (i++ < p->map->ctsector)
	{
		if (w->sect == &p->map->sect[i])
			return (i + 1);
	}
	return (1);
}

void		drawcline(t_dpos *up, t_dpos *down, t_param *p, int c)
{
	c = c * 3;
	if (c <= 0)
		setcolor(&p->col, 181 + c, 148 + c, 117 + c);
	else
		setcolor(&p->col, 99 + c, 75 + c, 53 + c);
	drawline(up, down, p);
}

void		startingvalues(t_qdpos *coor, t_dpos *up, t_dpos *down, int i)
{
	up->x = i;
	down->x = i;
	down->y = 0;
	up->y = coor->a.y + (i - coor->a.x) * (coor->c.y - coor->a.y) /
	(coor->c.x - coor->a.x);
}

void		lowerstartingvalues(t_qdpos *coor, t_dpos *up, t_dpos *down, int i)
{
	up->x = i;
	down->x = i;
	up->y = coor->a.y + (i - coor->a.x) * (coor->c.y - coor->a.y) /
	(coor->c.x - coor->a.x);
}

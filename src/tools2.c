#include "../includes/doom.h"

void		setcleanactmap(t_param *p)
{
	int i;
	int j;

	i = 0;
	while (i < WINL)
	{
		j = 0;
		while (j < WINH)
		{
			p->actmap[i][j].data = NULL;
			j++;
		}
		i++;
	}
	i = -1;
	while (i++ < p->map->centities)
		p->map->entities[i].lock = 1;
}

int			getwall(int ow, t_sector *os, t_sector *ns)
{
	int i;

	i = 0;
	while (i < ns->cwall)
	{
		if ((ns->wall[i].a.x == os->wall[ow].a.x &&
			ns->wall[i].a.y == os->wall[ow].a.y &&
			ns->wall[i].b.x == os->wall[ow].b.x &&
			ns->wall[i].b.y == os->wall[ow].b.y) ||
			(ns->wall[i].a.x == os->wall[ow].b.x &&
			ns->wall[i].a.y == os->wall[ow].b.y &&
			ns->wall[i].b.x == os->wall[ow].a.x &&
			ns->wall[i].b.y == os->wall[ow].a.y))
			return (i);
		i++;
	}
	error_func(0);
	return (0);
}

int			angark(double ang, double relang, double fov)
{
	fov /= 2;
	if (ang + fov >= 6.28 && ((relang >= ang - fov && relang <= 6.28) ||
		(relang >= 0 && relang <= (ang + fov - 6.28))))
		return (1);
	else if (ang - fov <= 0 && ((relang >= 0 && relang <= ang + fov) ||
		(relang >= 6.28 + (ang - fov) && relang <= 6.28)))
		return (1);
	else if (relang >= ang - fov && relang <= ang + fov)
		return (1);
	return (0);
}

double		distentz(t_entity *ent, t_map *map)
{
	double	z;
	double	l;

	z = (ent->pz - map->pz) / 1000;
	l = (sqrt(((ent->pos.x - map->pos.x)
			* (ent->pos.x - map->pos.x)
			+ ((ent->pos.y - map->pos.y)
			* (ent->pos.y - map->pos.y)))));
	return (sqrt(l * l + z * z));
}

double		distent(t_dpos ent, t_dpos pos)
{
	return (sqrt(((ent.x - pos.x) * (ent.x - pos.x)
		+ ((ent.y - pos.y) * (ent.y - pos.y)))));
}

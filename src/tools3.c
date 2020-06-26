#include "../includes/doom.h"

static int	verttwo(t_dpos i, t_dpos j, t_dpos k, t_dpos l)
{
	double a;
	double b;
	double y;

	if (i.y == j.y && 1 == ft_isbetween(i.x, j.x, k.x))
		return (1);
	if (i.y == j.y && 1 != ft_isbetween(i.x, j.x, k.x))
		return (0);
	a = (j.y - i.y) / (j.x - i.x);
	b = i.y - (a * i.x);
	y = a * k.x + b;
	if (ft_isbetween(i.y, j.y, y) && ft_isbetween(k.y, l.y, y))
		return (1);
	else
		return (0);
}

static int	vertone(t_dpos i, t_dpos j, t_dpos k, t_dpos l)
{
	double a;
	double b;
	double y;

	a = (l.y - k.y) / (l.x - k.x);
	b = k.y - (a * k.x);
	y = a * i.x + b
		;
	if (ft_isbetween(i.y, j.y, y) && ft_isbetween(k.y, l.y, y))
		return (1);
	else
		return (0);
}

int			crossline(t_dpos i, t_dpos j, t_dpos k, t_dpos l)
{
	t_dpos a;
	t_dpos b;
	double x;

	if (i.x == j.x)
		return (vertone(i, j, k, l));
	if (k.x == l.x)
		return (verttwo(i, j, k, l));
	a.x = (j.y - i.y) / (j.x - i.x);
	a.y = (l.y - k.y) / (l.x - k.x);
	if (a.x == a.y)
		return (0);
	b.x = i.y - (a.x * i.x);
	b.y = k.y - (a.y * k.x);
	x = (b.y - b.x) / (a.x - a.y);
	if (ft_isbetween(i.x, j.x, x) && ft_isbetween(k.x, l.x, x))
		return (1);
	else
		return (0);
}

void		copyentities(t_map *map)
{
	int i;

	i = -1;
	while (i++ < map->centities)
		map->sortentities[i] = map->entities[i];
}

void		orderentities(t_entity *ent, int max, t_dpos pos)
{
	int			i;
	int			go;
	t_entity	tmp;

	go = 1;
	while (go)
	{
		go = 0;
		i = -1;
		while (i++ < max - 2)
		{
			if (distent(ent[i].pos, pos) < distent(ent[i + 1].pos, pos))
			{
				go = 1;
				tmp = ent[i];
				ent[i] = ent[i + 1];
				ent[i + 1] = tmp;
			}
		}
	}
}

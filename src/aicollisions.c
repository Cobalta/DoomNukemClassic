#include "../includes/doom.h"

int		aiportalcoll(t_map *map, t_entity *ent, t_dpos dest, int i)
{
	t_sector *sect;

	sect = &map->sect[ent->os];
	if (!sect->wall[i].portal)
		return (0);
	if (sect->wall[i].portal)
	{
		if (ent->pz + 4000 > map->sect[sect->wall[i].portal - 1].top ||
				ent->pz + 3000 < map->sect[sect->wall[i].portal - 1].bot)
			return (0);
		if (!aireccolls(map, ent, dest, i))
			return (0);
		ent->psct = sect->wall[i].portal;
	}
	return (1);
}

int		aireccolls(t_map *map, t_entity *ent, t_dpos dest, int ow)
{
	int			i;
	t_sector	*sect;
	t_sector	*os;

	os = &map->sect[ent->os];
	sect = &map->sect[os->wall[ow].portal - 1];
	i = 0;
	while (i < sect->cwall)
	{
		if (crossline(ent->pos, dest, sect->wall[i].a, sect->wall[i].b) &&
				i != getwall(ow, os, sect))
		{
			ent->os = os->wall[ow].portal - 1;
			return (aiportalcoll(map, ent, dest, i));
		}
		i++;
	}
	return (1);
}

int		aicheckcolls(t_map *map, t_entity *ent, double x, double y)
{
	int			i;
	t_dpos		dest;
	t_sector	*sect;

	sect = &map->sect[ent->psct - 1];
	dest.x = x;
	dest.y = y;
	i = 0;
	while (i < sect->cwall)
	{
		if (crossline(ent->pos, dest, sect->wall[i].a, sect->wall[i].b))
		{
			ent->os = ent->psct - 1;
			return (aiportalcoll(map, ent, dest, i));
		}
		i++;
	}
	return (1);
}

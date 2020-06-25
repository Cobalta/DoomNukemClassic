
#include "../includes/doom.h"

void		xpixlensandart(t_wall *w, char **str, t_param *p)
{
	int a;
	int b;
	int c;

	a = w->a.x - w->b.x;
	a *= a;
	b = w->a.y - w->b.y;
	b *= b;
	c = a + b;
	w->xpix = sqrt(c);
	w->xpix *= 12.8;
	w->art = p->art[nextatoi(str, 0, 0)];
	if (w->portal)
		w->botart = p->art[nextatoi(str, 0, 0)];
}

static void	correct_portals_ypix(t_map *map)
{
	int	i;
	int j;

	i = -1;
	while (++i < map->ctsector)
	{
		j = -1;
		while (++j < map->sect[i].cwall)
		{
			if (map->sect[i].wall[j].portal)
			{
				map->sect[i].wall[j].ypix = 0.0128
						* ((map->sect[i].top
						- map->sect[map->sect[i].wall[j].portal - 1].top));
				map->sect[i].wall[j].botypix = 0.0128
						* ((map->sect[map->sect[i].wall[j].portal
						- 1].bot - map->sect[i].bot));
			}
		}
	}
}

static void	map_setup(t_map *map)
{
	map->hp = 100;
	map->status = 4;
	map->speed.x = 0;
	map->speed.y = 0;
	map->speed.z = 0;
	map->pcrouch = 0;
	map->powert = 0;
	map->power = 0;
	map->defence = 0;
	map->alock = 0;
	map->fly = 0;
	map->basepos.y = map->pos.y;
	map->basepos.x = map->pos.x;
	map->baseang = map->ang;
	map->basepsct = map->psct;
}

static void	readmap2(t_map *map, char *str, t_param *param)
{
	int i;

	i = 0;
	while (i < map->ctsector)
	{
		map->sect[i].id = i + 1;
		readsector(&str, &map->sect[i], param);
		i++;
	}
	map->pz = map->sect[map->psct - 1].bot;
	map->centities = nextatoi(&str, 0, 0);
	if (map->centities > 512)
		error_func(-1);
	i = 0;
	while (i < map->centities)
	{
		readentities(&str, &map->entities[i], param, map);
		i++;
	}
	checkend(&str);
	correct_portals_ypix(map);
	createweapon_2hsword(&map->weaplst[0]);
	param->map = map;
}

void		readmap(int fd, t_param *param)
{
	char		*str;
	char		*tmp;
	t_map		*map;

	if (!(map = malloc(sizeof(t_map))))
		error_func(-1);
	if (!(str = ft_strdup("")))
		error_func(-1);
	if (!(ft_strgetfrom(fd, &str)))
		error_func(-1);
	tmp = str;
	nextatoi(&str, 0, 0);
	map->pos.x = nextatoi(&str, 0, 0);
	map->pos.y = nextatoi(&str, 0, 0);
	map->ang = nextatoi(&str, 0, 0);
	map->psct = nextatoi(&str, 0, 0);
	map->ctsector = nextatoi(&str, 0, 0);
	map_setup(map);
	map->sect = malloc(sizeof(t_sector) * map->ctsector);
	readmap2(map, str, param);
	ft_strdel(&tmp);
}

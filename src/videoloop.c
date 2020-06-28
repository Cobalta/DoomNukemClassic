#include "../includes/doom.h"

static void	drawminimap(t_param *p, t_map *map, t_dpos dest)
{
	int		i;
	int		j;
	t_dpos	edst;

	drawline(&map->pos, &dest, p);
	i = 0;
	while (i < map->ctsector)
	{
		j = 0;
		while (j < map->sect[i].cwall)
		{
			drawline(&map->sect[i].wall[j].a, &map->sect[i].wall[j].b, p);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < map->centities)
	{
		edst.x = map->entities[i].pos.x + 3 * cos(map->entities[i].ang);
		edst.y = map->entities[i].pos.y + 3 * sin(map->entities[i].ang);
		(map->entities[i].type == 1 && map->entities[i].hp > 0) ?
		drawline(&map->entities[i].pos, &edst, p) : 0;
		i++;
	}
}

void		drawsector(t_param *p, int actual, int max[2], int ans)
{
	int			i;

	i = 0;
	while (i < p->map->sect[actual - 1].cwall)
	{
		p->actual = actual - 1;
		render(p, i, max, ans);
		i++;
	}
	i = 0;
	while (i < p->map->centities)
	{
		if (p->map->sortentities[i].psct == actual)
		{
			renderentities(p, max, i);
		}
		i++;
	}
}

static void	setypix(t_map *map)
{
	int i;
	int j;
	int ypix;

	i = 0;
	while (i < map->ctsector)
	{
		ypix = 0.0128 * ((map->sect[i].top - map->sect[i].bot));
		j = 0;
		while (j < map->sect[i].cwall)
		{
			if (map->sect[i].wall[j].portal)
			{
				map->sect[i].wall[j].ypix = 0.0128 * ((map->sect[i].top -
				map->sect[map->sect[i].wall[j].portal - 1].top));
				map->sect[i].wall[j].botypix = 0.0128 * ((map->sect
				[map->sect[i].wall[j].portal - 1].bot - map->sect[i].bot));
			}
			else
				map->sect[i].wall[j].ypix = ypix;
			j++;
		}
		i++;
	}
}

void		videoloop(t_param *p)
{
	t_dpos		dest;
	int			max[2];

	p->map->ang = (p->map->ang < .005 && p->map->ang > -.005) ? 0 : p->map->ang;
	setcleanactmap(p);
	ratartpick(p, p->map->entities, p->map->centities, p->map->pos);
	copyentities(p->map);
	orderentities(p->map->sortentities, p->map->centities, p->map->pos);
	setypix(p->map);
	max[0] = 0;
	max[1] = WINL;
	drawsector(p, p->map->psct, max, p->map->psct);
	dest.x = p->map->pos.x + 7 * cos(p->map->ang);
	dest.y = p->map->pos.y + 7 * sin(p->map->ang);
	show_hud(p);
	setcolor(&p->col, 255, 255, 255);
	drawminimap(p, p->map, dest);
	SDL_RenderClear(p->ren);
	SDL_DestroyTexture(p->texture);
	p->texture = SDL_CreateTextureFromSurface(p->ren, p->surf);
	SDL_RenderCopy(p->ren, p->texture, NULL, NULL);
	SDL_RenderPresent(p->ren);
	p->diff = -5000 + p->map->pcrouch - p->map->pz;
}

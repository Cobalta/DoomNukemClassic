/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mapparsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tprzybyl <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/07 15:26:42 by tprzybyl     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/25 16:41:22 by tprzybyl    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

static void		getpixlens(t_wall *w)
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
}

static void		readsector(char **str, t_sector *s, t_param *p, int t)
{
	int		i;
	int		ypix;

	s->cwall = ft_atoinext(str);
	s->top = ft_atoinext(str);
	s->bot = ft_atoinext(str);
	ypix = 12.8 * ((s->top - s->bot) / 1000);
	s->wall = malloc(sizeof(t_wall) * s->cwall);
	i = 0;
	while (i < s->cwall)
	{
		s->wall[i].a.x = ft_atoinext(str);
		s->wall[i].a.y = ft_atoinext(str);
		s->wall[i].b.x = ft_atoinext(str);
		s->wall[i].b.y = ft_atoinext(str);
		s->wall[i].portal = ft_atoinext(str);
		s->wall[i].ypix = ypix;
		getpixlens(&s->wall[i]);
		printf("%d - %d\n", s->wall[i].xpix, s->wall[i].ypix);
		i++;
	}
}

void			readmap(int fd, t_param *param)
{
	char		*str;
	char		*tmp;
	int			i;
	t_map		*map;

	if (!(map = malloc(sizeof(t_map))))
		error_func(-1);
	if (!(str = ft_strdup("")))
		error_func(-1);
	if (!(ft_strgetfrom(fd, &str)))
		error_func(-1);
	tmp = str;
	ft_atoinext(&str);
	map->pos.x = ft_atoinext(&str);
	map->pos.y = ft_atoinext(&str);
	map->ang = ft_atoinext(&str);
	map->psct = ft_atoinext(&str);
	map->basepos.y = map->pos.y;
	map->basepos.x = map->pos.x;
	map->baseang = map->ang;
	map->basepsct = map->psct;
	map->ctsector = ft_atoinext(&str);
	map->sect = malloc(sizeof(t_sector) * map->ctsector);
	i = 0;
	while (i < map->ctsector)
	{
		readsector(&str, &map->sect[i], param, i);
		i++;
	}
	ft_strdel(&tmp);
	param->map = map;
}

#include "doom.h"

void	draw_outline(t_param *p, int a, int b)
{
	t_dpos hud1;
	t_dpos hud2;

	hud1.x = a;
	hud1.y = WINH - 51;
	hud2.x = a;
	hud2.y = WINH - 30;
	drawline(&hud1, &hud2, p);
	hud2.x = b;
	hud2.y = WINH - 51;
	drawline(&hud1, &hud2, p);
	hud1.x = b;
	hud1.y = WINH - 30;
	drawline(&hud1, &hud2, p);
	hud2.x = a;
	hud2.y = WINH - 30;
	drawline(&hud1, &hud2, p);
}

void	draw_health(t_param *p)
{
	int i;
	int y;
	int r;
	draw_outline(p, 49, 250);
	r = 50;
	i = 0;
	y = 0;
	while (i < p->map->hp * 2)
	{
		y = 0;
		while (y < 20)
		{
			put_pixel(p->surf, i + 50, WINH - 50 + y, SDL_MapRGB(p->surf->format, r, y*2, y*4));
			y++;
		}
		r++;
		i++;
	}

}

void	draw_stamina(t_param *p)
{
	int i;
	int y;
	int g;
	draw_outline(p, WINL - 246, WINL - 49);
	g = 50;
	i = 0;
	y = 0;
	while (i < p->map->defence * 14)
	{
		y = 0;
		while (y < 20)
		{
			put_pixel(p->surf, WINL - i - 50, WINH - 50 + y, SDL_MapRGB(p->surf->format, y*2, g, y*4));
			y++;
		}
		g++;
		i++;
	}

}

void	show_hud(t_param *p)
{
	draw_health(p);
	draw_stamina(p);
}
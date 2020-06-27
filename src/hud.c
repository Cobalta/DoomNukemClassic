#include "../includes/doom.h"

static void	write_timer(t_param *p, int timer, SDL_Color c)
{
	SDL_Surface	*text;
	SDL_Rect	pos;

	if (timer > 0)
	{
		if (timer > 200)
		{
			p->font = TTF_OpenFont("Textures/Gameplay.ttf", 50);
			text = TTF_RenderText_Blended(p->font, "SPEED!", c);
			pos.x = WINL / 2 - (text->w / 2);
			pos.y = WINH / 2 - (text->h / 2) - 100;
			SDL_BlitSurface(text, NULL, p->surf, &pos);
			TTF_CloseFont(p->font);
			SDL_FreeSurface(text);
		}
		p->font = TTF_OpenFont("Textures/Gameplay.ttf", 20);
		text = TTF_RenderText_Solid(p->font, ft_itoa(timer), c);
		pos.x = WINL / 2 - (text->w / 2);
		pos.y = WINH - text->h - 20;
		SDL_BlitSurface(text, NULL, p->surf, &pos);
		TTF_CloseFont(p->font);
		SDL_FreeSurface(text);
	}
}

void		draw_health(t_param *p)
{
	int i;
	int y;
	int r;

	r = 50;
	i = 0;
	y = 0;
	while (i < (WINL * 0.3125 - WINL * 0.0625) *
			((double)p->map->hp / 100.0))
	{
		y = 0;
		while (y < WINH * 0.95 - WINH * 0.92)
		{
			put_pixel(p->surf, i + WINL * 0.0625, WINH * 0.92
					+ y, SDL_MapRGB(p->surf->format, r, y * 2, y * 4));
			y++;
		}
		r++;
		i++;
	}
}

void		draw_stamina(t_param *p)
{
	int i;
	int y;
	int g;

	g = 50;
	i = 0;
	y = 0;
	while (i < (WINL * 0.9375 - WINL * 0.6925) *
			((double)p->map->defence / p->map->weaplst[0].defence))
	{
		y = 0;
		while (y < WINH * 0.95 - WINH * 0.92)
		{
			put_pixel(p->surf, WINL * 0.9375 - i, WINH * 0.92
					+ y, SDL_MapRGB(p->surf->format, y * 2, g, y * 4));
			y++;
		}
		g++;
		i++;
	}
}

void		show_hud(t_param *p)
{
	SDL_Color c;

	c.r = 0;
	c.g = 0;
	c.b = 0;
	hudelement(p, p->map->weaplst[0].art[p->map->status]);
	draw_health(p);
	draw_stamina(p);
	hudelement(p, p->art[22]);
	if (p->map->power == 1)
		hudelement(p, p->art[15]);
	write_timer(p, p->map->powert, c);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:32:06 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/12 18:05:07 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		mouse_motion_event(SDL_Event event, t_param *p)
{
	if (event.motion.xrel != 0)
		p->map->ang += event.motion.xrel * .005;
	if (event.motion.yrel != 0)
		p->consty -= event.motion.yrel * 4;
	p->consty = (p->consty > 1500) ? 1500 : p->consty;
	p->consty = (p->consty < -1500) ? -1500 : p->consty;
	SDL_SetRelativeMouseMode(SDL_ENABLE);
	SDL_WarpMouseInWindow(p->win, WINH / 2, WINL / 2);
}

void		draw_press(t_param *p, int timer)
{
	SDL_Surface	*text;
	SDL_Rect	pos;
	SDL_Color	c;

	c.r = 0;
	c.g = 0;
	c.b = 0;
	p->font = TTF_OpenFont("Textures/Gameplay.ttf", 30);
	text = TTF_RenderText_Blended(p->font, "Press any key to start!", c);
	pos.x = WINL / 2 - (text->w / 2);
	pos.y = WINH - (text->h / 2) - 50;
	SDL_FreeSurface(text);
	if ((timer >= 25 && timer < 50) || timer > 75)
	{
		text = TTF_RenderText_Blended(p->font, "Press any key to start!", c);
		SDL_BlitSurface(text, NULL, p->surf, &pos);
		SDL_FreeSurface(text);
	}
	TTF_CloseFont(p->font);
}

void		start_menu(t_param *p)
{
	int			timer;
	SDL_Event	event;

	timer = 75;
	while (1)
	{
		hudelement(p, p->art[30]);
		SDL_PollEvent(&event);
		if (event.type == SDL_KEYDOWN && timer <= 50)
			break ;
		draw_press(p, timer);
		timer--;
		if (timer <= 0)
			timer = 50;
		SDL_RenderClear(p->ren);
		SDL_DestroyTexture(p->texture);
		p->texture = SDL_CreateTextureFromSurface(p->ren, p->surf);
		SDL_RenderCopy(p->ren, p->texture, NULL, NULL);
		SDL_RenderPresent(p->ren);
	}
}

SDL_Event	event_manager(t_param *p, const Uint8 **keystat)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		*keystat = SDL_GetKeyboardState(NULL);
		if (event.type == SDL_KEYDOWN)
			key_event(*keystat, p, &event);
		if (event.type == SDL_MOUSEBUTTONDOWN)
			mouse_button_event(event, p);
		if (event.type == SDL_MOUSEMOTION)
			mouse_motion_event(event, p);
	}
	return (event);
}

void		loop(t_param *p, SDL_Event event)
{
	const Uint8	*keystat;

	while (1)
	{
		event = event_manager(p, &keystat);
		if (event.type == SDL_QUIT || key_event(keystat, p, &event)
		|| p->map->hp <= 0 || p->map->cburrows == 0)
			break ;
		gameloop(p, keystat);
		videoloop(p);
	}
}

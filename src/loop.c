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

void			set_mouse(t_param *p)
{
	SDL_SetRelativeMouseMode(SDL_ENABLE);
	SDL_WarpMouseInWindow(p->win, WINH / 2, WINL / 2);
}

void		mouse_motion_event(SDL_Event event, t_param *p)
{
	if (event.motion.xrel != 0)
		p->map->ang += event.motion.xrel * .01;
	if (event.motion.yrel != 0)
		p->consty -= event.motion.yrel * 4;
	p->consty = (p->consty > 1500) ? 1500 : p->consty;
	p->consty = (p->consty < -1500) ? -1500 : p->consty;
	set_mouse(p);
}

void	draw_press(t_param *p, int timer)
{
	SDL_Surface	*text;
	SDL_Rect 	pos;
	SDL_Color 	c;

	text = TTF_RenderText_Blended(p->font, "Press any key to start!", c);
	c.r = 0;
	c.g = 0;
	c.b = 0;
	pos.x = WINL / 2 - (text->w / 2);
	pos.y = WINH - (text->h / 2) - 50;
	if ((timer >= 25 && timer < 50) || timer > 75)
	{
		text = TTF_RenderText_Blended(p->font, "Press any key to start!", c);
		SDL_BlitSurface(text, NULL, p->surf, &pos);
	}
}

void	start_menu(t_param *p)
{
	int 		timer;
	SDL_Event	event;

	timer = 100;
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

void			loop(t_param *p)
{
	static int	ntime;
	static int	otime;
	static int	timer = 50;
	SDL_Event	event;
	const Uint8	*keystat;
	Mix_Music	*music;

	music = Mix_LoadMUS("sounds/doot.wav");
	Mix_VolumeMusic(MIX_MAX_VOLUME / 8);
	Mix_PlayMusic(music, -1);
	Mix_PauseMusic();
	setcleanactmap(p);
	set_mouse(p);
	otime = SDL_GetTicks();
	start_menu(p);
	while (1)
	{
		if (SDL_GetTicks() % 10 == 0)
		{
			otime = ntime;
			while (SDL_PollEvent(&event))
			{
				keystat = SDL_GetKeyboardState(NULL);
				if (event.type == SDL_KEYDOWN)
					key_event(keystat, p, &event);
				if (event.type == SDL_MOUSEBUTTONDOWN)
					mouse_button_event(event, p);
				if (event.type == SDL_MOUSEMOTION)
					mouse_motion_event(event, p);
			}
			if (event.type == SDL_QUIT || key_event(keystat, p, &event)
			|| p->map->hp <= 0)
				break ;
			ntime = SDL_GetTicks();
			gameloop(p, event, keystat);
			if (timer <= 0)
			{
				videoloop(p);
				timer = 50;
			}
			timer -= (ntime - otime);
		}
	}
	Mix_FreeMusic(music);
}

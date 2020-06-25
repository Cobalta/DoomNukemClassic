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

void			loop(t_param *p)
{
	static int ntime;
	static int otime;
	static int timer = 50;
	SDL_Event	event;
	const Uint8	*keystat;
	Mix_Music *music;
	music = Mix_LoadMUS("sounds/doot.wav");
	Mix_VolumeMusic(MIX_MAX_VOLUME / 8);
	Mix_PlayMusic(music, -1);
	Mix_PauseMusic();
	setcleanactmap(p);
	set_mouse(p);
	otime = SDL_GetTicks();
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
			if (event.type == SDL_QUIT || key_event(keystat, p, &event) || p->map->hp <= 0)
				break;
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

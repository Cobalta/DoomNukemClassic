/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:32:06 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/12 17:25:39 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
	SDL_Event	event;
	const Uint8	*keystat;
	Mix_Music *music;
	music = Mix_LoadMUS("sounds/doot.wav");
	Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
	Mix_PlayMusic(music, -1);

	set_mouse(p);
	while (1)
	{
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
		if (event.type == SDL_QUIT || key_event(keystat, p, &event))
			break ;
		printf("ang = %f\n", p->map->ang);
		gameloop(p, event, keystat);
		videoloop(p);
	}
}

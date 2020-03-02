/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:32:06 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/02 17:25:36 by tprzybyl         ###   ########lyon.fr   */
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
		p->consty = (p->consty > 900) ? 900 : p->consty;
		p->consty = (p->consty < -900) ? -900 : p->consty;
	set_mouse(p);
}

int				key_event(const Uint8 *keyboard_state, t_param *p)
{
	if (keyboard_state[SDL_SCANCODE_ESCAPE])
		return (1);
	return (0);
}

void			loop(t_param *p)
{
	SDL_Event	event;
	const Uint8	*keystat;

	set_mouse(p);
	while (1)
	{
		while (SDL_PollEvent(&event))
		{
			keystat = SDL_GetKeyboardState(NULL);
			if (event.type == SDL_KEYDOWN)
				key_event(keystat, p);
			if (event.type == SDL_MOUSEBUTTONDOWN)
				mouse_button_event(event, p);
			if (event.type == SDL_MOUSEMOTION)
				mouse_motion_event(event, p);
		}
		if (event.type == SDL_QUIT || key_event(keystat, p))
			break ;
		gameloop(p, event, keystat);
		videoloop(p);
	}
}

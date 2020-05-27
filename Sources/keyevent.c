/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyevent.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 17:28:49 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/06 19:03:58 by ebourgeo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				key_event(const Uint8 *keystat, t_param *p, SDL_Event *e)
{
	if (keystat[SDL_SCANCODE_ESCAPE])
		return (1);
	if (e->type == SDL_KEYDOWN)
	{
		if (e->key.keysym.scancode == SDL_SCANCODE_M)
			(Mix_PausedMusic() == 1) ? Mix_ResumeMusic() : Mix_PauseMusic();
		if (e->key.keysym.scancode == SDL_SCANCODE_P)
			 p->map->fly = (p->map->fly == 1) ? 0 : 1;
	}
	return (0);
}


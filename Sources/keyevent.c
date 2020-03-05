/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyevent.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 17:28:49 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/05 19:20:46 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				key_event(const Uint8 *keystat, t_param *p, SDL_Event *e)
{
	if (keystat[SDL_SCANCODE_ESCAPE])
		return (1);
	if (keystat[SDL_SCANCODE_M] && !e->key.repeat)
	{
		(Mix_PausedMusic() == 1) ? Mix_ResumeMusic() : Mix_PauseMusic();
	}
	return (0);
}


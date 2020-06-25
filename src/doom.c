/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:31:49 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/06 18:29:09 by ebourgeo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	doom(t_param *p, int fd)
{
	SDL_Event e;
	setup(p);
	readmap(fd, p);
	p->s.music = Mix_LoadMUS("sounds/doot.wav");
	Mix_VolumeMusic(MIX_MAX_VOLUME / 8);
	Mix_PlayMusic(p->s.music, -1);
	Mix_PauseMusic();
	setcleanactmap(p);
	start_menu(p);
	loop(p, e);
	Mix_FreeMusic(p->s.music);
}

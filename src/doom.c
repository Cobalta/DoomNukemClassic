/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <tprzybyl@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:31:49 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/06/25 20:07:43 by tprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	game_over(t_param *p, int win)
{
	SDL_Event	e;
	int			alt;

	if (win == 0)
		alt = 31;
	else
		alt = 32;
	while (1)
	{
		hudelement(p, p->art[alt]);
		SDL_PollEvent(&e);
		if (e.type == SDL_KEYDOWN)
			break ;
		SDL_RenderClear(p->ren);
		SDL_DestroyTexture(p->texture);
		p->texture = SDL_CreateTextureFromSurface(p->ren, p->surf);
		SDL_RenderCopy(p->ren, p->texture, NULL, NULL);
		SDL_RenderPresent(p->ren);
	}
}

void	doom(t_param *p, int fd)
{
	SDL_Event e;

	SDL_PollEvent(&e);
	setup(p);
	readmap(fd, p);
	entitiesinit(p);
	p->s.music = Mix_LoadMUS("sounds/doot.wav");
	Mix_VolumeMusic(MIX_MAX_VOLUME / 8);
	Mix_PlayMusic(p->s.music, -1);
	Mix_PauseMusic();
	setcleanactmap(p);
	start_menu(p);
	loop(p, e);
	if (p->map->hp <= 0)
		game_over(p, 0);
	if (p->map->cburrows <= 0)
		game_over(p, 1);
	freeofdoom(p);
}

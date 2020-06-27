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

#include "../includes/doom.h"

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

void			movement_z2(t_param *p)
{
	if (p->map->pz > p->map->sect[p->map->psct - 1].bot && p->map->fly == 0)
	{
		if (p->map->speed.z > -4000)
			p->map->speed.z += -200;
	}
	if (p->map->pz < p->map->sect[p->map->psct - 1].bot)
	{
		p->map->pz = p->map->sect[p->map->psct - 1].bot;
		if (p->map->speed.z < -800 && p->map->fly == 0)
			Mix_PlayChannel(2, p->s.jump[2], 0);
		p->map->speed.z = 0;
	}
	if (p->map->pz + 5000 > p->map->sect[p->map->psct - 1].top)
	{
		p->map->pz = p->map->sect[p->map->psct - 1].top - 5000;
		p->map->speed.z = 0;
	}
	if (p->map->fly == 0)
		p->map->pz += p->map->speed.z;
}

void			movement_z(const Uint8 *keystat, t_param *p)
{
	if (keystat[SDL_SCANCODE_SPACE] && (p->map->pz ==
	p->map->sect[p->map->psct - 1].bot || p->map->fly == 1))
	{
		if (p->map->fly == 0)
		{
			p->map->speed.z = 1600;
			Mix_PlayChannel(-1, p->s.jump[rand() % 3], 0);
			Mix_PlayChannel(-1, p->s.jump[3], 0);
		}
		else if (p->map->pz + 5400 < p->map->sect[p->map->psct - 1].top)
			p->map->pz += 250;
	}
	if (p->map->fly == 0)
		p->map->pcrouch = (keystat[SDL_SCANCODE_LCTRL]) ? +2500 : 0;
	else
		p->map->pz -= (keystat[SDL_SCANCODE_LCTRL]) ? 250 : 0;
	movement_z2(p);
}

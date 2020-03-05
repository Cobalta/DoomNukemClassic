/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameloop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:30:45 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/05 19:07:54 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			movement_front(const Uint8 *keyboard_state, t_param *p)
{
	if (keyboard_state[SDL_SCANCODE_UP] || keyboard_state[SDL_SCANCODE_W])
	{
		p->map->pspeed.y += (p->map->pspeed.y == 5) ? 1 : 2;
	}
	if (keyboard_state[SDL_SCANCODE_DOWN] || keyboard_state[SDL_SCANCODE_S])
	{
		p->map->pspeed.y -= (p->map->pspeed.y == -4) ? 1 : 2;
	}
	if (p->map->pspeed.y != 0)
	{
		p->map->pspeed.y += (p->map->pspeed.y > 0) ? -1 : 1;
		if (checkcolls(p->map, &p->map->sect[p->map->psct - 1], p->map->pos.x + p->map->pspeed.y * .20 * cos(p->map->ang), p->map->pos.y + p->map->pspeed.y * .20 * sin(p->map->ang)))
		{
			p->map->pos.y += p->map->pspeed.y * .20 * sin(p->map->ang);
			p->map->pos.x += p->map->pspeed.y * .20 * cos(p->map->ang);
		}
	}
}

void			movement_side(const Uint8 *keyboard_state, t_param *p)
{
	if (keyboard_state[SDL_SCANCODE_RIGHT] || keyboard_state[SDL_SCANCODE_D])
	{
		p->map->pspeed.x -= (p->map->pspeed.x == -4) ? 1 : 2;
	}
	if (keyboard_state[SDL_SCANCODE_LEFT] || keyboard_state[SDL_SCANCODE_A])
	{
		p->map->pspeed.x += (p->map->pspeed.x == 4) ? 1 : 2;
	}
	if (p->map->pspeed.x != 0)
	{
		p->map->pspeed.x += (p->map->pspeed.x > 0) ? -1 : 1;
		if (checkcolls(p->map, &p->map->sect[p->map->psct - 1], p->map->pos.x + p->map->pspeed.x * .20 * sin(p->map->ang), p->map->pos.y - p->map->pspeed.x * .20 * cos(p->map->ang)))
		{
			p->map->pos.y -= p->map->pspeed.x * .20 * cos(p->map->ang);
			p->map->pos.x += p->map->pspeed.x * .20 * sin(p->map->ang);
		}
	}
}

void			movement_z(const Uint8 *keystat, t_param *p)
{
	if (keystat[SDL_SCANCODE_SPACE] && p->map->pz == p->map->sect[p->map->psct - 1].bot)
	{
		p->map->pspeed.z = 1600;
	}
	p->map->pcrouch = (keystat[SDL_SCANCODE_LCTRL]) ? 2500 : 0;

	if (p->map->pz > p->map->sect[p->map->psct - 1].bot)
	{
		if (p->map->pspeed.z > -4000)
			p->map->pspeed.z += -200;
	}
	if (p->map->pz < p->map->sect[p->map->psct - 1].bot)
	{
		p->map->pz = p->map->sect[p->map->psct - 1].bot;
		p->map->pspeed.z = 0;
	}

	p->map->pz += p->map->pspeed.z;
}

void			gameloop(t_param *p, SDL_Event event, const Uint8 *keystat)
{
	movement_front(keystat, p);
	movement_side(keystat, p);
	movement_z(keystat, p);
}

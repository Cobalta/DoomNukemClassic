/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameloop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:30:45 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/12 18:11:51 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void			movement_front(const Uint8 *keyboard_state, t_param *p)
{
	if (keyboard_state[SDL_SCANCODE_UP] || keyboard_state[SDL_SCANCODE_W])
	{
		p->map->speed.y += (p->map->speed.y == 5) ? 1 : 2;
	}
	if (keyboard_state[SDL_SCANCODE_DOWN] || keyboard_state[SDL_SCANCODE_S])
	{
		p->map->speed.y -= (p->map->speed.y == -4) ? 1 : 2;
	}
	if (p->map->speed.y != 0)
	{
		p->map->speed.y += (p->map->speed.y > 0) ? -1 : 1;
		if (checkcolls(p->map, &p->map->sect[p->map->psct - 1], p->map->pos.x
					+ p->map->speed.y * .20 * cos(p->map->ang), p->map->pos.y +
					p->map->speed.y * .20 * sin(p->map->ang)))
		{
			p->map->pos.y += p->map->speed.y * .20 * sin(p->map->ang);
			p->map->pos.x += p->map->speed.y * .20 * cos(p->map->ang);
		}
	}
}

void			movement_side(const Uint8 *keyboard_state, t_param *p)
{
	if (keyboard_state[SDL_SCANCODE_RIGHT] || keyboard_state[SDL_SCANCODE_D])
	{
		p->map->speed.x -= (p->map->speed.x == -4) ? 1 : 2;
	}
	if (keyboard_state[SDL_SCANCODE_LEFT] || keyboard_state[SDL_SCANCODE_A])
	{
		p->map->speed.x += (p->map->speed.x == 4) ? 1 : 2;
	}
	if (p->map->speed.x != 0)
	{
		p->map->speed.x += (p->map->speed.x > 0) ? -1 : 1;
		if (checkcolls(p->map, &p->map->sect[p->map->psct - 1],
				p->map->pos.x + p->map->speed.x * .20 * sin(p->map->ang),
				p->map->pos.y - p->map->speed.x * .20 * cos(p->map->ang)))
		{
			p->map->pos.y -= p->map->speed.x * .20 * cos(p->map->ang);
			p->map->pos.x += p->map->speed.x * .20 * sin(p->map->ang);
		}
	}
}

void			defregen(t_map *map, int t)
{
	static int	timer = 0;

	if (t)
		timer = t;
	else if (timer)
		timer--;
	else
	{
		timer = 5;
		map->defence += (map->defence < map->weaplst[0].defence) ? 1 : 0;
	}
	if (map->sect[map->psct - 1].bot >= map->sect[map->psct - 1].top)
		map->hp = 0;
}

void			gameloop(t_param *p, SDL_Event event, const Uint8 *keystat)
{
	audioloop(p);
	arms(p);
	ai(p);
	(p->map->power) ? power_up(p->map, &p->map->weaplst[0], 0, 7) : 0;
	defregen(p->map, 0);
	movement_front(keystat, p);
	movement_side(keystat, p);
	movement_z(keystat, p);
}

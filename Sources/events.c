/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   events.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tprzybyl <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/01 22:08:57 by tprzybyl     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/28 16:48:16 by tprzybyl    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void		drawminimap(t_param *p, t_map *map, t_dpos dest)
{
	int i = 0;
	int j = 0;

	drawline(&map->pos, &dest, p);
	while (i < map->ctsector)
	{
		j = 0;
		while (j < map->sect[i].cwall)
		{
			drawline(&map->sect[i].wall[j].a, &map->sect[i].wall[j].b, p);
			j++;
		}
		i++;
	}
}

void			set_mouse(t_param *p)
{
	SDL_SetRelativeMouseMode(SDL_ENABLE);
	SDL_WarpMouseInWindow(p->win, WINH / 2, WINL / 2);
}

void		mouse_button_event(SDL_Event event, t_param *p)
{
	return ;
}

void		mouse_motion_event(SDL_Event event, t_param *p)
{
	if (event.motion.xrel != 0)
		p->map->ang += event.motion.xrel * .01;
	set_mouse(p);
}

void			movement_direction(const Uint8 *keyboard_state, t_param *p)
{
	if (keyboard_state[SDL_SCANCODE_DOWN] || keyboard_state[SDL_SCANCODE_S])
	{
		if (checkcolls(p->map, &p->map->sect[p->map->psct - 1], p->map->pos.x - cos(p->map->ang), p->map->pos.y - sin(p->map->ang)))
		{
			p->map->pos.y -= sin(p->map->ang);
			p->map->pos.x -= cos(p->map->ang);
		}
	}
	if (keyboard_state[SDL_SCANCODE_UP] || keyboard_state[SDL_SCANCODE_W])
	{
		if (checkcolls(p->map, &p->map->sect[p->map->psct - 1], p->map->pos.x + cos(p->map->ang), p->map->pos.y + sin(p->map->ang)))
		{
			p->map->pos.y += sin(p->map->ang);
			p->map->pos.x += cos(p->map->ang);
		}
	}
}

void			movement_side(const Uint8 *keyboard_state, t_param *p)
{
	if (keyboard_state[SDL_SCANCODE_RIGHT] || keyboard_state[SDL_SCANCODE_D])
	{
		if (checkcolls(p->map, &p->map->sect[p->map->psct - 1], p->map->pos.x - sin(p->map->ang), p->map->pos.y + cos(p->map->ang)))
		{
			p->map->pos.y += cos(p->map->ang);
			p->map->pos.x -= sin(p->map->ang);
		}
	}
	if (keyboard_state[SDL_SCANCODE_LEFT] || keyboard_state[SDL_SCANCODE_A])
	{
		if (checkcolls(p->map, &p->map->sect[p->map->psct - 1], p->map->pos.x + sin(p->map->ang), p->map->pos.y - cos(p->map->ang)))
		{
			p->map->pos.y -= cos(p->map->ang);
			p->map->pos.x += sin(p->map->ang);
		}
	}
}

int				key_event(const Uint8 *keyboard_state, t_param *p)
{
	if (keyboard_state[SDL_SCANCODE_ESCAPE])
		return (1);
	return (0);
}

void			loop(t_param *p)
{
	t_dpos		dest;
	SDL_Event	event;
	const Uint8	*keyboard_state;

	set_mouse(p);
	while (1)
	{
		while (SDL_PollEvent(&event))
		{
			keyboard_state = SDL_GetKeyboardState(NULL);
			if (event.type == SDL_KEYDOWN)
				key_event(keyboard_state, p);
			if (event.type == SDL_MOUSEBUTTONDOWN)
				mouse_button_event(event, p);
			if (event.type == SDL_MOUSEMOTION)
				mouse_motion_event(event, p);
		}
		if (event.type == SDL_QUIT || key_event(keyboard_state, p))
			break ;
		movement_direction(keyboard_state, p);
		movement_side(keyboard_state, p);
		//		SDL_RenderCopy(v->ren, v->back, NULL, NULL);	SDL_SetRenderDrawColor(p->ren, 0, 0, 0, 255);
		SDL_RenderClear(p->ren);
		SDL_SetRenderDrawColor(p->ren, 255, 255, 255, 255);
		p->diff = -5000 - p->map->sect[p->map->psct - 1].bot;
		drawsector(p, p->map->psct, 0, WINL, p->map->psct);
		dest.x = p->map->pos.x + 7 * cos(p->map->ang);
		dest.y = p->map->pos.y + 7 * sin(p->map->ang);
		drawminimap(p, p->map, dest);
		SDL_RenderPresent(p->ren);
	}
}

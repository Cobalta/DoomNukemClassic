/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouseevent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 17:28:20 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/12 17:54:05 by ebourgeo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	push(t_param *p)
{
	int x;
	int y;

	p->map->defence -= 2;
	defregen(p->map, 25);
	x = 0;
	while (x < WINL)
	{
		y = 0;
		while (y < WINH)
		{
			if (p->actmap[x][y].data)
			{
				if (p->actmap[x][y].data->lock &&
				distent(p->actmap[x][y].data->pos, p->map->pos) < 10)
					pushdeliver(p, p->actmap[x][y].data);
			}
			y++;
		}
		x++;
	}
}

int		strike(t_param *p, int type)
{
	int			ret;
	static int	strike = 0;

	if (type)
	{
		Mix_PlayChannel(-1, p->map->weaplst[0].w_s.swipe[rand() % 2 + 3], 0);
		ret = p->map->weaplst[0].reloadspeed[strike] + 5;
		p->map->status = strike;
		p->map->weaplst[0].tmpstrike = strike;
		p->map->weaplst[0].tmpmass = 100 + p->map->weaplst[0].mass[strike];
		lineactmap(&p->map->weaplst[0].sweeps[strike][0],
				&p->map->weaplst[0].sweeps[strike][1], p, &p->map->weaplst[0]);
		strike = (strike == 3) ? 0 : strike + 1;
		return (ret);
	}
	else
		strike = 0;
	return (0);
}

void	arms2(t_param *p, int timer)
{
	if (timer == 0)
		p->map->alock = 0;
	if (!p->map->alock)
	{
		strike(p, 0);
		p->map->status = (SDL_GetMouseState(NULL, NULL) &
				SDL_BUTTON(SDL_BUTTON_RIGHT)) ? 5 : 4;
	}
}

void	arms(t_param *p)
{
	static int	timer = 0;

	if (p->map->alock == 3)
	{
		p->map->alock = 4;
		push(p);
		p->map->status = 6;
		timer = 5;
	}
	else if (p->map->alock == 1)
	{
		p->map->alock = 2;
		timer = strike(p, 1);
	}
	if (timer)
		timer--;
	if (timer <= 10 && p->map->alock == 2)
	{
		p->map->alock = 5;
		(SDL_GetMouseState(NULL, NULL) &
		SDL_BUTTON(SDL_BUTTON_RIGHT)) ? p->map->status = 5 : 0;
	}
	arms2(p, timer);
}

void	mouse_button_event(SDL_Event e, t_param *p)
{
	if (e.button.button == SDL_BUTTON_LEFT)
	{
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)
		&& (p->map->alock == 0 || p->map->alock == 5) && p->map->defence > 0)
		{
			p->map->alock = 3;
		}
		else if ((p->map->alock == 0 || p->map->alock == 5)
		&& p->map->status != 5)
			p->map->alock = 1;
	}
}

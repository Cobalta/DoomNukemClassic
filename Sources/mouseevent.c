/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouseevent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 17:28:20 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/10 18:47:07 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		mouse_button_event(SDL_Event e, t_param *p)
{
	if (e.button.button == SDL_BUTTON_LEFT)
	{
		if (p->actmap[WINL / 2][WINH / 2 ].data)
		{
		 p->actmap[WINL / 2][WINH / 2].data->pos.x += cos(p->map->ang);
		 p->actmap[WINL / 2][WINH / 2].data->pos.y += sin(p->map->ang);
		}
	}
	return ;
}

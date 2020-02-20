/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:31:49 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/02/20 17:31:50 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	drawsector(t_param *p, int actual, int min, int max, int ans)
{
	int			i;

	i = 0;
	while (i < p->map->sect[actual - 1].cwall)
	{
		p->actual = actual - 1;
		render(p, i,  min, max, ans);
		i++;
	}
	i = 0;
	while (i < p->map->centities)
	{
		if (p->map->entities[i].esct == actual)
			renderentities(p, i, actual, min, max);
		i++;
	}
}

/*void	draw(t_param *p)
  {
  drawsector(p, p->map->psct, 0, WINL, p->map->psct);
  drawminimap(p, p->map);
  SDL_RenderPresent(p->ren);
  SDL_Delay(10);
  }*/

void	doom(t_param *p)
{
	SDL_Event e;
	setup(p);
	loop(p);
}

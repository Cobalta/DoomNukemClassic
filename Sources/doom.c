/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:31:49 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/04 15:49:33 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*void	draw(t_param *p)
  {
  drawsector(p, p->map->psct, 0, WINL, p->map->psct);
  drawminimap(p, p->map);
  SDL_RenderPresent(p->ren);
  SDL_Delay(10);
  }*/

void	doom(t_param *p, int fd)
{
	SDL_Event e;
	setup(p);
	readmap(fd, p);
	loop(p);
}

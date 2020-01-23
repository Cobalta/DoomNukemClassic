/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   doom.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ebourgeo <ebourgeo@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/23 16:23:41 by ebourgeo     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/23 16:23:41 by ebourgeo    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void	drawsector(t_param *p, int actual, int min, int max, int ans)
{
	int			i;

	i = 0;
	while (i < p->map->sect[actual - 1].cwall)
	{
		p->actual = actual - 1;
		render(p, i, min, max, ans);
		i++;
	}
}

void	draw(t_param *p)
{
	drawsector(p, p->map->psct, 0, WINL, p->map->psct);
	drawminimap(p, p->map);
	SDL_RenderPresent(p->ren);
	SDL_Delay(10);
}

void	doom(t_param *p)
{
	SDL_Event e;
	setup(p);

	while (p->quit)
	{
		event_manager(&e, p);
		draw(p);
	}
}
/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   setup.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ebourgeo <ebourgeo@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/23 16:37:32 by ebourgeo     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 19:09:24 by tprzybyl    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void	setup(t_param *p)
{
	SDL_Surface		*xxx;
	SDL_Surface		*tmp;

	if ((xxx = SDL_LoadBMP("./Textures/rock.bmp")) == NULL)
		printf("%s\n", SDL_GetError());
	p->xxx = xxx;
	p->quit = 1;
}

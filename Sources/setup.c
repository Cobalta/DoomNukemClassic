/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   setup.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ebourgeo <ebourgeo@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/23 16:37:32 by ebourgeo     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/23 16:37:32 by ebourgeo    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void	setup(t_param *p)
{
	SDL_Surface		*xxx;

	if ((xxx = SDL_LoadBMP("./Textures/rock.bmp")) == NULL)
		printf("%s\n", SDL_GetError());

	p->xxx = xxx;
	p->quit = 1;
	p->eve.a = 0;
	p->eve.w = 0;
	p->eve.d = 0;
	p->eve.s = 0;
	p->eve.r = 0;
}
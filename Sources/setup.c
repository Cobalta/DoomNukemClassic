/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:32:23 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/02 17:16:55 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

SDL_Surface	*create_surface(int w, int h)
{
	Uint32		rmask;
	Uint32		gmask;
	Uint32		bmask;
	Uint32		amask;
	SDL_Surface	*surface;

	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
	surface = SDL_CreateRGBSurface(0, w, h, 32, rmask, gmask, bmask, amask);
	return (surface);
}

void	setup(t_param *p)
{
	SDL_Surface		*xxx;
	SDL_Surface		*tmp;

	if ((xxx = SDL_LoadBMP("./Textures/rock.bmp")) == NULL)
		printf("%s\n", SDL_GetError());

	p->surf = create_surface(WINL, WINH);
	setcleanactmap(p);
	p->texture = SDL_CreateTextureFromSurface(p->ren, p->surf);
	p->xxx = xxx;
	p->quit = 1;
	p->consty = 0;
}

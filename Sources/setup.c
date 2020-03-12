/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:32:23 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/07 17:15:47 by ebourgeo         ###   ########lyon.fr   */
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

void	loadaudio(t_param *p)
{
	p->s.step[0] = Mix_LoadWAV("sounds/pl_step1.wav");
	p->s.step[1] = Mix_LoadWAV("sounds/pl_step2.wav");
	p->s.step[2] = Mix_LoadWAV("sounds/pl_step3.wav");
	p->s.step[3] = Mix_LoadWAV("sounds/pl_step4.wav");
	p->s.jump[0] = Mix_LoadWAV("soudns/pl_jump1.wav");
	p->s.jump[1] = Mix_LoadWAV("soudns/pl_jump2.wav");
	p->s.jump[2] = Mix_LoadWAV("soudns/pl_jumpland.wav");
}

void	assignart(t_param *p)
{
	if ((p->art[0] = SDL_LoadBMP("./Textures/brick.bmp")) == NULL)
		error_func(-3);
	if ((p->art[1] = SDL_LoadBMP("./Textures/metal.bmp")) == NULL)
		error_func(-3);
	if ((p->art[2] = SDL_LoadBMP("./Textures/rock.bmp")) == NULL)
		error_func(-3);
	if ((p->art[3] = SDL_LoadBMP("./Textures/test.bmp")) == NULL)
		error_func(-3);
	if ((p->art[4] = SDL_LoadBMP("./Textures/tprz.bmp")) == NULL)
		error_func(-3);
	if ((p->art[5] = SDL_LoadBMP("./Textures/wall.bmp")) == NULL)
		error_func(-3);
	if ((p->art[6] = SDL_LoadBMP("./Textures/wood.bmp")) == NULL)
		error_func(-3);
}

void	setup(t_param *p)
{
	assignart(p);
	loadaudio(p);
	p->surf = create_surface(WINL, WINH);
	setcleanactmap(p);
	p->texture = SDL_CreateTextureFromSurface(p->ren, p->surf);
	p->quit = 1;
	p->consty = 0;
}

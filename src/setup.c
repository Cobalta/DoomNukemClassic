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

#include "../includes/doom.h"

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

void		loadaudio(t_param *p)
{
	p->s.step[0] = Mix_LoadWAV("sounds/pl_step1.wav");
	p->s.step[1] = Mix_LoadWAV("sounds/pl_step2.wav");
	p->s.step[2] = Mix_LoadWAV("sounds/pl_step3.wav");
	p->s.step[3] = Mix_LoadWAV("sounds/pl_step4.wav");
	p->s.jump[0] = Mix_LoadWAV("sounds/pl_jump1.wav");
	p->s.jump[1] = Mix_LoadWAV("sounds/pl_jump2.wav");
	p->s.jump[2] = Mix_LoadWAV("sounds/pl_jumpland.wav");
	p->s.jump[3] = Mix_LoadWAV("sounds/pl_jumphuh.wav");
	p->s.skaven[0] = Mix_LoadWAV("sounds/sk_grunt.wav");
	p->s.skaven[1] = Mix_LoadWAV("sounds/sk_oof.wav");
	p->s.skaven[2] = Mix_LoadWAV("sounds/sk_ded.wav");
	p->s.player[0] = Mix_LoadWAV("sounds/pl_oof.wav");
	p->s.player[1] = Mix_LoadWAV("sounds/pl_slash1.wav");
	p->s.player[2] = Mix_LoadWAV("sounds/SPEED.wav");
	p->s.dig[0] = Mix_LoadWAV("sounds/pl_dig1.wav");
	p->s.dig[1] = Mix_LoadWAV("sounds/pl_dig2.wav");
	p->s.dig[2] = Mix_LoadWAV("sounds/pl_dig3.wav");
}

void		assignart2(t_param *p)
{
	if ((p->art[24] = SDL_LoadBMP("./Textures/prop/potion.bmp")) == NULL)
		error_func(-3);
	if ((p->art[28] = SDL_LoadBMP("./Textures/prop/adrenaline.bmp")) == NULL)
		error_func(-3);
	if ((p->art[27] = SDL_LoadBMP("./Textures/burrow/active.bmp")) == NULL)
		error_func(-3);
	if ((p->art[23] = SDL_LoadBMP("./Textures/prop/epotion.bmp")) == NULL)
		error_func(-3);
	if ((p->art[25] = SDL_LoadBMP("./Textures/prop/leveron.bmp")) == NULL)
		error_func(-3);
	if ((p->art[26] = SDL_LoadBMP("./Textures/prop/leveroff.bmp")) == NULL)
		error_func(-3);
	if ((p->art[22] = SDL_LoadBMP("./Textures/hud.bmp")) == NULL)
		error_func(-3);
	if ((p->art[21] = SDL_LoadBMP("./Textures/burrow/dead.bmp")) == NULL)
		error_func(-3);
	if ((p->art[15] = SDL_LoadBMP("./Textures/SPEED.bmp")) == NULL)
		error_func(-3);
	if ((p->art[60] = SDL_LoadBMP("./Textures/NULL.bmp")) == NULL)
		error_func(-3);
}

void		assignart(t_param *p)
{
	if ((p->art[0] = SDL_LoadBMP("./Textures/brick.bmp")) == NULL)
		error_func(-3);
	if ((p->art[1] = SDL_LoadBMP("./Textures/oldbrick.bmp")) == NULL)
		error_func(-3);
	if ((p->art[2] = SDL_LoadBMP("./Textures/oldwall.bmp")) == NULL)
		error_func(-3);
	if ((p->art[3] = SDL_LoadBMP("./Textures/rock.bmp")) == NULL)
		error_func(-3);
	if ((p->art[4] = SDL_LoadBMP("./Textures/tprz.bmp")) == NULL)
		error_func(-3);
	if ((p->art[5] = SDL_LoadBMP("./Textures/brickwall.bmp")) == NULL)
		error_func(-3);
	if ((p->art[6] = SDL_LoadBMP("./Textures/wood.bmp")) == NULL)
		error_func(-3);
	if ((p->art[30] = SDL_LoadBMP("./Textures/start.bmp")) == NULL)
		error_func(-3);
	if ((p->art[31] = SDL_LoadBMP("./Textures/gameover.bmp")) == NULL)
		error_func(-3);
	if ((p->art[32] = SDL_LoadBMP("./Textures/you_win.bmp")) == NULL)
		error_func(-3);
}

void		setup(t_param *p)
{
	assignart(p);
	assignart2(p);
	assignratart_idle(p);
	loadaudio(p);
	p->surf = create_surface(WINL, WINH);
	p->texture = SDL_CreateTextureFromSurface(p->ren, p->surf);
	p->quit = 1;
	p->consty = 0;
	p->s.sk_cooldown = 500;
	SDL_SetRelativeMouseMode(SDL_ENABLE);
	SDL_WarpMouseInWindow(p->win, WINH / 2, WINL / 2);
}

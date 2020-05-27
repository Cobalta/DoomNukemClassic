/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setratart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:32:23 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/07 17:15:47 by ebourgeo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	assignratart_movea(t_param *p)
{
	if ((p->ratart[1][0] = SDL_LoadBMP("./Textures/xlrat/move/0.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[1][1] = SDL_LoadBMP("./Textures/xlrat/move/45.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[1][2] = SDL_LoadBMP("./Textures/xlrat/move/90.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[1][3] = SDL_LoadBMP("./Textures/xlrat/move/135.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[1][4] = SDL_LoadBMP("./Textures/xlrat/move/180.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[1][5] = SDL_LoadBMP("./Textures/xlrat/move/225.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[1][6] = SDL_LoadBMP("./Textures/xlrat/move/270.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[1][7] = SDL_LoadBMP("./Textures/xlrat/move/315.bmp")) == NULL)
		error_func(-3);
}

void	assignratart_moveb(t_param *p)
{
	if ((p->ratart[2][0] = SDL_LoadBMP("./Textures/xlrat/move2/0.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[2][1] = SDL_LoadBMP("./Textures/xlrat/move2/45.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[2][2] = SDL_LoadBMP("./Textures/xlrat/move2/90.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[2][3] = SDL_LoadBMP("./Textures/xlrat/move2/135.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[2][4] = SDL_LoadBMP("./Textures/xlrat/move2/180.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[2][5] = SDL_LoadBMP("./Textures/xlrat/move2/225.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[2][6] = SDL_LoadBMP("./Textures/xlrat/move2/270.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[2][7] = SDL_LoadBMP("./Textures/xlrat/move2/315.bmp")) == NULL)
		error_func(-3);
		assignratart_movea(p);
}

void	assignratart_idle(t_param *p)
{
	if ((p->ratart[0][0] = SDL_LoadBMP("./Textures/xlrat/idle/0.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[0][1] = SDL_LoadBMP("./Textures/xlrat/idle/45.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[0][2] = SDL_LoadBMP("./Textures/xlrat/idle/90.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[0][3] = SDL_LoadBMP("./Textures/xlrat/idle/135.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[0][4] = SDL_LoadBMP("./Textures/xlrat/idle/180.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[0][5] = SDL_LoadBMP("./Textures/xlrat/idle/225.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[0][6] = SDL_LoadBMP("./Textures/xlrat/idle/270.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[0][7] = SDL_LoadBMP("./Textures/xlrat/idle/315.bmp")) == NULL)
		error_func(-3);
		assignratart_moveb(p);
}

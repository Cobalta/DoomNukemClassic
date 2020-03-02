/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entitiesinit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 17:33:47 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/02 13:43:37 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/* ALL TYPES OF ENTITIES LISTED HERE! =
 * TYPE 1 = Basic ennemy
 * TYPE 21 = Basic ennemy spawner
 * TTYPE 10 = Health thing
 * */

void				setart(t_entity *e, int type)
{
	if (type == 1)
	e->art = SDL_LoadBMP("./Textures/test.bmp");
	if (type == 21)
	e->art = SDL_LoadBMP("./Textures/tprz.bmp");
	if (type == 10)
	e->art = SDL_LoadBMP("./Textures/wall.bmp");
}

void				sethitpoints(t_entity *e, int type)
{
	if (type == 1)
	e->hp = 40;
	if (type == 21)
	e->hp = 200;
	if (type == 10)
	e->hp = -1;
}

void				setmaxspeed(t_entity *e, int type)
{
	if (type == 1)
	e->hp = 4;
	if (type == 21)
	e->hp = 0;
	if (type == 10)
	e->hp = 0;
}

void			readentity(t_param *p, t_entity *e, int type)
{
	sethitpoints(e, type);
	setmaxspeed(e, type);
	setart(e, type);
}

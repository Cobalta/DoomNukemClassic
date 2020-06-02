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

void				setart(t_entity *e)
{
	if (e->type == 1)
	e->art = SDL_LoadBMP("./Textures/tprz.bmp");
	if (e->type == 21)
	e->art = SDL_LoadBMP("./Textures/tprz.bmp");
	if (e->type == 10)
	e->art = SDL_LoadBMP("./Textures/wall.bmp");
}

void				sethitpoints(t_entity *e)
{
	if (e->type == 1)
	e->hp = 40;
	if (e->type == 21)
	e->hp = 200;
	if (e->type == 10)
	e->hp = -1;
}

void				setmaxspeed(t_entity *e)
{
	if (e->type == 1)
	e->hp = 4;
	if (e->type == 21)
	e->hp = 0;
	if (e->type == 10)
	e->hp = 0;
}

void			readentity(t_param *p, t_entity *e, t_map *map)
{
	sethitpoints(e);
	setmaxspeed(e);
	setart(e);
	e->pz = map->sect[e->psct - 1].bot;
	e->speed.x = 0;
	e->speed.y = 0;
	e->state = 0;
	e->maxspeed = 3;
	e->rotspeed = .07;
}

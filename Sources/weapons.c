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

/* typedef struct	s_weapon
// {
//	int			range;
//	t_dpos		sweeps[4];
//	SDL_Surface *art[6];
//	int			mass[4];
//	int			damage[4];
//	int			impact[4];
//	int			reloadspeed[4];
//	int			defence;
}				t_weapon;*/


void	createweapon_2hsword(t_weapon *weap)
{
	weap->range = 13;
printf("hi!\n");
	weap->defence = 6;
	if ((weap->art[4] = SDL_LoadBMP("./Textures/weapon/idle.bmp")) == NULL)
		error_func(-3);
	if ((weap->art[5] = SDL_LoadBMP("./Textures/weapon/parry.bmp")) == NULL)
		error_func(-3);
	if ((weap->art[6] = SDL_LoadBMP("./Textures/weapon/push.bmp")) == NULL)
		error_func(-3);
	weap->sweeps[0][0].x = WINL * .9;
	weap->sweeps[0][0].y = WINH * .1;
	weap->sweeps[0][1].x = WINL * .1;
	weap->sweeps[0][1].y = WINH * .9;
	if ((weap->art[0] = SDL_LoadBMP("./Textures/weapon/attack1.bmp")) == NULL)
		error_func(-3);
//	weap->art[0] = ;
	weap->mass[0] = 25;
	weap->damage[0] = 40;
	weap->impact[0] = 25;
	weap->reloadspeed[0] = 15;
	weap->sweeps[1][0].x = WINL * .1;
	weap->sweeps[1][0].y = WINH * .2;
	weap->sweeps[1][1].x = WINL * .9;
	weap->sweeps[1][1].y = WINH * .8;
	if ((weap->art[1] = SDL_LoadBMP("./Textures/weapon/attack2.bmp")) == NULL)
		error_func(-3);
//	weap->art[1] = 1;
	weap->mass[1] = 25;
	weap->damage[1] = 50;
	weap->impact[1] = 25;
	weap->reloadspeed[1] = 15;
	weap->sweeps[2][0].x = WINL * .9;
	weap->sweeps[2][0].y = WINH * .1;
	weap->sweeps[2][1].x = WINL * .1;
	weap->sweeps[2][1].y = WINH * .9;
	if ((weap->art[2] = SDL_LoadBMP("./Textures/weapon/attack3.bmp")) == NULL)
		error_func(-3);
//	weap->art[2] = 1;
	weap->mass[2] = 25;
	weap->damage[2] = 50;
	weap->impact[2] = 25;
	weap->reloadspeed[2] = 15;
	weap->sweeps[3][0].x = WINL * .4;
	weap->sweeps[3][0].y = WINH * .1;
	weap->sweeps[3][1].x = WINL * .6;
	weap->sweeps[3][1].y = WINH;
	if ((weap->art[3] = SDL_LoadBMP("./Textures/weapon/attack4.bmp")) == NULL)
		error_func(-3);
//	weap->art[3] = 1;
	weap->mass[3] = 100;
	weap->damage[3] = 100;
	weap->impact[3] = 50;
	weap->reloadspeed[3] = 20;
}
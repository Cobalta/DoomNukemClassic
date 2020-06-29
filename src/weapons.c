/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:32:23 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/07 17:15:47 by ebourgeo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	speed_down(t_map *map)
{
	map->speed.x = (map->speed.x > 4) ? 4 : map->speed.x;
	map->speed.x = (map->speed.x < -4) ? -4 : map->speed.x;
	map->speed.y = (map->speed.y > 5) ? 5 : map->speed.y;
	map->speed.y = (map->speed.y < -4) ? -4 : map->speed.y;
}

void	power_up(t_map *map, t_weapon *weap, int i, int boost)
{
	static int	timer = -1;
	static int	save[4];

	if (map->power == 1 && timer == -1)
	{
		timer = 251;
		while (i < 4)
		{
			save[i] = weap->reloadspeed[i];
			weap->reloadspeed[i++] -= boost;
		}
	}
	if (timer)
		timer--;
	else
	{
		speed_down(map);
		while (++i < 4)
			weap->reloadspeed[i] = save[i];
		timer = -1;
		map->power = 0;
	}
	map->powert = timer;
}

void	createweapon_2hsword3(t_weapon *weap)
{
	if ((weap->art[3] = SDL_LoadBMP("./Textures/weapon/attack4.bmp")) == NULL)
		error_func(-3);
	weap->mass[3] = 50;
	weap->damage[3] = 100;
	weap->impact[3] = 50;
	weap->reloadspeed[3] = 20;
	weap->w_s.swipe[0] = Mix_LoadWAV("sounds/pl_swipe1.wav");
	weap->w_s.swipe[1] = Mix_LoadWAV("sounds/pl_swipe2.wav");
	weap->w_s.swipe[2] = Mix_LoadWAV("sounds/pl_swipe3.wav");
	weap->w_s.swipe[3] = Mix_LoadWAV("sounds/pl_swipe4.wav");
	weap->w_s.swipe[4] = Mix_LoadWAV("sounds/pl_swipe5.wav");
	weap->w_s.swipe[5] = Mix_LoadWAV("sounds/pl_swipe6.wav");
	weap->w_s.block[0] = Mix_LoadWAV("sounds/pl_block1.wav");
	weap->w_s.block[1] = Mix_LoadWAV("sounds/pl_block2.wav");
	weap->w_s.block[2] = Mix_LoadWAV("sounds/pl_block3.wav");
}

void	createweapon_2hsword2(t_weapon *weap)
{
	if ((weap->art[1] = SDL_LoadBMP("./Textures/weapon/attack2.bmp")) == NULL)
		error_func(-3);
	weap->mass[1] = 20;
	weap->damage[1] = 50;
	weap->impact[1] = 20;
	weap->reloadspeed[1] = 15;
	weap->sweeps[2][0].x = WINL * .9;
	weap->sweeps[2][0].y = WINH * .1;
	weap->sweeps[2][1].x = WINL * .1;
	weap->sweeps[2][1].y = WINH * .9;
	if ((weap->art[2] = SDL_LoadBMP("./Textures/weapon/attack3.bmp")) == NULL)
		error_func(-3);
	weap->mass[2] = 20;
	weap->damage[2] = 50;
	weap->impact[2] = 20;
	weap->reloadspeed[2] = 15;
	weap->sweeps[3][0].x = WINL * .4;
	weap->sweeps[3][0].y = WINH * .1;
	weap->sweeps[3][1].x = WINL * .6;
	weap->sweeps[3][1].y = WINH;
	createweapon_2hsword3(weap);
}

void	createweapon_2hsword(t_weapon *weap)
{
	weap->range = 13;
	weap->defence = 14;
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
	weap->mass[0] = 20;
	weap->damage[0] = 50;
	weap->impact[0] = 20;
	weap->reloadspeed[0] = 15;
	weap->sweeps[1][0].x = WINL * .1;
	weap->sweeps[1][0].y = WINH * .2;
	weap->sweeps[1][1].x = WINL * .9;
	weap->sweeps[1][1].y = WINH * .8;
	createweapon_2hsword2(weap);
}

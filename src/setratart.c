/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setratart.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:32:23 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/07 17:15:47 by ebourgeo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	assignratart_attackprep(t_param *p)
{
	if ((p->ratart[3][0] = SDL_LoadBMP(RAT"move/0.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[3][1] = SDL_LoadBMP(RAT"attackprep/45.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[3][2] = SDL_LoadBMP(RAT"attackprep/90.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[3][3] = SDL_LoadBMP(RAT"attackprep/135.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[3][4] = SDL_LoadBMP(RAT"attackprep/180.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[3][5] = SDL_LoadBMP(RAT"attackprep/225.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[3][6] = SDL_LoadBMP(RAT"attackprep/270.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[3][7] = SDL_LoadBMP(RAT"attackprep/315.bmp")) == NULL)
		error_func(-3);
}

void	assignratart_attackdeliver(t_param *p)
{
	if ((p->ratart[4][0] = SDL_LoadBMP(RAT"attackdeliver/0.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[4][1] = SDL_LoadBMP(RAT"attackdeliver/45.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[4][2] = SDL_LoadBMP(RAT"attackdeliver/90.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[4][3] = SDL_LoadBMP(RAT"attackdeliver/135.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[4][4] = SDL_LoadBMP(RAT"attackdeliver/180.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[4][5] = SDL_LoadBMP(RAT"attackdeliver/225.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[4][6] = SDL_LoadBMP(RAT"attackdeliver/270.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[4][7] = SDL_LoadBMP(RAT"attackdeliver/315.bmp")) == NULL)
		error_func(-3);
	assignratart_attackprep(p);
}

void	assignratart_dying(t_param *p)
{
	if ((p->ratart[5][0] = SDL_LoadBMP(RAT"dying/0.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[5][1] = SDL_LoadBMP(RAT"dying/45.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[5][2] = SDL_LoadBMP(RAT"dying/90.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[5][3] = SDL_LoadBMP(RAT"dying/135.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[5][4] = SDL_LoadBMP(RAT"dying/180.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[5][5] = SDL_LoadBMP(RAT"dying/225.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[5][6] = SDL_LoadBMP(RAT"dying/270.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[5][7] = SDL_LoadBMP(RAT"dying/315.bmp")) == NULL)
		error_func(-3);
	assignratart_attackdeliver(p);
}

void	assignratart_dead(t_param *p)
{
	if ((p->ratart[6][0] = SDL_LoadBMP(RAT"dead/0.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[6][1] = SDL_LoadBMP(RAT"dead/45.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[6][2] = SDL_LoadBMP(RAT"dead/90.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[6][3] = SDL_LoadBMP(RAT"dead/135.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[6][4] = SDL_LoadBMP(RAT"dead/180.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[6][5] = SDL_LoadBMP(RAT"dead/225.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[6][6] = SDL_LoadBMP(RAT"dead/270.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[6][7] = SDL_LoadBMP(RAT"dead/315.bmp")) == NULL)
		error_func(-3);
	assignratart_dying(p);
}

void	assignratart_movea(t_param *p)
{
	if ((p->ratart[1][0] = SDL_LoadBMP(RAT"move/0.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[1][1] = SDL_LoadBMP(RAT"move/45.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[1][2] = SDL_LoadBMP(RAT"move/90.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[1][3] = SDL_LoadBMP(RAT"move/135.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[1][4] = SDL_LoadBMP(RAT"move/180.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[1][5] = SDL_LoadBMP(RAT"move/225.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[1][6] = SDL_LoadBMP(RAT"move/270.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[1][7] = SDL_LoadBMP(RAT"move/315.bmp")) == NULL)
		error_func(-3);
	assignratart_dead(p);
}

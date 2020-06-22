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

#include "../includes/doom.h"

void	assignratart_attackprep(t_param *p)
{
	if ((p->ratart[3][0] = SDL_LoadBMP("./Textures/xlrat/move/0.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[3][1] = SDL_LoadBMP("./Textures/xlrat/attackprep/45.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[3][2] = SDL_LoadBMP("./Textures/xlrat/attackprep/90.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[3][3] = SDL_LoadBMP("./Textures/xlrat/attackprep/135.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[3][4] = SDL_LoadBMP("./Textures/xlrat/attackprep/180.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[3][5] = SDL_LoadBMP("./Textures/xlrat/attackprep/225.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[3][6] = SDL_LoadBMP("./Textures/xlrat/attackprep/270.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[3][7] = SDL_LoadBMP("./Textures/xlrat/attackprep/315.bmp")) == NULL)
		error_func(-3);
}

void	assignratart_attackdeliver(t_param *p)
{
	if ((p->ratart[4][0] = SDL_LoadBMP("./Textures/xlrat/attackdeliver/0.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[4][1] = SDL_LoadBMP("./Textures/xlrat/attackdeliver/45.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[4][2] = SDL_LoadBMP("./Textures/xlrat/attackdeliver/90.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[4][3] = SDL_LoadBMP("./Textures/xlrat/attackdeliver/135.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[4][4] = SDL_LoadBMP("./Textures/xlrat/attackdeliver/180.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[4][5] = SDL_LoadBMP("./Textures/xlrat/attackdeliver/225.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[4][6] = SDL_LoadBMP("./Textures/xlrat/attackdeliver/270.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[4][7] = SDL_LoadBMP("./Textures/xlrat/attackdeliver/315.bmp")) == NULL)
		error_func(-3);
		assignratart_attackprep(p);
}

void	assignratart_dying(t_param *p)
{
	if ((p->ratart[5][0] = SDL_LoadBMP("./Textures/xlrat/dying/0.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[5][1] = SDL_LoadBMP("./Textures/xlrat/dying/45.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[5][2] = SDL_LoadBMP("./Textures/xlrat/dying/90.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[5][3] = SDL_LoadBMP("./Textures/xlrat/dying/135.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[5][4] = SDL_LoadBMP("./Textures/xlrat/dying/180.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[5][5] = SDL_LoadBMP("./Textures/xlrat/dying/225.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[5][6] = SDL_LoadBMP("./Textures/xlrat/dying/270.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[5][7] = SDL_LoadBMP("./Textures/xlrat/dying/315.bmp")) == NULL)
		error_func(-3);
		assignratart_attackdeliver(p);
}

void	assignratart_dead(t_param *p)
{
	if ((p->ratart[6][0] = SDL_LoadBMP("./Textures/xlrat/dead/0.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[6][1] = SDL_LoadBMP("./Textures/xlrat/dead/45.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[6][2] = SDL_LoadBMP("./Textures/xlrat/dead/90.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[6][3] = SDL_LoadBMP("./Textures/xlrat/dead/135.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[6][4] = SDL_LoadBMP("./Textures/xlrat/dead/180.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[6][5] = SDL_LoadBMP("./Textures/xlrat/dead/225.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[6][6] = SDL_LoadBMP("./Textures/xlrat/dead/270.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[6][7] = SDL_LoadBMP("./Textures/xlrat/dead/315.bmp")) == NULL)
		error_func(-3);
		assignratart_dying(p);
}

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
		assignratart_dead(p);
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

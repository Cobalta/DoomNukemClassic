/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:31:49 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/06 18:29:09 by ebourgeo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	doom(t_param *p, int fd)
{
	SDL_Event e;
	setup(p);
	readmap(fd, p);
	loop(p);
}

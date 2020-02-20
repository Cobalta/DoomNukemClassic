/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:32:11 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/02/20 17:32:13 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			main(int ac, char **av)
{
	t_param			*param;
	int				fd;

	if (ac == 2)
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
			return (1);
		if (-1 == (fd = open(av[1], O_RDONLY)))
			error_func(-2);
		if (!(param = malloc(sizeof(t_param))))
			error_func(-1);

		param->win = SDL_CreateWindow("General Kenobi! *cough cough*"
				, SDL_WINDOWPOS_CENTERED
				, SDL_WINDOWPOS_CENTERED
				, WINL, WINH,
									  0);
		//			SDL_WINDOW_FULLSCREEN_DESKTOP);

		param->ren = SDL_CreateRenderer(param->win, -1, SDL_RENDERER_SOFTWARE);
		readmap(fd, param);
		SDL_SetRenderDrawColor(param->ren, 255, 255, 255, 255);

		doom(param);
		SDL_DestroyWindow(param->win);
		SDL_Quit();
	}
	return (0);
}

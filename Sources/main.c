/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:32:11 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/06 19:36:54 by ebourgeo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			setdif(char *str)
{
	int d;

	d = ft_atoi(str);
	if (d <= 0 || d > 4)
	d = 2;
	return (d);
}

int			main(int ac, char **av)
{
	t_param			*param;
	int				fd;
	int				diflvl;

	if (ac == 1)
	{
		if (-1 == (fd = open("maps/demo", O_RDONLY)))
			error_func(-2);
	}
	else if (-1 == (fd = open(av[1], O_RDONLY)))
		error_func(-2);
	diflvl = (ac > 2) ? setdif(av[2]) : 2;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return (1);
	if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
		error_func(-5);
	if (!(param = malloc(sizeof(t_param))))
		error_func(-1);

	param->win = SDL_CreateWindow("Doom Nukem Classic"
			, SDL_WINDOWPOS_CENTERED
			, SDL_WINDOWPOS_CENTERED
			, WINL, WINH,
								  0);
	//			SDL_WINDOW_FULLSCREEN_DESKTOP);
		param->dy = 1;
	param->ren = SDL_CreateRenderer(param->win, -1, SDL_RENDERER_SOFTWARE);
	SDL_SetRenderDrawColor(param->ren, 255, 255, 255, 255);
	param->diflvl = diflvl;
	doom(param, fd);
	SDL_DestroyWindow(param->win);
//	Mix_FreeChunk(param->sounds->step);
	Mix_CloseAudio();
	SDL_Quit();
	return (0);
}

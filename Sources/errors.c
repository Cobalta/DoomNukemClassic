/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:31:57 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/02/20 17:31:58 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

#define USAGE1	"usage: ./fractol [-mandelbrot | -julia | -burningship"
#define USAGE2	" | -tricorn | -triplebrot]\n"

void	error_func(int code)
{
	//char *us;

	//us = "usage: ./fractol [-mandelbrot | -julia | -burningship | -tricorn";
	if (code == -4)
		perror("Close error");
	else if (code == -3)
		perror("Read error");
	else if (code == -2)
		perror("Open error");
	else if (code == -1)
		perror("Memory allocation error");
	else if (code == 0)
	{
		ft_putstr(USAGE1 USAGE2);
		/*
		ft_putstr_fd(us, 2);
		ft_putendl_fd(" | -triplebrot]", 2);
		*/
	}
	else if (code == 1)
		perror("Thread creation failed");
	else if (code == 2)
		perror("Thread join failed");
	else if (code == 5)
		perror("MLX Init failed");
	exit(EXIT_FAILURE);
}

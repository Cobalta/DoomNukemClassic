/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:31:57 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/05 18:14:50 by ebourgeo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	error_func(int code)
{
	if (code == -5)
		perror("Audio error");
	else if (code == -4)
		perror("Close error");
	else if (code == -3)
		perror("Read error");
	else if (code == -2)
		perror("Open error");
	else if (code == -1)
		perror("Memory allocation error");
	else if (code == 0)
	{
		ft_putstr("How the fuck did you get this error ?");
	}
	else if (code == 1)
		perror("Thread creation failed");
	else if (code == 2)
		perror("Thread join failed");
	else if (code == 4)
		perror("Too many entities! MAX 512");
	else if (code == 5)
		perror("MLX Init failed");
	exit(EXIT_FAILURE);
}

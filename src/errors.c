/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <tprzybyl@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:31:57 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/06/25 20:05:12 by tprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

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
		ft_putstr("How the fuck did you get this error ?");
	else if (code == 6)
		ft_putstr("Map is incorrect!");
	else if (code == 1)
		perror("Thread creation failed");
	else if (code == 2)
		perror("Thread join failed");
	else if (code == 4)
		perror("Too many entities! MAX 512");
	else if (code == 5)
		perror("MLX Init failed");
	else
		perror("Error's error, I do not exist ???");
	exit(EXIT_FAILURE);
}

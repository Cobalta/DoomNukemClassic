/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolsparsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:19:37 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/11 17:51:05 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	checkend(char **str)
{
	while ((**str))
	{
		if (**str == '-' || **str == '+' || (**str > 47 && **str < 58))
			error_func(6);
		*str += 1;
	}
}

int		nextatoi(char **str)
{
	long	nb;
	int		i;
	int		neg;

	if (!(**str))
		error_func(6);
	nb = 0;
	i = 0;
	neg = 0;
	while ((*str)[i] == '\f' || (*str)[i] == ' ' || (*str)[i] == '\t' ||
			(*str)[i] == '\n' || (*str)[i] == '\r' || (*str)[i] == '\v')
		i++;
	if ((*str)[i] == '-')
		neg = 1;
	if ((*str)[i] == '-' || (*str)[i] == '+')
		i++;
	while ((*str)[i] > 47 && (*str)[i] < 58)
	{
		nb = nb * 10 + ((*str)[i] - 48);
		i++;
	}
	if (neg == 1)
		nb = -nb;
	*str += i;
	while (!ft_isdigit(**str) && **str && **str != '-')
		*str += 1;
	return ((int)nb);
}

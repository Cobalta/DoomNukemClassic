/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_isbetween.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tprzybyl <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/05 20:36:34 by tprzybyl     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 13:40:07 by tprzybyl    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_isbetween(double a, double b, double c)
{
	if (a >= b && a >= c && c >= b)
	{
		return (1);
		}
	else if (a <= b && a <= c && c <= b)
		{
		return (1);
		}
	else
		return (0);
}

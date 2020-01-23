/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_seekpercent.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tprzybyl <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/05 20:36:34 by tprzybyl     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/05 20:38:12 by tprzybyl    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

double		seekpercent(double start, double end, double percentage)
{
	return ((1 - percentage) * start + percentage * end);
}

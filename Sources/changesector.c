/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changesector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:31:22 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/02/20 17:31:23 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			refreshportals(t_param *p)
{
	int i;

	i = 0;
	while(i < p->map->sect[(p->map->psct)- 1].cwall)
	{
		if (p->map->sect[(p->map->psct)- 1].wall[i].portal)
			fillcollisiongrid(&p->map->sect[(p->map->psct)- 1].wall[i].a, &p->map->sect[(p->map->psct)- 1].wall[i].b, p , p->map->sect[(p->map->psct)- 1].wall[i].portal);
		i++;
	}
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   changesector.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tprzybyl <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/13 19:47:01 by tprzybyl     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/18 14:52:37 by tprzybyl    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

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

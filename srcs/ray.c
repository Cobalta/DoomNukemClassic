/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ray.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ebourgeo <ebourgeo@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/28 17:37:21 by ebourgeo     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/28 17:37:21 by ebourgeo    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h"

int	get_distance_line(t_pt *pt, t_line *l)
{
	int dist;

	dist = abs((l->y2 - l->y1) * pt->x - (l->x2 - l->x1) * pt->y + (l->x2 * l->y1) - (l->y2 * l->x1))
			/ sqrt((l->y2 - l->y1) * (l->y2 - l->y1) + (l->x2 - l->x1) * (l->x2 - l->x1));
	return (dist);
}

int	find_min_dist(t_wall wall)
{
	int dist;
	int newdist;

	dist = get_distance_line(pt, l(i));
	wall = wall->next;

	while (wall->next != '\0')
	{
		newdist = get_distance_line(pt, l(i))
		if (dist > newdist)
		   dist = newdist;
	}

	return (dist);
}
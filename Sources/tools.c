/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ebourgeo <ebourgeo@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 17:18:28 by ebourgeo     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/04 17:18:28 by ebourgeo    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void		put_pixel(SDL_Surface *surf, int x, int y, int color)
{
	Uint32 *pixels;

	pixels = (Uint32 *)surf->pixels;
	if (x >= 0 && y >= 0 && x < surf->w && y < surf->h)
		pixels[y * surf->w + x] = color;
}
/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   editeur.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nrivoire <nrivoire@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/12 13:48:22 by nrivoire     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/12 15:05:45 by nrivoire    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EDITEUR_H
# define EDITEUR_H

# include "doom.h"
# include "struct.h"
# define RADIUS 200

/*-----------------------------DRAWLINE-------------------------------*/
typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_rgb
{
	int			r;
	int			g;
	int			b;
	int			a;
}				t_rgb;

typedef struct	s_bressen
{
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			e2;
}				t_bressen;

t_point			make_point(int x, int y);
t_rgb			make_rgb(int r, int g, int b, int a);
void			my_sdl_drawline(t_point m1, t_point m2, t_rgb color, t_env *v);

void			draw_circle(t_env *v, int x, int y);

#endif

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   editeur.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nrivoire <nrivoire@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/28 15:21:37 by ebourgeo     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/13 09:27:37 by nrivoire    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EDITEUR_H
# define EDITEUR_H

# include "../libft/libft.h"
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <pthread.h>
# include "../sdl2/2.0.10/include/SDL2/SDL.h"
# include "../sdl2/2.0.10/include/SDL2/SDL_surface.h"
# include "../sdl2/2.0.10/include/SDL2/SDL_video.h"
# include "../sdl2/2.0.10/include/SDL2/SDL_render.h"
# include "../sdl2/2.0.10/include/SDL2/SDL_pixels.h"
# include "../sdl2/2.0.10/include/SDL2/SDL_events.h"
# include "../sdl2_image/2.0.5/include/SDL2/SDL_image.h"

# define WIDTH 1280
# define HEIGHT 960
# define RADIUS 100

/*
** -----------------------------EDITEUR---------------------------------
*/

typedef struct		s_draw_circle
{
	int				x;
	int				y;
}					t_draw_circle;

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


/*
** -----------------------------ENVIRONNEMENT----------------------------
*/

typedef struct		s_env
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Event		e;
	t_draw_circle	center;
}					t_env;

/*
** ----------------------------------------------------------------------
*/

void			pixel_put(t_env *v, int x, int y, t_rgb color);

t_point			make_point(int x, int y);
t_rgb			make_rgb(int r, int g, int b, int a);
void			drawline(t_point m1, t_point m2, t_rgb color, t_env *v);

void			draw_void_circle(t_env *v, int x, int y, t_rgb color);
void			draw_full_circle(t_env *v, int x, int y, t_rgb color);

void			display(t_env *v);

#endif

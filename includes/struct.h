/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   struct.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nrivoire <nrivoire@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/28 15:21:37 by ebourgeo     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/07 15:41:56 by nrivoire    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "doom.h"
# include "../sdl2/2.0.10/include/SDL2/SDL.h"
# include "../sdl2/2.0.10/include/SDL2/SDL_surface.h"
# include "../sdl2/2.0.10/include/SDL2/SDL_video.h"
# include "../sdl2/2.0.10/include/SDL2/SDL_render.h"
# include "../sdl2/2.0.10/include/SDL2/SDL_pixels.h"
# include "../sdl2/2.0.10/include/SDL2/SDL_events.h"
# include "../sdl2_image/2.0.5/include/SDL2/SDL_image.h"

typedef struct		s_pt
{
	float			x;
	float			y;
}					t_pt;

typedef struct		s_line
{
	int				px;
	int				py;
	int				dx;
	int				dy;
	int				x_incr;
	int				y_incr;
}					t_line;

typedef struct		s_seg
{
	float			x1;
	float			y1;
	float			x2;
	float			y2;
}					t_seg;

typedef struct		s_circle
{
	float			x;
	float			y;
	float			r;
}					t_circle;

/*
** -----------------------------ENVIRONNEMENT----------------------------
*/

typedef struct		s_env
{
	SDL_Window		*win;
	SDL_Renderer	*render;
	SDL_Event		e;
	//t_map			map;
	int				width;
	int				height;
	int				quit;
	int				fov;
	float			cos_t[360];
	float			sin_t[360];
	float			tan_t[360];

	

}					t_env;

#endif

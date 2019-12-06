/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   struct.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ebourgeo <ebourgeo@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/28 15:21:37 by ebourgeo     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/28 15:21:37 by ebourgeo    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct		s_pt
{
	float	x;
	float	y;
}					t_pt;

typedef struct	s_line
{
	int		px;
	int		py;
	int		dx;
	int		dy;
	int		x_incr;
	int		y_incr;
}				t_line;

typedef struct		s_seg
{
	float	x1;
	float	y1;
	float	x2;
	float	y2;
}					t_seg;

typedef struct		s_circle
{
	float x;
	float y;
	float r;
}					t_circle;

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

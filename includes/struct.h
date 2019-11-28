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

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   doom.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ebourgeo <ebourgeo@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/28 15:18:19 by ebourgeo     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/28 15:18:19 by ebourgeo    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "sdl2/SDL.h"
# include "struct.h"
# include "../libft/libft.h"
# define PI 3.14159265359
# define WIDTH 1280
# define HEIGHT 960

void	setup(t_env *env);
void	control(t_env *env, const Uint8 *keystates);
void	line_tracer(t_seg *seg, t_env *env);
void	render(t_env *env);

#endif
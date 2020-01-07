/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   doom.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nrivoire <nrivoire@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/28 15:18:19 by ebourgeo     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/07 17:17:32 by nrivoire    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "../libft/libft.h"
# include "struct.h"
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

# define PI 3.14159265359
# define WIDTH 1280
# define HEIGHT 960

void		setup(t_env *env);
void		control(t_env *env, const Uint8 *keystates);
void		line_tracer(t_seg *seg, t_env *env);
void		render(t_env *env);

void		display(t_env *v);

/*
** --events--
*/
void		mouse_button_event(SDL_Event event, t_env *v);
void		mouse_motion_event(SDL_Event event, t_env *v);
int			key_event(const Uint8 *keyboard_state, t_env *v);

#endif
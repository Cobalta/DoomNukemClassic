/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   control.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ebourgeo <ebourgeo@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/28 15:40:45 by ebourgeo     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/28 15:40:45 by ebourgeo    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h"

void	control(t_env *env, const Uint8 *keystates)
{
	if (env->e.type == SDL_QUIT || keystates[SDL_SCANCODE_ESCAPE])
		env->quit = 1;
}

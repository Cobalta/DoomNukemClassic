/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   setup.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ebourgeo <ebourgeo@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/28 15:32:59 by ebourgeo     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/28 15:32:59 by ebourgeo    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h"

void	angle_table(t_env *env)
{
	int i;

	i = 0;
	while (i <= 360)
	{
		env->cos_t[i] = cos(PI * i / 180);
		i++;
	}
	i = 0;
	while (i <= 360)
	{
		env->sin_t[i] = sin(PI * i / 180);
		i++;
	}
	i = 0;
	while (i <= 360)
	{
		env->tan_t[i] = tan(PI * i / 180);
		i++;
	}
}

void	setup(t_env *env)
{
	env->fov = 60;
	env->render = SDL_CreateRenderer(env->win, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(env->render, 0, 0, 0, 255);
	//angle_table(env);
	//texture_load(env);
//	SDL_SetRelativeMouseMode(SDL_TRUE);
}

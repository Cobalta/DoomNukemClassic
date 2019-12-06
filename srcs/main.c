/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ebourgeo <ebourgeo@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/28 15:26:14 by ebourgeo     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/28 15:26:14 by ebourgeo    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h"

void    display(t_env *env)
{
	SDL_SetRenderDrawColor(env->render, 0, 0, 0, 255);
	SDL_RenderClear(env->render);
	render(env);
	SDL_RenderPresent(env->render);
}

void    doom(t_env *env)
{
	const Uint8 *keystates;
	int w, h;

	display(env);
	while (!env->quit)
	{

		while (SDL_PollEvent(&env->e) != 0 || env->e.key.repeat == 0)
		{
			if (env->e.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				SDL_GetWindowSize(env->win, &w, &h);
				env->width = w;
				env->height = h;
			}
			keystates = SDL_GetKeyboardState(NULL);
			if (env->quit == 1)
				break;
			control(env, keystates);
			display(env);
		}
		SDL_Delay(200);
	}
}

void	init(t_env *env)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("ERREUR : Init SDL > %s\n", SDL_GetError());
		exit(0);
	}
	if ((env->win = SDL_CreateWindow("DOOM NUKEM",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			env->width, env->height, SDL_WINDOW_RESIZABLE)) == NULL)
	{
		SDL_Log("ERREUR : Creation fenetre echouee > %s\n", SDL_GetError());
		exit(0);
	}
	env->quit = 0;
}

int		main()
{
	t_env	env;

	env.width = WIDTH;
	env.height = HEIGHT;
	init(&env);
	setup(&env);
	doom(&env);
	SDL_DestroyRenderer(env.render);
	SDL_DestroyWindow(env.win);
	SDL_Quit();
	return (0);
}

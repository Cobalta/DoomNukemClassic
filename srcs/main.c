/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nrivoire <nrivoire@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/28 15:26:14 by ebourgeo     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/07 17:11:10 by nrivoire    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h"

// void    display(t_env *env)
// {
// 	SDL_SetRenderDrawColor(env->render, 0, 0, 0, 255);
// 	SDL_RenderClear(env->render);
// 	render(env);
// 	SDL_RenderPresent(env->render);
// }

// void    doom(t_env *env)
// {
// 	const Uint8 *keystates;
// 	int w, h;

// 	display(env);
// 	while (!env->quit)
// 	{

// 		while (SDL_PollEvent(&env->e) != 0 || env->e.key.repeat == 0)
// 		{
// 			if (env->e.window.event == SDL_WINDOWEVENT_RESIZED)
// 			{
// 				SDL_GetWindowSize(env->win, &w, &h);
// 				env->width = w;
// 				env->height = h;
// 			}
// 			keystates = SDL_GetKeyboardState(NULL);
// 			if (env->quit == 1)
// 				break;
// 			control(env, keystates);
// 			display(env);
// 		}
// 		SDL_Delay(200);
// 	}
// }

void		init(t_env *env)
{
	if (SDL_Init(SDL_INIT_VIDEO))
		ft_error("Couldn't initialize SDL");
	if (!(env->win = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0)))
		ft_error("Could not create the window");
	if (!(env->render = SDL_CreateRenderer(env->win, -1, SDL_RENDERER_SOFTWARE)))
		ft_error("Could not create a renderer");
	env->quit = 0;
}

// void			editeur_setup(t_env *v)
// {
	
// }

int			main(int argc, char **argv)
{
	t_env	*env;
	int		fd;

	fd = 0;
	if (!(env = ft_memalloc(sizeof(t_env))))
		return (0);
	if (argc != 2 || (fd = open(argv[1], O_RDONLY)) < 0)
		return (0);
	init(env);
	//editeur_setup(env);
	display(env);
	return (0);
}
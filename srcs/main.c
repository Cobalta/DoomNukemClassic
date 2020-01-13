/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nrivoire <nrivoire@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/28 15:26:14 by ebourgeo     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/13 09:18:59 by nrivoire    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editeur.h"

void		init(t_env *env)
{
	if (SDL_Init(SDL_INIT_VIDEO))
		ft_error("Couldn't initialize SDL");
	if (!(env->win = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0)))
		ft_error("Could not create the window");
	if (!(env->ren = SDL_CreateRenderer(env->win, -1, SDL_RENDERER_SOFTWARE)))
		ft_error("Could not create a renderer");
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
	//if (argc != 2 || (fd = open(argv[1], O_RDONLY)) < 0)
	//	return (0);
	init(env);
	//editeur_setup(env);
	display(env);
	return (0);
}
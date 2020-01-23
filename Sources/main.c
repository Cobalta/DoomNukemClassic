/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tprzybyl <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/29 19:45:13 by tprzybyl     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/25 16:43:41 by tprzybyl    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

void	drawsector(t_param *p, int actual, int min, int max, int ans)
{
	int			i;

	i = 0;
	while (i < p->map->sect[actual - 1].cwall)
	{
		p->actual = actual - 1;
		tiny_function(p, i, min, max, ans);
		i++;
	}
}

int			main(int ac, char **av)
{
	t_param			*param;
	SDL_Event		e;
	int				fd;
	SDL_Surface		*xxx;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return (1);
	if (-1 == (fd = open(av[1], O_RDONLY)))
		error_func(-2);
	if (!(param = malloc(sizeof(t_param))))
		error_func(-1);


	ac = 0;
	param->win = SDL_CreateWindow("General Kenobi! *cough cough*"
			, SDL_WINDOWPOS_CENTERED
			, SDL_WINDOWPOS_CENTERED
			, WINL, WINH,
			0);
	//			SDL_WINDOW_FULLSCREEN_DESKTOP);

	param->ren = SDL_CreateRenderer(param->win, -1, SDL_RENDERER_SOFTWARE);
	readmap(fd, param);
	SDL_SetRenderDrawColor(param->ren, 255, 255, 255, 255);

	if ((xxx = SDL_LoadBMP("./Textures/rock.bmp")) == NULL)
	printf("%s\n", SDL_GetError());
	param->xxx = xxx;
	param->quit = 1;
	param->eve.a = 0;
	param->eve.w = 0;
	param->eve.d = 0;
	param->eve.s = 0;
	param->eve.r = 0;
	while (param->quit)
	{
		event_manager(&e, param);
	}
	SDL_DestroyWindow(param->win);
	SDL_Quit();
	return (0);
}

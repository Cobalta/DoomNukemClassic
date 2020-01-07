/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nrivoire <nrivoire@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/07 15:57:04 by nrivoire     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/07 17:15:52 by nrivoire    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h"

void			events(t_env *v, SDL_Event event)
{
	const Uint8	*keyboard_state;

	keyboard_state = SDL_GetKeyboardState(NULL);
	if (event.type == SDL_KEYDOWN)
		key_event(keyboard_state, v);
	if (event.type == SDL_MOUSEBUTTONDOWN)
		mouse_button_event(event, v);
	if (event.type == SDL_MOUSEMOTION)
		mouse_motion_event(event, v);
}

void			display(t_env *v)
{
	SDL_Event	event;

	while (1)
	{
		while (SDL_PollEvent(&event))
			events(v, event);
		if (event.type == SDL_QUIT)
			break ;
		SDL_RenderPresent(v->render);
	}
	SDL_DestroyRenderer(v->render);
	SDL_DestroyWindow(v->win);
	SDL_Quit();
}

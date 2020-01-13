/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   events.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nrivoire <nrivoire@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/07 17:14:18 by nrivoire     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/13 09:27:31 by nrivoire    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editeur.h"

void		mouse_button_event(SDL_Event event, t_env *v)
{
	if (event.button.button == SDL_BUTTON_LEFT)
		draw_full_circle(v, event.button.x, event.button.y, make_rgb(204, 255, 255, 255));
	if (event.button.button == SDL_BUTTON_RIGHT)
		draw_void_circle(v, event.button.x, event.button.y, make_rgb(204, 255, 255, 255));
}

void		mouse_motion_event(SDL_Event event, t_env *v)
{

}

int			key_event(const Uint8 *keyboard_state, t_env *v)
{
	if (keyboard_state[SDL_SCANCODE_ESCAPE])
		return (1);
	return (0);
}

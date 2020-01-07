/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   events.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nrivoire <nrivoire@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/07 17:14:18 by nrivoire     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/07 17:17:27 by nrivoire    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h"

void		mouse_button_event(SDL_Event event, t_env *v)
{
    
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

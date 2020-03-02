/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:31:09 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/02 17:39:07 by tprzybyl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H
# include "../libft/libft.h"
# include <pthread.h>
# include <math.h>
# include <../SDL/Headers/SDL.h>
# include <../SDL/Headers/SDL_surface.h>
# include <../SDL/Headers/SDL_video.h>
# include <../SDL/Headers/SDL_render.h>
# include <../SDL/Headers/SDL_pixels.h>
# include <../SDL/Headers/SDL_events.h>
#define WINH 800
#define WINL 1000

typedef struct	s_ipos
{
	int				x;
	int				y;
	int				z;
}				t_ipos;

typedef struct	s_dpos
{
	double			x;
	double			y;
}				t_dpos;

typedef struct	s_qdpos
{
	t_dpos			a;
	t_dpos			b;
	t_dpos			c;
	t_dpos			d;
	t_dpos			ta;
	t_dpos			tb;
	int				min;
	int				max;
	int				go;

}				t_qdpos;

typedef struct	s_wall
{
	int			ypix;
	int			xpix;
	t_dpos		a;
	t_dpos		b;
	double		len;
	int			portal;
}				t_wall;

typedef struct	s_sector
{
	int			top;
	int			bot;
	int			cwall;
	t_wall		*wall;
}				t_sector;

typedef struct	s_entity
{
	t_dpos		pos;
	int			type;
	int			esct;
	double		ang;
	int			scale;
	int			z;
	t_ipos		speed;
	int			maxspeed;
	int			hp;
	SDL_Surface	*art;
}				t_entity;

typedef struct	s_map
{
	t_sector	*sect;
	t_entity	entities[512];
	t_dpos		pos;
	int			centities;
	int			ctsector;
	int			psct;
	int			pz;
	int			pcrouch;
	t_ipos		pspeed;
	double		ang;
	double		baseang;
	int			basepsct;
	t_dpos		basepos;
}				t_map;

typedef struct	s_event
{
	int		a;
	int		w;
	int		s;
	int		d;
	int		r;
}				t_event;

typedef struct	s_actcase
{
	t_entity	*data;
}				t_actcase;

typedef struct	s_param
{
	SDL_Surface		*xxx;
	SDL_Surface		*surf;
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Texture		*texture;
	t_map			*map;
	t_event			eve;
	t_actcase		actmap[WINL][WINH];
	char			quit;
	int				consty;
	int				i;
	int				dx;
	int				dy;
	int				actual;
	int				diff;
}				t_param;

void	mouse_button_event(SDL_Event event, t_param *p);
void	renderentities(t_param *p, int i, int actual, int min, int max);
void	readentity(t_param *p, t_entity *e, int type);
void	put_pixel(SDL_Surface *surf, int x, int y, int color);
void	gettexturex(t_param *p, t_qdpos *coor, t_dpos up, t_wall *w);
void	setcleanactmap(t_param *p);
void	loop(t_param *p);
int		checkcolls(t_map *map, t_sector *sect, double x, double y);
void	doom(t_param *p);
void	setup(t_param *p);
void	error_func(int code);
void	readmap(int fd, t_param *param);
void	drawline(t_dpos *src, t_dpos *dst, t_param *param);
void	drawtexedline(t_dpos *src, t_dpos *dst, t_param *p, t_wall *w);
void	drawspritedline(t_dpos *src, t_dpos *dst, t_param *p, t_entity *e);
void	drawminimap(t_param *p, t_map *map, t_dpos dest);
void	drawsector(t_param *p, int actual, int min, int max, int ans);
void	event_manager(SDL_Event *e, t_param *p);
void	getcoor(t_qdpos *coor, t_param *p, int i, int k);
void	render(t_param *p, int i, int min, int max, int ans);
void	wewillbuildawall(t_qdpos *coor, t_param *p, t_wall *w);
void	wewillbuildaportal(t_qdpos *coor, t_param *p, int port, int i);
void	wewillbuildanentity(t_qdpos *coor, t_param *p, t_entity *e);
void	videoloop(t_param *p);
void	gameloop(t_param *p, SDL_Event event, const Uint8 *keystat);

#endif

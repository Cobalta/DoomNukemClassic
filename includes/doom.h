/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprzybyl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:31:09 by tprzybyl          #+#    #+#             */
/*   Updated: 2020/03/11 18:04:30 by tprzybyl         ###   ########lyon.fr   */
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
# include <../sdl2_mixer/2.0.4/include/SDL2/SDL_mixer.h>

#define WINH 600
#define WINL 800

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
	int			botypix;
	int			xpix;
	t_dpos		a;
	t_dpos		b;
	double		len;
	int			portal;
	SDL_Surface	*art;
	SDL_Surface	*botart;
}				t_wall;

typedef struct	s_sector
{
	int			id;
	int			top;
	int			bot;
	int			cwall;
	t_wall		*wall;
	SDL_Surface	*topart;
	SDL_Surface	*botart;
}				t_sector;

typedef struct	s_entity
{
	t_dpos		pos;
	t_dpos		tgtpos;
	void		*addr;
	int			spot;
	int			state;
	int			type;
	int			psct;
	double		ang;
	double		tgtang;
	int			scale;
	int			lock;
	int			pz;
	t_ipos		speed;
	double		rotspeed;
	int			maxspeed;
	int			boost;
	int			fov;
	int			hp;
	int			range;
	int			damage;
	SDL_Surface	*art;
}				t_entity;

typedef struct	s_weapon
{
	int			range;
	int			tmpstrike;
	t_dpos		sweeps[4][2];
	SDL_Surface *art[7];
	int			tmpmass;
	int			mass[4];
	int			damage[4];
	int			impact[4];
	int			reloadspeed[4];
	int			defence;
}				t_weapon;

typedef struct	s_map
{
	t_sector	*sect;
	t_entity	entities[512];
	t_entity	sortentities[512];
	t_dpos		pos;
	int			status;
	int			alock;
	int			weap;
	t_weapon	weaplst[5];
	int			defence;
	int			hp;
	int			centities;
	int			ctsector;
	int			psct;
	int			pz;
	int			pcrouch;
	t_ipos		speed;
	int			fly;
	double		ang;
	double		baseang;
	int			basepsct;
	t_dpos		basepos;
}				t_map;


typedef struct	s_sounds
{
	Mix_Chunk *step[4];
	Mix_Chunk *jump[3];
}				t_sounds;

typedef struct	s_event
{
	int		a;
	int		w;
	int		s;
	int		d;
	int		r;
}				t_event;

typedef union	s_actcase
{
	t_entity	*data;
}				t_actcase;

typedef struct	s_param
{
	SDL_Surface		*art[64];
	SDL_Surface		*ratart[7][8];
	SDL_Surface		*surf;
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Texture		*texture;
	t_map			*map;
	t_event			eve;
	t_sounds		s;
	t_actcase		actmap[WINL][WINH];
	char			quit;
	int				consty;
	int				dx;
	int				dy;
	int				actual;
	int				diff;
}				t_param;

void	defregen(t_map *map, int t);
void	pushdeliver(t_map *map, t_entity *ent);
void	entaccel(t_entity *ent, int y, int x);
void	behaverecover(t_entity *ent, int id, t_map *map, int t);
void	arms(t_param *p);
void	lineactmap(t_dpos *src, t_dpos *dst, t_param *p, t_weapon *wp);
void	createweapon_2hsword(t_weapon *weap);
void	hudelement(t_param *p, SDL_Surface *elem);
void	mouse_hold_event(SDL_Event e, t_param *p);
void	mouse_button_event(SDL_Event event, t_param *p);
void	renderentities(t_param *p, int i, int actual, int min, int max);
void	readentity(t_param *p, t_entity *e, t_map *map);
void	put_pixel(SDL_Surface *surf, int x, int y, int color);
void	gettexturex(t_param *p, t_qdpos *coor, t_dpos up, t_wall *w);
void	setcleanactmap(t_param *p);
void	loop(t_param *p);
int		checkcolls(t_map *map, t_sector *sect, double x, double y);
int		aicheckcolls(t_map *map, t_entity *ent, double x, double y);
void	doom(t_param *p, int fd);
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
void	wewillbuildaportal(t_qdpos coor, t_param *p, t_qdpos newcoor, t_wall *w);
void	wewillbuildanentity(t_qdpos *coor, t_param *p, t_entity *e);
void	videoloop(t_param *p);
void	gameloop(t_param *p, SDL_Event event, const Uint8 *keystat);
void	audioloop(t_param *p);
int		key_event(const Uint8 *keyboard_state, t_param *p, SDL_Event *e);
int		getwall(int ow, t_sector *os, t_sector *ns);
void	assignratart_idle(t_param *p);
int		nextatoi(char **str);
void	checkend(char **str);
void	ai(t_param *p);
double	distent(t_dpos ent, t_dpos pos);
void	entcollision(t_entity *ent, int id, t_map *map);
int		angark(double ang, double relang, double fov);

#endif

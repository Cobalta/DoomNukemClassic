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
# define WINH 600
# define WINL 800
# define RAT "./Textures/xlrat/"
# include "../libft/libft.h"
# include <pthread.h>
# include <math.h>
# include <stdint.h>
# include "/usr/include/SDL2/SDL.h"
# include "/usr/include/SDL2/SDL_mixer.h"
# include "/usr/include/SDL2/SDL_image.h"
# include "/usr/include/SDL2/SDL_ttf.h"

typedef struct	s_ipos
{
	int			x;
	int			y;
	int			z;
}				t_ipos;

typedef struct	s_dpos
{
	double		x;
	double		y;
}				t_dpos;

typedef struct	s_qdpos
{
	t_dpos		a;
	t_dpos		b;
	t_dpos		c;
	t_dpos		d;
	t_dpos		ta;
	t_dpos		tb;
	int			min;
	int			max;
	int			go;

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
	void		*sect;
	SDL_Surface	*art;
	SDL_Surface	*botart;
}				t_wall;

typedef struct	s_sector
{
	int			id;
	int			top;
	int			bbot;
	int			btop;
	int			bot;
	int			cwall;
	t_wall		*wall;
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
	int			os;
	t_ipos		lever;
	SDL_Surface	*art;
}				t_entity;

typedef struct	s_ws
{
	Mix_Chunk	*swipe[6];
	Mix_Chunk	*block[3];
}				t_ws;

typedef struct	s_weapon
{
	t_ws		w_s;
	int			range;
	int			tmpstrike;
	t_dpos		sweeps[4][2];
	SDL_Surface	*art[7];
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
	int			cburrows;
	int			ctsector;
	int			psct;
	int			pz;
	int			pcrouch;
	t_ipos		speed;
	int			fly;
	int			power;
	int			powert;
	double		ang;
	double		baseang;
	int			basepsct;
	t_dpos		basepos;
}				t_map;

typedef struct	s_sounds
{
	Mix_Chunk	*step[4];
	Mix_Chunk	*jump[4];
	Mix_Chunk	*skaven[4];
	Mix_Chunk	*player[3];
	Mix_Chunk	*dig[3];
	Mix_Music	*music;
	int			sk_cooldown;
}				t_sounds;

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
	SDL_Surface		*art[64];
	SDL_Surface		*ratart[7][8];
	SDL_Surface		*surf;
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Texture		*texture;
	SDL_Color		col;
	TTF_Font		*font;
	t_map			*map;
	t_event			eve;
	t_sounds		s;
	t_actcase		actmap[WINL][WINH];
	char			diflvl;
	char			quit;
	int				consty;
	int				dx;
	int				dy;
	int				actual;
	int				ans;
	int				diff;
}				t_param;

void			freeofdoom(t_param *p);
void			lowerstartingvalues(t_qdpos *coor,
					t_dpos *up, t_dpos *down, int i);
void			startingvalues(t_qdpos *coor, t_dpos *up, t_dpos *down, int i);
int				sctnb(t_wall *w, t_param *p);
void			drawcline(t_dpos *up, t_dpos *down, t_param *p, int c);
void			strikedeliver(t_param *p, t_entity *ent, t_weapon *wp);
void			ratstrike(t_entity *ent, t_param *p);
void			getentitycoor(t_qdpos *coor, t_param *p, t_entity e, int i);
int				checklos(t_entity *ent, t_map *map);
void			ratsspacing(t_entity *ent, t_map *map);
void			behavespot(t_entity *ent, t_map *map);
void			behaveattack(t_entity *ent, int id, t_param *p);
void			behavewander(t_entity *ent, int id);
void			behaverecover(t_entity *ent, int id, t_param *p, int t);
void			behavemove(t_entity *ent, t_map *map);
void			gravity(t_param *p, t_entity *ent);
void			burrow(t_entity *ent, t_param *p, int id);
void			lever(t_entity *e, t_map *map);
void			adrenaline(t_entity *ent, t_param *p);
void			potion(t_entity *ent, t_param *p);
void			entitymovement(t_param *p, t_entity *ent, int id);
int				aireccolls(t_map *map, t_entity *ent, t_dpos dest, int ow);
int				aiportalcoll(t_map *map, t_entity *ent, t_dpos dest, int i);
int				portalcoll(t_map *map, t_sector *os, t_dpos dest, int ow);
int				reccolls(t_map *map, t_sector *os, t_dpos dest, int ow);
void			ratartpick(t_param *p, t_entity *ent, int max, t_dpos pos);
void			copyentities(t_map *map);
void			orderentities(t_entity *ent, int max, t_dpos pos);
int				pthfind(t_entity *ent, t_map *map, t_sector sct, int rec);
void			setcolor(SDL_Color *col, int r, int g, int b);
void			gettexturex(t_param *p, t_qdpos *coor, t_dpos ln, t_wall *w);
void			xgettexturex(t_param *p, t_qdpos *coor, t_dpos ln, t_wall *w);
void			uxgettexturex(t_param *p, t_qdpos *coor, t_dpos ln, t_wall *w);
double			distentz(t_entity *ent, t_map *map);
int				crossline(t_dpos i, t_dpos j, t_dpos k, t_dpos l);
void			defregen(t_map *map, int t);
void			pushdeliver(t_param *p, t_entity *ent);
void			entaccel(t_entity *ent, int y, int x, int z);
void			behaverecover(t_entity *ent, int id, t_param *p, int t);
void			arms(t_param *p);
void			show_hud(t_param *p);
void			lineactmap(t_dpos *src, t_dpos *dst, t_param *p, t_weapon *wp);
void			createweapon_2hsword(t_weapon *weap);
void			hudelement(t_param *p, SDL_Surface *elem);
void			mouse_hold_event(SDL_Event e, t_param *p);
void			mouse_button_event(SDL_Event event, t_param *p);
void			renderentities(t_param *p, int max[2], int w);
void			entitiesinit(t_param *p);
void			put_pixel(SDL_Surface *surf, int x, int y, int color);
void			setcleanactmap(t_param *p);
void			loop(t_param *p, SDL_Event event);
int				checkcolls(t_map *map, t_sector *sect, double x, double y);
int				aicheckcolls(t_map *map, t_entity *ent, double x, double y);
void			doom(t_param *p, int fd);
void			setup(t_param *p);
void			error_func(int code);
void			readmap(int fd, t_param *param);
void			drawline(t_dpos *src, t_dpos *dst, t_param *param);
void			drawtexedline(t_dpos *src, t_dpos *dst, t_param *p, t_wall *w);
void			drawspritedline(t_dpos *src, t_dpos *dst,
					t_param *p, t_entity *e);
void			drawsector(t_param *p, int actual, int max[2], int ans);
void			getcoor(t_qdpos *coor, t_param *p, int i, int s);
void			render(t_param *p, int w, int max[2], int ans);
void			wewillbuildawall(t_qdpos *coor, t_param *p, t_wall *w);
void			buildaportal(t_qdpos coor, t_param *p,
					t_qdpos newcoor, t_wall *w);
void			wewillbuildanentity(t_qdpos *coor, t_param *p, t_entity *e);
void			videoloop(t_param *p);
void			gameloop(t_param *p, const Uint8 *keystat);
void			audioloop(t_param *p);
int				key_event(const Uint8 *keyboard_state,
					t_param *p, SDL_Event *e);
int				getwall(int ow, t_sector *os, t_sector *ns);
void			assignratart_idle(t_param *p);
int				nextatoi(char **str, int i, int neg);
void			checkend(char **str);
void			ai(t_param *p);
double			distent(t_dpos ent, t_dpos pos);
void			entcollision(t_entity *ent, t_map *map);
int				angark(double ang, double relang, double fov);
void			behaveaudio(t_param *p, int state);
void			power_up(t_map *map, t_weapon *weap, int i, int boost);
void			readsector(char **str, t_sector *s, t_param *p);
void			readentities(char **str, t_entity *e);
void			xpixlensandart(t_wall *w, char **str, t_param *p);
void			free_audio(t_sounds s);
void			start_menu(t_param *p);
void			movement_z(const Uint8 *keystat, t_param *p);
void			assignratart_movea(t_param *p);

#endif

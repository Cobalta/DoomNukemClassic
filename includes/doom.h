/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   doom.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ebourgeo <ebourgeo@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/23 16:26:07 by ebourgeo     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/23 16:26:07 by ebourgeo    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
#define WINH 1000
#define WINL 1200

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

typedef struct	s_map
{
	t_sector	*sect;
	t_dpos		pos;
	int			ctsector;
	int			psct;
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

typedef struct	s_param
{
	SDL_Surface		*xxx;
	SDL_Window		*win;
	SDL_Renderer	*ren;
	t_map			*map;
	t_event			eve;
	char			quit;
	int				dx;
	int				dy;
	int				actual;
	int				diff;
}				t_param;

int		checkcolls(t_map *map, t_sector *sect, double x, double y);
void	doom(t_param *p);
void	setup(t_param *p);
void	error_func(int code);
void	readmap(int fd, t_param *param);
void	drawline(t_dpos *src, t_dpos *dst, t_param *param);
void	drawtexedline(t_dpos *src, t_dpos *dst, t_param *p, t_wall *w);
void	drawminimap(t_param *p, t_map *map);
void	drawsector(t_param *p, int actual, int min, int max, int ans);
void	event_manager(SDL_Event *e, t_param *p);
void	getcoor(t_qdpos *coor, t_param *p, int i, int k);
void	render(t_param *p, int i, int min, int max, int ans);
void	wewillbuildawall(t_qdpos *coor, t_param *p, t_wall *w);
void	wewillbuildaportal(t_qdpos *coor, t_param *p, int port, int i);

#endif

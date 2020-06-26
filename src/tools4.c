#include "../includes/doom.h"

static Uint32		getpixel(SDL_Surface *surface, int x, int y)
{
	int			bpp;
	Uint8		*p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 1)
		return (*p);
	else if (bpp == 2)
		return (*(Uint16 *)p);
	else if (bpp == 3)
		return (p[0] | p[1] << 8 | p[2] << 16);
	else if (bpp == 4)
		return (*(Uint32 *)p);
	return (0);
}

static void		facepick(t_param *p, t_entity *ent, double sideangle)
{
	if (sideangle > .3839 && sideangle <= 1.1693)
		ent->art = p->ratart[ent->state][7];
	else if (sideangle > 1.1693 && sideangle <= 1.9547)
		ent->art = p->ratart[ent->state][6];
	else if (sideangle > 1.9547 && sideangle <= 2.7401)
		ent->art = p->ratart[ent->state][5];
	else if (sideangle > 2.7401 && sideangle <= 3.5255)
		ent->art = p->ratart[ent->state][4];
	else if (sideangle > 3.5255 && sideangle <= 4.3109)
		ent->art = p->ratart[ent->state][3];
	else if (sideangle > 4.3109 && sideangle <= 5.0963)
		ent->art = p->ratart[ent->state][2];
	else if (sideangle > 5.0963 && sideangle <= 5.8817)
		ent->art = p->ratart[ent->state][1];
	else
		ent->art = p->ratart[ent->state][0];
}

void			ratartpick(t_param *p, t_entity *ent, int max, t_dpos pos)
{
	int			i;
	double		sideangle;

	i = -1;
	while (i++ < max - 1)
	{
		if (ent[i].type == 1)
		{
			sideangle = fmod((acos((ent[i].pos.x - pos.x)
			* 1 / (distent(ent[i].pos, pos)))), 6.2831);
			sideangle = (ent[i].pos.y < pos.y) ? 6.2831 -
				sideangle : sideangle;
			sideangle -= ent[i].ang;
			sideangle = (sideangle < 0) ? 6.2831 + sideangle : sideangle;
			facepick(p, &ent[i], sideangle);
		}
	}
}

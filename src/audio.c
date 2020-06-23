
#include "../includes/doom.h"

void	audioloop(t_param *p)
{
	static int s_delay = 75;

	if ((abs(p->map->speed.x) > 0 || abs(p->map->speed.y) > 0) &&
		p->map->pz == p->map->sect[p->map->psct - 1].bot)
	{
		if (abs(p->map->speed.x) > abs(p->map->speed.y))
			s_delay -= abs(p->map->speed.x);
		else
			s_delay -= abs(p->map->speed.y);
		if (s_delay <= 0)
		{
			s_delay = 75;
			Mix_PlayChannel(-1, p->s.step[rand() % 3], 0);
		}
	}
}

void	behaveaudio(t_param *p, int state)
{
	if (state == 5)
	{
		Mix_PlayChannel(-1, p->s.skaven[1], 0);
	}
	if (state == 3)
		Mix_PlayChannel(-1, p->s.skaven[3], 0);
	if (p->s.sk_cooldown <= 0)
	{
		Mix_PlayChannel(-1, p->s.skaven[0], 0);
		p->s.sk_cooldown = 500;
	}
	else
		p->s.sk_cooldown--;
}


#include "doom.h"

//t_sounds loadaudio(t_param *p)
//{
//	t_sounds s;
//	s.step = Mix_LoadWAV("sounds/pl_step1.wav");
//}

void	audioloop(t_param *p)
{
	//Stepping noises
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
			Mix_PlayChannel(1, p->s.step[rand() % 3], 0);
		}
	}
}

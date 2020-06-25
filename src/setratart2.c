#include "../includes/doom.h"

void	assignratart_moveb(t_param *p)
{
	if ((p->ratart[2][0] = SDL_LoadBMP(RAT"move2/0.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[2][1] = SDL_LoadBMP(RAT"move2/45.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[2][2] = SDL_LoadBMP(RAT"move2/90.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[2][3] = SDL_LoadBMP(RAT"move2/135.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[2][4] = SDL_LoadBMP(RAT"move2/180.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[2][5] = SDL_LoadBMP(RAT"move2/225.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[2][6] = SDL_LoadBMP(RAT"move2/270.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[2][7] = SDL_LoadBMP(RAT"move2/315.bmp")) == NULL)
		error_func(-3);
	assignratart_movea(p);
}

void	assignratart_idle(t_param *p)
{
	if ((p->ratart[0][0] = SDL_LoadBMP(RAT"idle/0.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[0][1] = SDL_LoadBMP(RAT"idle/45.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[0][2] = SDL_LoadBMP(RAT"idle/90.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[0][3] = SDL_LoadBMP(RAT"idle/135.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[0][4] = SDL_LoadBMP(RAT"idle/180.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[0][5] = SDL_LoadBMP(RAT"idle/225.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[0][6] = SDL_LoadBMP(RAT"idle/270.bmp")) == NULL)
		error_func(-3);
	if ((p->ratart[0][7] = SDL_LoadBMP(RAT"idle/315.bmp")) == NULL)
		error_func(-3);
	assignratart_moveb(p);
}

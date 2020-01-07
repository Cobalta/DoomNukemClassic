/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tga_parser.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nrivoire <nrivoire@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/15 09:31:49 by nrivoire     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/07 14:48:45 by nrivoire    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tga_parser.h"

//gcc -Wall -Wextra -fsanitize=address -L sdl2/2.0.10/lib/ -lSDL2 libft/libft.a tga_parser.c  && ./a.out chat.tga

char				*get_chunk(char chunk)
{
	char			*str;
	char			rep[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	int				i;
	int				j;

	i = -1;
	j = 0;
	str = ft_strnew(2);
	while (++i < 1)
	{
		str[j] = rep[(chunk >> 4) & 0x0F];
		str[j + 1] = rep[chunk & 0x0F];
		j = j + 2;
	}
	return (str);
}

t_px				make_pixel(unsigned char *byte, int byte_size)
{
	t_px			px;

	if (byte_size == 4)
	{
		px.r = ft_atoi_base(get_chunk(byte[2]), 16);
		px.g = ft_atoi_base(get_chunk(byte[1]), 16);
		px.b = ft_atoi_base(get_chunk(byte[0]), 16);
		px.a = ft_atoi_base(get_chunk(byte[3]), 16);
	}
	else if (byte_size == 3)
	{
		px.r = ft_atoi_base(get_chunk(byte[2]), 16);
		px.g = ft_atoi_base(get_chunk(byte[1]), 16);
		px.b = ft_atoi_base(get_chunk(byte[0]), 16);
		px.a = 255;
	}
	else
	{
		px.r = ft_atoi_base(get_chunk((byte[1] & 0x7c) << 1), 16);
		px.g = ft_atoi_base(get_chunk(((byte[1] & 0x03) << 6) | ((byte[0] & 0xe0) >> 2)), 16);
		px.b = ft_atoi_base(get_chunk((byte[0] & 0x1f) << 3), 16);
		px.a = ft_atoi_base(get_chunk(byte[1] & 0x80), 16);
	}
	return (px);
}

t_px				*save_tga_rgba(int fd, t_px *px, t_header h, int byte_size)
{
	int				i;
	unsigned int	n;
	int				ret;
	unsigned char	byte[byte_size];

	ret = 0;
	n = -1;
	while ((ret = read(fd, byte, byte_size)) > 0 && (++n < (h.height * h.width)))
	{
		if (h.datatypecode == 2)
			px[n] = make_pixel(byte, byte_size);
		else if (h.datatypecode == 10)
		{
			px[n] = make_pixel(&(byte[1]), byte_size);
			if ((byte[0] & 0x80) && (i == -1))
			{
				i = -1;
				while (++i < (byte[0] & 0x7f))
					px[n] = make_pixel(&(byte[1]), byte_size);
			}
			else
			{
				i = -1;
				while (++i < (byte[0] & 0x7f))
					px[n] = make_pixel(byte, byte_size);
			}
		}
	}
	return (px);
}

t_header			save_header_tga(t_header h, int fd)
{
	int 			ret;
	char			buff[18];

	ret = 0;
	while ((ret = read(fd, buff, 18)))
	{
		h.idlength = buff[0];
		h.colourmaptype = buff[1];
		h.datatypecode = buff[2];
		h.colourmaporigin = buff[3];
		h.colourmaplength = buff[5];
		h.colourmapdepth = buff[7];
		h.x_origin = buff[8];
		h.y_origin = buff[10];
		h.width = ft_atoi_base(ft_strjoin(get_chunk(buff[11]), get_chunk(buff[12])), 16);
		h.height = ft_atoi_base(ft_strjoin(get_chunk(buff[13]), get_chunk(buff[14])), 16);
		h.bitsperpixel = buff[16];
		h.imagedescriptor = buff[17];
		break;
	}
	if (h.datatypecode != 2 && h.datatypecode != 10)
		ft_error("Can only handle image type 2 and 10");
	if (h.bitsperpixel != 16 && h.bitsperpixel != 24 && h.bitsperpixel != 32)
		ft_error("Can only handle pixel depths of 16, 24, and 32");
	if (h.colourmaptype != 0 && h.colourmaptype != 1)
		ft_error("Can only handle colour map types of 0 and 1");
	return (h);
}

t_tga				*tga_parser(char *img)
{
	t_tga			*tga;
	int				fd;

	if ((fd = open(img, O_RDONLY)) < 0)
		return (0);
	if (!(tga = ft_memalloc(sizeof(tga))))
		return (0);
	tga->h = save_header_tga(tga->h, fd);
	if (!(tga->px = malloc(sizeof(t_px) * (tga->h.width * tga->h.height))))
		ft_error("The malloc of the pixel struct didn't work.");
	tga->px = save_tga_rgba(fd, tga->px, tga->h, tga->h.bitsperpixel / 8);
	return (tga);
}

int		main(int argc, char **argv)
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	t_tga			*tga;
	SDL_Event		event;
	const Uint8		*keyboard_state;

	if (argc != 2)
		return (0);
	if (SDL_Init(SDL_INIT_VIDEO))
		ft_error("Couldn't initialize SDL");
	if (!(win = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0)))
		ft_error("Could not create the window");
	if (!(ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE)))
		ft_error("Could not create a renderer");
	tga = tga_parser(argv[1]);
	printf("height = %d width = %d\n", tga->h.height, tga->h.width);
	while (1)
	{
		while (SDL_PollEvent(&event))
		{
			keyboard_state = SDL_GetKeyboardState(NULL);
			if (keyboard_state[SDL_SCANCODE_ESCAPE])
				exit(0);
		}
		if (event.type == SDL_QUIT)
			break ;
		unsigned int i = -1;
		int y = -1;
		int x = -1;
		while (++y < HEIGHT)
		{
			x = -1;
			while (++x < WIDTH && ++i < tga->h.width * tga->h.height)
			{
				SDL_SetRenderDrawColor(ren, tga->px[i].r, tga->px[i].g, tga->px[i].b, tga->px[i].a);
				SDL_RenderDrawPoint(ren, x, y);
			}
		}
		SDL_RenderPresent(ren);
	}
	return (0);
}

#  ************************************************************************** #
#                                                           LE - /            #
#                                                               /             #
#    Makefile                                         .::    .:/ .      .::   #
#                                                  +:+:+   +:    +:  +:+:+    #
#    By: brey-gal <brey-gal@student.le-101.fr>      +:+   +:    +:    +:+     #
#                                                  #+#   #+    #+    #+#      #
#    Created: 2019/08/01 03:24:58 by brey-gal     #+#   ##    ##    #+#       #
#    Updated: 2019/11/22 16:06:18 by ebourgeo    ###    #+. /#+    ###.fr      #
#                                                          /                  #
#                                                         /                   #
#  ************************************************************************** #

NAME = doom-nukem

LIBS =  libft/ft_puterror.c	\
        libft/ft_putstr.c	\
        libft/ft_strnew.c	\
        libft/ft_strjoin.c	\
        libft/ft_strcpy.c	\
        libft/ft_strsub.c	\
        libft/ft_strlen.c	\
        libft/ft_strdup.c	\
        libft/ft_atoi.c		\
        libft/ft_itoa.c

SRCS =	srcs/main.c		\
		srcs/setup.c	\
		srcs/control.c  \
		srcs/render.c   \
		srcs/line_tracer.c \

OBJS =	$(SRCS:.c=.o)

OBJSLIB = $(LIBS:.c=.o)

LIB = -L. libft/libft.a

INC =	includes/struct.h	\
		includes/doom.h		\
		libft/libft.h

CC = gcc

CFLAGS	+= -O3

SDL2 = -I include -L lib -l SDL2-2.0.0

all : $(NAME)
	clear
	@echo "$'\x1b[32m   ▄████████  ▄█        ▄█            ████████▄   ▄██████▄  ███▄▄▄▄      ▄████████    "
	@echo "  ███    ███ ███       ███            ███   ▀███ ███    ███ ███▀▀▀██▄   ███    ███    "
	@echo "  ███    ███ ███       ███            ███    ███ ███    ███ ███   ███   ███    █▀     "
	@echo "  ███    ███ ███       ███            ███    ███ ███    ███ ███   ███  ▄███▄▄▄        "
	@echo "▀███████████ ███       ███            ███    ███ ███    ███ ███   ███ ▀▀███▀▀▀        "
	@echo "  ███    ███ ███       ███            ███    ███ ███    ███ ███   ███   ███    █▄     "
	@echo "  ███    ███ ███▌    ▄ ███▌    ▄      ███   ▄███ ███    ███ ███   ███   ███    ███    "
	@echo "  ███    █▀  █████▄▄██ █████▄▄██      ████████▀   ▀██████▀   ▀█   █▀    ██████████    "
	@echo "             ▀         ▀                                                              $'\x1b[0m"

%.o: %.c $(INC)
		@echo "$'\x1b[31mCompiling :$'\x1b[0m $<$'\x1b[0m"
	    @$(CC) -c -o $@ $< -I ./includes/struct.h -I ./includes/doom3d.h -O3

flags :
		@echo "$'\x1b[31mFlags :$<$'\x1b[0m $'\x1b[35m$(CFLAGS)$<$'\x1b[0m"

libf : $(OBJSLIB)
		@ar ruc libft/libft.a $?
		@ranlib libft/libft.a
		@echo "$'\x1b[32mLibft.a created$'\x1b[0m"


$(NAME) : flags libf $(OBJS) $(INC)
		@echo "$'\x1b[31mCreating executable :$'\x1b[0m $(NAME)"
		@$(CC) -o $(NAME) -O3 $(OBJS) $(LIB) $(SDL2)

clean :
		@echo "$'\x1b[31mCleaning .o$'\x1b[0m"
		@rm -f $(OBJS) $(OBJSLIB)

fclean : clean
		@echo "$'\x1b[31mCleaning : $(NAME) & libft.a$'\x1b[0m"
		@rm -f $(NAME) libft/libft.a

re : fclean all

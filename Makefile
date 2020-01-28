# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: tprzybyl <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/03 11:36:22 by tprzybyl     #+#   ##    ##    #+#        #
#    Updated: 2019/06/18 14:46:59 by tprzybyl    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = doom-nukem

SRC_PATH = Sources
SRC_NAME =	main.c					\
			doom.c					\
			errors.c				\
			drawline.c				\
			events.c				\
			map.c					\
			collisions.c			\
			wallbuilder.c			\
			coordscalculator.c		\
			setup.c

OBJ_PATH = Objects
OBJ_NAME = $(SRC_NAME:.c=.o)

FLAGS = -O3 -lpthread -L libft -lft -F /Library/Frameworks/ -framework SDL2

SRC = $(addprefix $(SRC_PATH)/,$(srC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	@gcc $(FLAGS) $^ -o $@
	@echo ""$(NAME)" ready to go!\n"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@gcc -O3 -Wall -Wextra -I Includes -I libft -o $@ -c $<

clean:
	@rm -rf $(OBJ)
	@make -C libft/ clean
	@echo "Removing objects from "$(NAME)""

fclean: clean
	@rm -rf $(NAME)
	@make -C libft fclean
	@echo "Removing binary "$(NAME)""

re: fclean all

sdl2:
	brew install sdl2
	brew link sdl2

.PHONY: all clean fclean re

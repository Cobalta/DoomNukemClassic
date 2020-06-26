NAME = doom-nukem

SRC_PATH = src
SRC =	main.c					\
		doom.c					\
		errors.c				\
		drawline.c				\
		drawtex.c				\
		mouseevent.c			\
		entitiesinit.c			\
		keyevent.c				\
		loop.c					\
		gameloop.c				\
		videoloop.c				\
		map.c					\
		collisions.c			\
		wallbuilder.c			\
		wallbuildtools.c		\
		coordscalculator.c		\
		setup.c					\
		audio.c					\
		toolsparsing.c			\
		setratart.c				\
		setratart2.c			\
		ai.c					\
		aiactions.c				\
		aiprops.c				\
		aibehaviors.c			\
		aimove.c				\
		aitools.c				\
		aicollisions.c			\
		interaction.c			\
		render.c				\
		weapons.c				\
		tools4.c				\
		tools3.c				\
		tools2.c				\
		tools.c					\
		lineactmap.c			\
		free.c					\
		hud.c

OBJ_PATH = objects
OBJ_NAME = $(SRC:.c=.o)
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

LIB = -Llibft -lm

INC = includes/doom.h	\
		libft/libft.h

CC = clang

CFLAGS += -Wall -Wextra -Werror -O3

SDL2 = `sdl2-config --cflags`

SDL2bis = `sdl2-config --libs` -lSDL2_mixer -lSDL2_ttf

all : flags libft $(NAME)
	@clear
	@echo "   ▄████████  ▄█        ▄█            ████████▄   ▄██████▄  ███▄▄▄▄      ▄████████    "
	@echo "  ███    ███ ███       ███            ███   ▀███ ███    ███ ███▀▀▀██▄   ███    ███    "
	@echo "  ███    ███ ███       ███            ███    ███ ███    ███ ███   ███   ███    █▀     "
	@echo "  ███    ███ ███       ███            ███    ███ ███    ███ ███   ███  ▄███▄▄▄        "
	@echo "▀███████████ ███       ███            ███    ███ ███    ███ ███   ███ ▀▀███▀▀▀        "
	@echo "  ███    ███ ███       ███            ███    ███ ███    ███ ███   ███   ███    █▄     "
	@echo "  ███    ███ ███▌    ▄ ███▌    ▄      ███   ▄███ ███    ███ ███   ███   ███    ███    "
	@echo "  ███    █▀  █████▄▄██ █████▄▄██      ████████▀   ▀██████▀   ▀█   █▀    ██████████    "
	@echo "             ▀         ▀                                                              "

$(NAME) : $(OBJ)
	@echo "Creating executable : $(NAME)"
	@$(CC) -lpthread $(LIB) $(SDL2bis) $(OBJ) -lft -o $@

$(OBJ_PATH)/%.o : src/%.c $(INC)
	@mkdir -p objects
	@echo "Compiling : $@"
	@$(CC) $(CFLAGS) -c $< -o $@

sdl :
	@sudo apt-get install libsdl2-dev
	@sudo apt-get install libsdl2-image-dev
	@sudo apt-get install libsdl2-mixer-dev
	@sudo apt-get install libsdl2-ttf-dev

flags :
	@echo "Flags :$< $(CFLAGS) $<"

libft :
	@make -C ./libft

clean :
	@echo "Cleaning .o"
	@rm -rf objects

fclean : clean
	@echo "Cleaning : $(NAME) & libft.a"
	@make -C ./libft fclean
	@rm -f $(NAME) libft/libft.a

re : fclean all

.PHONY : libft

NAME		= fdf
CC			= gcc
FLAGS		= -O3 -Wall -Wextra -Werror
FLAGS_MLX	= -lXext -lX11 -lm -lz
RM			= rm -rf
AR			= ar rc
INC			= ./inc
INC_MLX		= ./minilibx_linux
INC_FILE	= ./inc/*
LIBFT		= libft/libft.a
MINILIBX	= minilibx-linux/libmlx_Linux.a

SRCS_PATH	= ./src/
OBJS_PATH	= ./objs/

SRCS_NAME	=	main.c read_map.c error.c get_next_line.c \
				get_next_line_utils.c helper_func.c draw.c \
				color.c param_view.c draw_turn.c draw2.c control.c
SRCS		= $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJS		= $(addprefix $(OBJS_PATH), $(SRCS_NAME:.c=.o))

all: $(LIBFT) $(MINILIBX) $(NAME)

$(NAME): $(OBJS_PATH) $(OBJS)
	$(CC) $(FLAGS) -L$(INC_MLX) $(OBJS) $(LIBFT) $(MINILIBX) -I$(INC_MLX) $(FLAGS_MLX) -o $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(INC_FILE)
	$(CC) $(FLAGS) -I $(INC) -I $(INC_MLX) -c $< -o $@

$(OBJS_PATH):
	mkdir -p $(OBJS_PATH)

$(MINILIBX):
	@make -C ./minilibx-linux

$(LIBFT):
	@make -C ./libft

clean: clean_libft
	$(RM) $(OBJS_PATH)

clean_libft:
	@make clean -C ./libft

clean_minilibx:
	@make clean -C ./minilibx-linux

fclean:		clean clean_minilibx
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)
	$(RM) $(LIBFT)

re:			fclean all

.PHONY: all clean fclean re $(LIBFT)

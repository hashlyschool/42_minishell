NAME			=	minishell
CC				=	clang
RM				=	rm -rf
FLAGS			=	-Wall -Wextra -Werror
#School MAC
FLAGS_RL		=	-lreadline -L/Users/${USER}/.brew/Cellar/readline/8.1.2/lib/ -I/Users/${USER}/.brew/Cellar/readline/8.1.2/include/
#Linux
# FLAGS_RL		=	-lreadline
LIBFT_PATH		=	./42_libft/
LIBFT_NAME		=	libft.a
LIBFT			=	$(addprefix $(LIBFT_PATH), $(LIBFT_NAME))
INC_PATH		=	./inc/
INC_NAME		=	minishell.h color.h parser.h
INC				=	$(addprefix $(INC_PATH), $(INC_NAME))
SRCS_PATH		=	./src/
OBJS_PATH		=	./objs/
SRCS_NAME		=	minishell.c signal.c parsing.c output.c envp.c \
					built_in_1.c built_in_2.c built_in_3.c built_in_4.c \
					forest_1.c forest_2.c execute_1.c execute_2.c condition.c \
					free.c preparsing_1.c preparsing_2.c preparsing_3.c \
					parsing_utils.c parsing_replase.c pipe_redir_1.c \
					pipe_redir_2.c pipe_redir_3.c ft_minishell_split.c
SRCS			=	$(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJS			=	$(addprefix $(OBJS_PATH), $(SRCS_NAME:.c=.o))

OPTFLAGS		= -MMD -g

all: libft ${NAME}

bonus: libft ${NAME}

$(NAME): $(OBJS_PATH) $(OBJS)
	$(CC) $(FLAGS) $(OPTFLAGS) $(FLAGS_RL) $(OBJS) -L$(LIBFT_PATH) -lft -o $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(INC)
	$(CC) $(FLAGS) $(OPTFLAGS) -I $(INC_PATH) -c $< -o $@

$(OBJS_PATH):
	mkdir -p $(OBJS_PATH)

libft:
	@make -C $(LIBFT_PATH)

clean:		clean_libft
	$(RM) $(OBJS_PATH)

clean_libft:
	@make clean -C $(LIBFT_PATH)

fclean:		clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)

re:			fclean all

.PHONY: all clean fclean re bonus

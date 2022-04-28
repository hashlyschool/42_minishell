NAME			=	minishell
CC				=	clang
RM				=	rm -rf
FLAGS			=	-Wall -Wextra -Werror -g
FLAGS_RL		=	-lreadline
LIBFT_PATH		=	./42_libft/
LIBFT_NAME		=	libft.a
LIBFT			=	$(addprefix $(LIBFT_PATH), $(LIBFT_NAME))
INC_PATH		=	./inc/
INC_NAME		=	minishell.h color.h parser.h parsers.h
INC				=	$(addprefix $(INC_PATH), $(INC_NAME))
SRCS_PATH		=	./src/
OBJS_PATH		=	./objs/
SRCS_NAME		=	minishell.c signal.c parsing.c output_1.c envp.c \
					built_in_1.c built_in_2.c built_in_3.c built_in_4.c \
					forest_1.c forest_2.c execute_1.c execute_2.c execute_3.c \
					condition.c free.c preparsing_1.c preparsing_2.c \
					preparsing_3.c parsing_utils.c parsing_replase.c \
					ft_minishell_split.c condition_redirect.c set_redir.c \
					processing_pipe.c processing_redir.c built_in_5.c \
					output_2.c preparsing_4.c heredoc.c shlvl.c \
					main_lexer.c preparse.c ft_charjoin.c replase.c \
					lex_check_redirect.c main_lexer_init.c parsing_utils_2.c \
					parsing_get_line.c  parsing_2.c execute_4.c\
					parse/check_symbol.c parse/job.c parse/lexer.c \
					parse/lexer_check_grammar.c parse/lexer_get_token.c parse/error.c \
					parse/lexer_quotes.c parse/lexer_token_type.c parse/parser.c \
					parse/parser_make_jobs.c parse/token.c parse/token_prepare.c
SRCS			=	$(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJS			=	$(addprefix $(OBJS_PATH), $(SRCS_NAME:.c=.o))

OPTFLAGS		=

all: libft ${NAME}

bonus: libft ${NAME}

$(NAME): $(OBJS_PATH) $(OBJS)
	$(CC) $(FLAGS) $(OPTFLAGS) $(FLAGS_RL) $(OBJS) -L$(LIBFT_PATH) -lft -o $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(INC)
	$(CC) $(FLAGS) $(OPTFLAGS) -I $(INC_PATH) -c $< -o $@

$(OBJS_PATH):
	mkdir -p $(OBJS_PATH)/parse

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

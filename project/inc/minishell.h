/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:45:11 by hashly            #+#    #+#             */
/*   Updated: 2022/03/20 23:04:13 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//for libft
# include "../42_libft/include/libft.h"
//for readline color
# include "./color.h"
//for parsing
# include "./parser.h"
//for getcwd, chdir
# include <unistd.h>
//for signal
# include <signal.h>
//for readline
# include <readline/readline.h>
//for add_history
# include <readline/history.h>
//for getenv
# include <stdlib.h>
//for errno
# include <errno.h>
//for waitpid
# include <sys/wait.h>
//for opendir, readdir, closedir
# include <sys/types.h>
# include <dirent.h>
//open
# include <fcntl.h>
# include <sys/stat.h>

# define CLOSE "$ "
# define PROMT "FlexTeam@minishell"
# define PROGRAM_NAME "minishell"

# define NONE 0
# define AND 1
# define OR 2
# define PIPE 3
# define PIPE_ON_THE_LEFT 4
# define PIPE_ON_THE_RIGHT 5
# define PIPE_BOTH_SIDES 6
# define SEMICOLON_CODE 7

# define BR_LEFT			"\1\2(\3\23"
# define BR_RIGHT			"\1\2)\3\23"
# define AND_STR			"\1\2&&\3\23"
# define PIPE_STR			"\1\2|\3\23"
# define OR_STR				"\1\2||\3\23"
# define SEMICOLON			"\1\2;\3\23"

# define REDIR_RIGHT_ONE	"\1\2>\3\23"
# define REDIR_RIGHT_TWO	"\1\2>>\3\23"
# define REDIR_LEFT_ONE		"\1\2<\3\23"
# define REDIR_LEFT_TWO		"\1\2<<\3\23"

# define START_VALUE		"\001\002${"
# define END_VALUE			"}\003\023"
# define STAR				"\001\002*\003\023"

# define START_DOUBLE_QUOTE	"\1\2!\3\23"
# define END_DOUBLE_QUOTE	"\1\2!!\3\23"

# define TESTER
# define STD_IN				0
# define STD_OUT			1
# define STD_ERR			2

typedef struct s_data
{
	char	*cmd;
	char	*cmd_exec;
	char	**argv;
	char	**redir;
	char	sep; //NONE, AND, OR, SEMICOLON
	char	pipe; //NONE, PIPE, PIPE_ON_THE_LEFT, PIPE_ON_THE_RIGHT, PIPE_BOTH_SIDES
}	t_data;

typedef struct s_node
{
	struct s_node	*next;
	struct s_node	*next_lvl;
	struct s_node	*prev_lvl;
	t_data			*data;
	char			exec;
	char			exit;
	char			stop;
	int				def_fd[2];
	int				pipe[2];
	int				redir_fd[3];
	char			**env;
}	t_node;

//minishell.c

//envp.c
char	**ft_copy_env(char **env, char ***argv);
int		ft_free_envp(char **env);
int		ft_set_ret(int value, char *msg, char **env);
char	*ft_getenv(char *name, char **env);
char	*ft_get_status(char **env);
//signal.c
void	sig_d(int signo);
void	set_signal(void);
//parsing.c
char	**parsing(char **env);
//output.c
char	*get_promt(char **env);
char	*ft_getenv(char *name, char **env);
void	output_error(int status, t_node *node);
//built_in_1.c
int		ft_echo(char **argv, char **env);
int		ft_cd(char **argv, char **env);
int		ft_env(char **argv, char **env);
//built_in_2.c
int		ft_export(char **argv, char ***env);
//built_in_3.c
int		ft_unset(char **argv, char ***env);
void	ft_parsing_argv_2(char **argv, char ***key, char ***value, size_t j);
//built_in_4.c
int		ft_pwd(char **argv, char **env);
int		ft_exit(char **argv, char **env, char *exit);
//forest_1.c
t_node	*create_empty_node(char **env);
t_node	*create_node_next_lvl(t_node *node, char **env);
t_node	*go_prev_lvl(t_node *node);
t_node	*create_next_node(t_node *node, char separator, char **env);
//forest_2.c
void	ft_add_argv(t_node *node, char *str);
t_node	*get_forest(char **line, char **env);
//execute_1.c
void	execute(t_node *node);
void	error_handling(int mode, t_node *node, char **path);
//execute_2.c
void	open_path_and_check_access(t_node *node);
//free.c
void	free_node(t_node *node);
void	free_forest(t_node *temp, char ***env);
//condition.c
int		cond_status(t_node	*node);
int		cond_is_built_in(t_node *node);
int		node_is_not_empty(t_node *root);
int		cmd_in_path(t_node *node);
//redir_pipe_1.c
void	ft_set_redir_pipe(t_node *node);
int		find_def_fd(t_node *node, int fd);
//redir_pipe_2.c
void	ft_set_redir(t_node *node);
//redir_pipe_3.c
void	ft_close_redir_pipe(t_node *node);
//predparsing_1.c
void	preparsing(t_node *node);
//preparsing_2.c
void	replace_data_in_node(char ***arr, t_node *node);
char	**split_cmd_line(char **end_str);
//preparsing_3.c
char	**open_star(t_node *node);

#endif

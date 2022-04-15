/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:45:11 by hashly            #+#    #+#             */
/*   Updated: 2022/04/15 14:05:13 by hashly           ###   ########.fr       */
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

# define BR_LEFT			"\001\002(\003\023"
# define BR_RIGHT			"\001\002)\003\023"
# define AND_STR			"\001\002&&\003\023"
# define PIPE_STR			"\001\002|\003\023"
# define OR_STR				"\001\002||\003\023"
# define SEMICOLON			"\001\002;\003\023"

# define REDIR_RIGHT_ONE	"\001\002>\003\023"
# define REDIR_RIGHT_TWO	"\001\002>>\003\023"
# define REDIR_LEFT_ONE		"\001\002<\003\023"
# define REDIR_LEFT_TWO		"\001\002<<\003\023"

# define START_VALUE		"\001\002${"
# define END_VALUE			"}\003\023"
# define STAR				"\001\002*\003\023"
# define START_DOLLAR		"\001\002$"
# define END_DOLLAR			"\003\023"

# define START_DOUBLE_QUOTE	"\001\002!\003\002"
# define END_DOUBLE_QUOTE	"\001\002!!\003\02"

// # define TESTER //debug
# define STD_IN				0
# define STD_OUT			1
# define STD_ERR			2

# ifdef __APPLE__ //debug
	void	rl_replace_line();
# endif

typedef struct s_data
{
	char	*cmd;
	char	*cmd_exec;
	char	**argv;
	char	sep;
	char	pipe;
}	t_data;

typedef struct s_list_redir
{
	int		n;
	int		type_redir;
	char	*word;
	int		fd;
}	t_list_redir;

typedef struct s_node
{
	struct s_node	*next;
	struct s_node	*next_lvl;
	struct s_node	*prev_lvl;
	t_data			*data;
	char			exec;
	char			exit;
	char			stop;
	int				def_fd[3];
	int				pipe[2];
	t_list			*list_redir;
	char			***env;
}	t_node;

typedef struct s_content
{
	pid_t	pid;
	t_node	*node;
}	t_content;

//envp.c
char	***ft_copy_env(char **env);
int		ft_free_envp(char ****env);
int		ft_set_ret(int value, char *msg, char **env);
char	*ft_getenv(char *name, char **env);
char	*ft_get_status(char **env);
//signal.c
void	sig_d(int signo);
void	set_signal(void);
//parsing.c
char	**parsing(char ***env, char *cmd, char mode_work);
//output.c
void	print_value_export(char **env, size_t len_key, size_t i);
void	print_error_parsing_argv(char ***key, char ***value, size_t i);
char	*get_promt(char **env);
char	*ft_getenv(char *name, char **env);
void	output_error(int status, t_node *node);
//built_in_1.c
int		ft_echo(char **argv, char ***env);
int		ft_cd(char **argv, char ***env);
int		ft_env(char **argv, char ***env);
//built_in_2.c
int		ft_export(char **argv, char ****env);
//built_in_3.c
int		ft_unset(char **argv, char ****env);
//built_in_4.c
int		ft_pwd(char **argv, char ***env);
int		ft_exit(char **argv, char ***env, char *exit);
//built_in_5.c
void	ft_parsing_argv_2(char **argv, char ***key, char ***value, char **env);
//forest_1.c
t_node	*create_empty_node(char ***env);
t_node	*create_node_next_lvl(t_node *node, char ***env);
t_node	*go_prev_lvl(t_node *node);
t_node	*create_next_node(t_node *node, char separator, char ***env);
//forest_2.c
void	ft_add_argv(t_node *node, char *str);
t_node	*get_forest(char **line, char ***env);
//execute_1.c
void	execute_level(t_node *node);
//execute_2.c
void	open_path_and_check_access(t_node *node);
//execute_3.c
void	error_handling(int mode, t_node *node, char **path);
void	execute_cmd_in_node(t_node *node);
//free.c
void	free_arr_export(char ***key, char ***value);
void	free_node(t_node *node);
void	free_forest(t_node *temp, char ****env);
//condition.c
int		cond_status(t_node	*node);
int		cond_is_built_in(t_node *node);
int		node_is_not_empty(t_node *root);
int		cmd_in_path(t_node *node);
//condition_redirect.c
char	str_is_redirect(char **str, int i);
//set_redir.c
void	ft_set_redir(t_node *node);
//processing_redir.c
void	ft_close_redir(t_node *node);
//set_pipe.c
void	ft_set_pipe(t_node *node);
//processing_pipe.c
void	set_default_fd(t_node *node);
void	close_default_fd(t_node *node);
int		pipilene_is_over(t_list **pipeline);
void	processing_pipe_in_child(t_node *node);
//predparsing_1.c
void	preparsing(t_node *node);
//preparsing_2.c
int		check_error_in_env_name(char *name, char *flag);
void	replace_data_in_node(char ***arr, t_node *node);
char	**split_cmd_line(char **end_str);
//preparsing_3.c
char	**open_star(t_node *node);
//preparsing_4.c
void	get_ret_no_ret(char **split_end, char **ret, t_node *node, int *x);
void	get_ret_yes_ret(char **split_end, char **ret, t_node *node, int *x);
char	matching(char **split_arr, char *d_name);
#endif

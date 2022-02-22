/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:45:11 by hashly            #+#    #+#             */
/*   Updated: 2022/02/22 17:50:00 by hashly           ###   ########.fr       */
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

# define BR_LEFT "("		//"\1\2(\3\23"
# define BR_RIGHT ")"		//\1\2)\3\23"
# define AND_STR "&&"		//"\1\2&&\3\23"
# define PIPE_STR "|"		//"\1\2|\3\23"
# define OR_STR "||"		//"\1\2||\3\23"
# define SEMICOLON ";"		//"\1\2;\3\23"

# define REDIR_RIGHT_ONE ">"	//"\1\2>\3\23"
# define REDIR_RIGHT_TWO ">>"	//"\1\2>>\3\23"
# define REDIR_LEFT_ONE "<"		//"\1\2<\3\23"
# define REDIR_LEFT_TWO "<<"	//"\1\2<<\3\23"

# define START_VALUE "${"	//"\001\002${"
# define END_VALUE "}"		//"}\003\023"
# define START_STAR "\001\002"
# define END_STAR "\003\023"

typedef struct s_data
{
	char	*cmd;
	char	*cmd_exec;
	char	**argv;
	char	**redir;
	char	sep; //NONE, AND, OR, SEMICOLON
	char	pipe; //NONE, PIPE, PIPE_ON_THE_LEFT, PIPE_ON_THE_RIGHT, PIPE_BOTH_SIDES
	int		fd_def[2];
	int		fd_old[2];
	int		fd_now[2];
}	t_data;

typedef struct s_node
{
	struct s_node	*next;
	struct s_node	*next_lvl;
	struct s_node	*prev_lvl;
	t_data			*data;
	char			exec;
	int				def_fd[2];
	int				pipe[2];
	char			**env;
}	t_node;

//minishell.c

//envp.c
char	**ft_copy_env(char **env);
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
int		ft_pwd(char **argv, char **env);
int		ft_env(char **argv, char **env);
//built_in_2.c
int		ft_export(char **argv, char **env);
//built_in_3.c
int		ft_unset(char *key, char **env);
//built_in_4.c

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
void	free_cmd_line(char ***arg);
void	free_node(t_node *node);
void	free_forest(t_node *temp);
//condition.c
int		cond_status(t_node	*node);
int		cond_is_built_in(t_node *node);
int		node_is_not_empty(t_node *root);
int		cmd_in_path(t_node *node);
//redir_pipe.c
void	ft_set_redir_pipe(t_node *node);
void	ft_close_redir_pipe(t_node *node);
//predparsing_1.c
void	preparsing(t_node *node);
//preparsing_2.c
void	replace_data_in_node(char ***arr, t_node *node);
char	**split_cmd_line(char **end_str);

#endif

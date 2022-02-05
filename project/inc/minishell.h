/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:45:11 by hashly            #+#    #+#             */
/*   Updated: 2022/02/05 20:19:12 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../42_libft/include/libft.h"
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

# define CLOSE "\001\033[0m\002$ \0"
# define PROMT "\001\033[1m\002\033[32mhashly@minishell:\033[34m"

# define NONE 0
# define AND 1
# define OR 2
# define PIPE 3
# define PIPE_ON_THE_LEFT 4
# define PIPE_ON_THE_RIGHT 5
# define PIPE_BOTH_SIDES 6
# define SEMICOLON_CODE 7

# define BRACKET_LEFT "(" //")\004"
# define BRACKET_RIGHT ")" //)\004"
# define TWO_AMPERSAND "&&" //"&&\004"
# define VERTICAL_BAR "|" //"|\004"
# define TWO_VERTICAL_BAR "||" //"||\004"
# define SEMICOLON ";" //";\004"

# define REDIR_RIGHT_ONE ">"	//"\1\2>\3\23"
# define REDIR_RIGHT_TWO ">>"	//"\1\2>>\3\23"
# define REDIR_LEFT_ONE "<"		//"\1\2<\3\23"
# define REDIR_LEFT_TWO "<<"	//"\1\2<<\3\23"

# define START_VALUE "${" //"\001\002${"
# define END_VALUE "}" //"}\003\023"

char	**g_envp;

typedef struct s_data
{
	char	*cmd;
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
	t_data	*data;
	char	exec;
	int		def_fd[2];
	int		pipe[2];
}	t_node;

//minishell.c

//envp.c
char	**ft_copy_env(char **envp);
int		ft_free_envp(void);
int		ft_set_ret(int value, char *msg);
char	*ft_getenv(char *name);
int		ft_get_status();
//signal.c
void	sig_d(int signo);
void	set_signal(void);
//parsing.c
char	**parsing(void);
//output.c
char	*get_promt(void);
char	*ft_getenv(char *name);
//built_in_1.c
int		ft_echo(char **argv);
int		ft_cd(char **argv);
int		ft_pwd(char **argv);
int		ft_env(char **argv);
//built_in_2.c
int		ft_export(char **argv);
//built_in_3.c
int		ft_unset(char *key);
//built_in_4.c

//forest.c
t_node	*get_forest(char **line);
void	ft_add_argv(t_node *node, char *str);
//execute.c
void	action(t_node *node);
void	execute(t_node *node, void (*action)(t_node *));
//free.c
void	free_cmd_line(char ***arg);
void	free_node(t_node *node);
void	free_forest(t_node *temp);
//condition.c
int		cond_status(t_node	*node);
int		cond_is_built_in(t_node *node);
//redir_pipe.c
void	ft_set_redir_pipe(t_node *node);
void	ft_close_redir_pipe(t_node *node);
//predparsing.c
void	preparsing(t_node *node);

#endif

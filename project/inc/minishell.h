/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:45:11 by hashly            #+#    #+#             */
/*   Updated: 2022/01/25 23:13:52 by hashly           ###   ########.fr       */
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

# define CLOSE "\001\033[0m\002$ \0"
# define PROMT "\001\033[1m\002\033[32mhashly@minishell:\033[34m"
# define NONE 0
# define AND 1
# define OR 2
# define PIPE 3
# define SEMICOLON_CODE 4
# define BRACKET_LEFT "(" //")\004"
# define BRACKET_RIGHT ")" //)\004"
# define TWO_AMPERSAND "&&" //"&&\004"
# define VERTICAL_BAR "|" //"|\004"
# define TWO_VERTICAL_BAR "||" //"||\004"
# define SEMICOLON ";" //";\004"
# define REDIR_RIGHT_ONE ">"	//"\1\2>\3\4"
# define REDIR_RIGHT_TWO ">>"	//"\1\2>>\3\4"
# define REDIR_LEFT_ONE "<"		//"\1\2<\3\4"
# define REDIR_LEFT_TWO "<<"	//"\1\2<<\3\4"

char	**g_envp;

typedef struct s_data
{
	char	*cmd;
	char	**argv;
	char	**redir;
	char	sep; //NONE, AND, OR, SEMICOLON
	char	pipe; //NONE, PIPE
}	t_data;

typedef struct s_node
{
	struct s_node	*next;
	struct s_node	*next_lvl;
	struct s_node	*prev_lvl;
	t_data	*data;
	char	exec;
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
//execute.c
void	execute(t_node *node, void (*action)(t_node *));
void	action(t_node *node);
//free.c
void	free_cmd_line(char ***arg);
void	free_node(t_node *node);
void	free_forest(t_node *temp);
//condition.c
int		cond_status(t_node	*node);
int		cond_is_built_in(t_node *node);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:45:11 by hashly            #+#    #+#             */
/*   Updated: 2022/01/16 14:47:26 by hashly           ###   ########.fr       */
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

char	**g_envp;

typedef struct s_data
{
	char	*cmd;
	char	**flag;
	char	**pipe;
	char	**redir;
	char	**argv;
	char	and;
	char	or;
}	t_data;

//minishell.c

//envp.c
char	**ft_copy_env(char **envp);
int		ft_free_envp(void);
int		ft_set_ret(int value);
char	*ft_getenv(char *name);
//signal.c
void	sig_d(int signo);
void	set_signal(void);
//parsing.c
char	*get_line(void);
t_list	*split_on_cmd(char *str);
//output.c
char	*get_promt(void);
char	*ft_getenv(char *name);
//built_in_1.c
int		ft_echo(t_data *data);
int		ft_cd(t_data *data);
int		ft_pwd(t_data *data);
int		ft_env(t_data *data);
//built_in_2.c
int		ft_export(char *key, char *value);
//built_in_3.c
int		ft_unset(char *key);
//built_in_4.c


#endif

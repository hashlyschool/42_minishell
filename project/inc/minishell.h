/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:45:11 by hashly            #+#    #+#             */
/*   Updated: 2022/01/11 16:29:21 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../42_libft/include/libft.h"
//for getcwd
# include <unistd.h>
//for signal
# include <signal.h>
//for readline
# include <readline/readline.h>
//for add_history
# include <readline/history.h>
//for getenv
# include <stdlib.h>

# define CLOSE "\001\033[0m\002$ "
# define PROMT "\001\033[1m\002\033[32mhashly@minishell:\033[34m"

typedef struct s_data
{
	char	*cmd;
	int		pipe;
}	t_data;

//minishell.c

//signal.c
void	sig_d(int signo);
void	set_signal(void);
//parsing.c
char	*get_line(void);
t_list	*split_on_cmd(char *str);
//output.c
char	*get_promt(void);

#endif

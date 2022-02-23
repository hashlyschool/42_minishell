/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 01:34:18 by hashly            #+#    #+#             */
/*   Updated: 2022/02/23 22:50:47 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//pwd
int	ft_pwd(char **argv, char **env)
{
	char	*dir;

	if (argv && argv[0])
		return (ft_set_ret(1, \
		"minishell: pwd: options are not processed\n", env));
	dir = getcwd(NULL, 1024);
	if (!dir)
		return (ft_set_ret(-1, "minishell: pwd: invalid argument\n", env));
	ft_putstr_fd(dir, 1);
	write(1, "\n", 1);
	free(dir);
	return (ft_set_ret(0, NULL, env));
}

static char	str_is_number(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

//exit
int	ft_exit(char **argv, char **env, char *exit)
{
	write(1, "exit\n", 5);
	if (argv && argv[0])
	{
		if (!str_is_number(argv[0]))
		{
			ft_putstr_fd("minishell: exit: ", 1);
			ft_putstr_fd(argv[0], 1);
			ft_set_ret(2, ": numeric argument required\n", env);
		}
		else
			ft_set_ret(ft_atoi(argv[0]), "", env);
	}
	*exit = 1;
	return (0);
}

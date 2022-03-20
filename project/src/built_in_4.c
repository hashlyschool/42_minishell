/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 01:34:18 by hashly            #+#    #+#             */
/*   Updated: 2022/03/20 23:41:21 by hashly           ###   ########.fr       */
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
	ft_putendl_fd(dir, STD_OUT);
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
	ft_putstr_fd("exit\n", STD_ERR);
	if (argv && argv[0])
	{
		if (argv[1])
			ft_set_ret(1, "minishell: exit: too many arguments\n", env);
		else if (!str_is_number(argv[0]))
		{
			ft_putstr_fd("minishell: exit: ", STD_ERR);
			ft_putstr_fd(argv[0], STD_ERR);
			ft_set_ret(2, ": numeric argument required\n", env);
		}
		else
			ft_set_ret(ft_atoi_long_long(argv[0]), "", env);
	}
	*exit = 1;
	return (0);
}

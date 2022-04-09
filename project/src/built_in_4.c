/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 01:34:18 by hashly            #+#    #+#             */
/*   Updated: 2022/04/09 23:43:02 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//pwd
int	ft_pwd(char **argv, char ***env)
{
	char	*dir;

	if (argv && argv[0])
		return (ft_set_ret(1, \
		"minishell: pwd: options are not processed\n", *env));
	dir = getcwd(NULL, 1024);
	if (!dir)
		return (ft_set_ret(-1, "minishell: pwd: invalid argument\n", *env));
	ft_putendl_fd(dir, STD_OUT);
	free(dir);
	return (ft_set_ret(0, NULL, *env));
}

static int	check_max_long_long(char *str, int start, int end, char minus)
{
	char	*temp;
	char	flag;
	size_t	len;

	flag = 0;
	while (str[start] && str[start] == '0')
		start++;
	temp = ft_substr(str, start, end + 1);
	len = ft_strlen(temp);
	if (len > 19 || (len == 19 && \
	((minus && ft_strncmp(temp, "9223372036854775808", len) > 0) || \
	(!minus && ft_strncmp(temp, "9223372036854775807", len) > 0))))
		flag = 1;
	free(temp);
	return (flag);
}

static char	check_minus(char c)
{
	if (c == '-')
		return (1);
	return (0);
}

static char	str_is_number(char *str)
{
	size_t	i;
	int		start_nbr;
	char	minus;

	minus = check_minus(str[0]);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && (str[i] == '\f' || str[i] == ' ' || str[i] == '\t' || str[i] == '\r'))
		i++;
	start_nbr = i;
	while (str[i])
	{
		if (check_max_long_long(str, start_nbr, i, minus))
			return (0);
		if (!ft_isdigit(str[i]))
		{
			while (str[i] && (str[i] == ' ' || str[i] == '\t'))
				i++;
			if (str[i] == 0)
				return (1);
			return (0);
		}
		i++;
	}
	return (1);
}

//exit
int	ft_exit(char **argv, char ***env, char *exit)
{
	// 	ft_putstr_fd("exit\n", STD_ERR); //add in finish minishell
	if (argv && argv[0])
	{
		if (!str_is_number(argv[0]))
		{
			ft_putstr_fd("minishell: exit: ", STD_ERR);
			ft_putstr_fd(argv[0], STD_ERR);
			ft_set_ret(2, ": numeric argument required\n", *env);
		}
		else if (argv[1])
			ft_set_ret(1, "minishell: exit: too many arguments\n", *env);
		else
			ft_set_ret(ft_atoi_long_long(argv[0]), "", *env);
	}
	*exit = 1;
	return (0);
}

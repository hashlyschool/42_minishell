/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:27:13 by hashly            #+#    #+#             */
/*   Updated: 2022/01/16 14:46:07 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//echo
int	ft_echo(t_data *data)
{
	char	flag_n;
	size_t	i;

	flag_n = 0;
	if (data->flag && data->flag[0] && ft_strncmp(data->flag[0], "-n", 3) == 0)
		flag_n = 1;
	i = flag_n;
	while (data->flag[i])
	{
		ft_putstr_fd(data->flag[i++], 1);
		if (data->flag[i] || (data->argv && data->argv[0]))
			write(1, " ", 1);
	}
	i = 0;
	while (data->argv && data->argv[i])
	{
		ft_putstr_fd(data->argv[i++], 1);
		if (data->argv[i])
			write(1, " ", 1);
	}
	if (flag_n == 0)
		write(1, "\n", 1);
	return (ft_set_ret(0));
}

//cd
int	ft_cd(t_data *data)
{
	if (data->flag)
	{
		write(2, "minishell: cd: options are not processed\n", 42);
		return (ft_set_ret(1));
	}
	if (data->argv[0] == NULL)
	{
		data->argv[0] = ft_getenv("HOME");
		if (data->argv[0] == NULL)
		{
			write(2, "minishell: cd: HOME not set\n", 29);
			return (ft_set_ret(1));
		}
	}
	if (data->argv[1] != NULL)
	{
		write(2, "minishell: cd: too many arguments\n", 35);
		return (ft_set_ret(1));
	}
	if (chdir(data->argv[0]) == 0)
		return (ft_set_ret(0));
	perror("minishell: cd");
	errno = 0;
	return (ft_set_ret(1));
}

//pwd
int	ft_pwd(t_data *data)
{
	char	*dir;

	if (data->flag)
	{
		write(2, "minishell: pwd: options are not processed\n", 43);
		return (ft_set_ret(1));
	}
	dir = getcwd(NULL, 1024);
	if (!dir)
		return (ft_set_ret(-1));
	ft_putstr_fd(dir, 1);
	write(1, "\n", 1);
	free(dir);
	return (ft_set_ret(0));
}

//env
int	ft_env(t_data *data)
{
	char	*temp;
	size_t	i;

	if (data->flag)
	{
		write(2, "minishell: env: options are not processed\n", 43);
		return (ft_set_ret(1));
	}
	i = 0;
	temp = g_envp[i];
	while (temp)
	{
		ft_putstr_fd(temp, 1);
		temp = g_envp[++i];
	}
	return (ft_set_ret(0));
}

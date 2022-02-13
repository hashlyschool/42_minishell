/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:27:13 by hashly            #+#    #+#             */
/*   Updated: 2022/02/13 18:03:09 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//echo
int	ft_echo(char **argv, char **env)
{
	char	flag_n;
	size_t	i;

	flag_n = 0;
	if (argv && argv[0] && ft_strncmp(argv[0], "-n", 3) == 0)
		flag_n = 1;
	i = flag_n;
	while (argv && argv[i])
	{
		ft_putstr_fd(argv[i++], 1);
		if (argv[i])
			write(1, " ", 1);
	}
	if (flag_n == 0)
		write(1, "\n", 1);
	return (ft_set_ret(0, NULL, env));
}

/*
Синтаксис		Объяснение
cd				Перемещение в домашний каталог +
cd ~			Перемещение в домашний каталог ?
cd ..			Перемещение на один уровень выше ?
cd -			Перемещение в предыдущий каталог ?
cd Directory1	Перемещение в каталог Directory1 ? нужно
cd Dir1/Dir2	Перемещение в каталог Dir2 по указанному пути ? нужно
*/
//cd
int	ft_cd(char **argv, char **env)
{
	if (argv[0] == NULL)
	{
		argv[0] = ft_getenv("HOME", env);
		if (argv[0] == NULL)
			return (ft_set_ret(1, "minishell: cd: HOME not set\n", env));
	}
	if (argv[1] != NULL)
		return (ft_set_ret(1, "minishell: cd: too many arguments\n", env));
	if (chdir(argv[0]) == 0)
		return (ft_set_ret(0, NULL, env));
	perror("minishell: cd");
	errno = 0;
	return (ft_set_ret(1, NULL, env));
}

//pwd
int	ft_pwd(char **argv, char **env)
{
	char	*dir;

	if (argv && argv[0])
		return (ft_set_ret(1, "minishell: pwd: options are not processed\n", env));
	dir = getcwd(NULL, 1024);
	if (!dir)
		return (ft_set_ret(-1, "minishell: pwd: invalid argument\n", env));
	ft_putstr_fd(dir, 1);
	write(1, "\n", 1);
	free(dir);
	return (ft_set_ret(0, NULL, env));
}

//env
int	ft_env(char **argv, char **env)
{
	char	*temp;
	size_t	i;

	if (argv && argv[0])
		return (ft_set_ret(1, "minishell: env: options are not processed\n", env));
	i = 0;
	temp = env[i];
	while (temp)
	{
		ft_putstr_fd(temp, 1);
		temp = env[++i];
	}
	return (ft_set_ret(0, NULL, env));
}

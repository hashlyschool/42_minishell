/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:27:13 by hashly            #+#    #+#             */
/*   Updated: 2022/02/23 00:32:25 by hashly           ###   ########.fr       */
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

static void	change_old_pwd(char **env)
{
	char	**argv;
	char	*old_pwd;

	argv = NULL;
	old_pwd = getcwd(NULL, 1024);
	if (!old_pwd)
		return ;
	old_pwd = ft_strjoin_free_s2("OLDPWD=", old_pwd);
	argv = ft_add_line(argv, old_pwd);
	free(old_pwd);
	ft_export(argv, env);
	ft_free_str_of_str(&argv);
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
	char	*path;

	if (!argv || !argv[0] || ft_strncmp(argv[0], "~", 2) == 0)
	{
		path = ft_strdup(ft_getenv("HOME", env));
		if (path == NULL)
			return (ft_set_ret(1, "minishell: cd: HOME not set\n", env));
	}
	else if (ft_strncmp(argv[0], "-", 2) == 0)
	{
		path = ft_strdup(ft_getenv("OLDPWD", env));
		if (path == NULL)
			return (ft_set_ret(1, "minishell: cd: OLDPWD not set\n", env));
		ft_putstr_fd(path, 1);
		write(1, "\n", 1);
	}
	else
		path = ft_strdup(argv[0]);
	change_old_pwd(env);
	if (chdir(path) == 0)
	{
		free(path);
		return (ft_set_ret(0, NULL, env));
	}
	path = ft_strjoin_free_s2("minishell: cd: ", path);
	perror(path);
	free(path);
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
		write(1, "\n", 1);
		temp = env[++i];
	}
	return (ft_set_ret(0, NULL, env));
}

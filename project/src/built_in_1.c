/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:27:13 by hashly            #+#    #+#             */
/*   Updated: 2022/04/11 19:47:26 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//echo
int	ft_echo(char **argv, char ***env)
{
	int	flag_n;
	size_t	i;

	flag_n = 0;
	while (argv && argv[flag_n] && ft_strncmp(argv[flag_n], "-n", 2) == 0)
		flag_n++;
	i = flag_n;
	while (argv && argv[i])
	{
		ft_putstr_fd(argv[i++], STD_OUT);
		if (argv[i])
			ft_putstr_fd(" ", STD_OUT);
	}
	if (flag_n == 0)
		ft_putstr_fd("\n", STD_OUT);
	return (ft_set_ret(0, NULL, *env));
}

static void	change_old_pwd_and_pwd(char ***env, char *old_pwd)
{
	char	**argv;
	char	*pwd;


	argv = NULL;
	argv = ft_add_line(argv, old_pwd);
	pwd = ft_strjoin_free_s2("PWD=", getcwd(NULL, 1024));
	argv = ft_add_line(argv, pwd);
	free(pwd);
	ft_export(argv, &env);
	ft_free_str_of_str(&argv);
}

static int	ft_get_path(char **path, char **argv, char **env)
{
	if (!argv || !argv[0] || ft_strncmp(argv[0], "~", 2) == 0)
	{
		*path = ft_getenv("HOME", env);
		if (*path == NULL)
			return (ft_set_ret(1, "minishell: cd: HOME not set\n", env));
		*path = ft_strdup(*path);
	}
	else if (ft_strncmp(argv[0], "-", 2) == 0)
	{
		*path = ft_getenv("OLDPWD", env);
		if (*path == NULL)
			return (ft_set_ret(1, "minishell: cd: OLDPWD not set\n", env));
		*path = ft_strdup(*path);
		ft_putendl_fd(*path, STD_OUT);
	}
	else
		*path = ft_strdup(argv[0]);
	return (0);
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
int	ft_cd(char **argv, char ***env)
{
	char	*path;
	char	*old_pwd;

	if (ft_get_path(&path, argv, *env))
		return (1);
	old_pwd = ft_strjoin("OLDPWD=", ft_getenv("PWD", *env));
	if (chdir(path) == 0)
	{
		change_old_pwd_and_pwd(env, old_pwd);
		free(old_pwd);
		free(path);
		return (ft_set_ret(0, NULL, *env));
	}
	path = ft_strjoin_free_s2("minishell: cd: ", path);
	perror(path);
	free(path);
	errno = 0;
	return (ft_set_ret(1, NULL, *env));
}

//env
int	ft_env(char **argv, char ***env)
{
	char	*temp;
	size_t	i;

	if (argv && argv[0])
		return (ft_set_ret(1, \
		"minishell: env: options are not processed\n", *env));
	i = 0;
	temp = env[0][i];
	while (temp)
	{
		if (ft_strchr(temp, '='))
			ft_putendl_fd(temp, STD_OUT);
		temp = env[0][++i];
	}
	return (ft_set_ret(0, NULL, *env));
}

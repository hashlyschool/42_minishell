/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:05:59 by hashly            #+#    #+#             */
/*   Updated: 2022/04/10 17:57:36 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	output_error(int status, t_node *node)
{
	if (status == 1)
	{
		ft_putstr_fd(PROGRAM_NAME": ", STD_ERR);
		ft_putstr_fd(node->data->cmd, STD_ERR);
		exit(ft_set_ret(127, ": command not found\n", *node->env));
	}
	else if (status == 2)
	{
		ft_putstr_fd(PROGRAM_NAME": ", STD_ERR);
		ft_putstr_fd(node->data->cmd, STD_ERR);
		exit(ft_set_ret(127, ": No such file or directory\n", *node->env));
	}
	else if (status == 3)
	{
		ft_putstr_fd(PROGRAM_NAME": ", STD_ERR);
		ft_putstr_fd(node->data->cmd, STD_ERR);
		exit(ft_set_ret(126, ": Is a directory\n", *node->env));
	}
}

static char	*get_pwd(char **env)
{
	char	*home;
	char	*dir;
	char	*dir_new;
	size_t	len_home;

	dir = getcwd(NULL, 1024);
	if (!dir)
		return (NULL);
	home = ft_getenv("HOME", env);
	if (home)
	{
		len_home = ft_strlen(home);
		if (ft_strncmp(home, dir, len_home) == 0 && ft_strlen(dir) >= len_home)
		{
			dir_new = ft_strdup(dir + len_home - 1);
			dir_new[0] = '~';
			free(dir);
			dir = dir_new;
		}
	}
	return (dir);
}

char	*get_promt(char **env)
{
	char	*str;
	char	*dir;
	char	*promt;

	dir = get_pwd(env);
	str = ft_strjoin(RL_GREEN""PROMT""RL_RESET":"RL_BLUE, dir);
	free(dir);
	promt = ft_strjoin(str, RL_RESET""CLOSE);
	free(str);
	return (promt);
}

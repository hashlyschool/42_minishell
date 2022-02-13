/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:05:59 by hashly            #+#    #+#             */
/*   Updated: 2022/02/13 18:04:59 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
		if (ft_strncmp(home, dir, len_home) == 0 && ft_strlen(dir) > len_home)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:05:59 by hashly            #+#    #+#             */
/*   Updated: 2022/01/11 18:10:36 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*get_pwd(void)
{
	char	*home;
	char	*dir;
	char	*dir_new;
	size_t	len_home;

	dir = getcwd(NULL, 1024);
	if (!dir)
		return (NULL);
	home = getenv("HOME");
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

char	*get_promt(void)
{
	char	*str;
	char	*dir;
	char	*promt;

	dir = get_pwd();
	str = ft_strjoin(PROMT, dir);
	free(dir);
	promt = ft_strjoin(str, CLOSE);
	free(str);
	return (promt);
}

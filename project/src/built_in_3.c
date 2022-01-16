/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 17:03:31 by hashly            #+#    #+#             */
/*   Updated: 2022/01/15 17:03:39 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**malloc_for_unset(size_t index)
{
	char	**ret;
	size_t	i;
	size_t	j;

	i = 0;
	ret = g_envp;
	while (ret[i])
		i++;
	ret = (char **)malloc(sizeof(char *) * (i + 2));
	ret[i - 1] = NULL;
	ret[i] = g_envp[i + 1];
	ret[i + 1] = NULL;
	i = 0;
	j = 0;
	while (ret[i])
	{
		if (j != index)
			ret[i++] = g_envp[j];
		j++;
	}
	free(g_envp[index]);
	free(g_envp);
	return (ret);
}

//unset
int	ft_unset(char *key)
{
	char	**temp_envp;
	size_t	len_key;
	size_t	i;

	i = 0;
	temp_envp = g_envp;
	len_key = ft_strlen(key);
	while (temp_envp[i])
	{
		if (ft_strlen(temp_envp[i]) > len_key && \
		ft_strncmp(temp_envp[i], key, len_key) == 0 && \
		temp_envp[i][len_key] == '=')
		{
			g_envp = malloc_for_unset(i);
			return (0);
		}
		i++;
	}
	return (-1);
}
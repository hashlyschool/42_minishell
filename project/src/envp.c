/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 17:05:33 by hashly            #+#    #+#             */
/*   Updated: 2022/01/15 17:07:28 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**ft_copy_env(char **envp)
{
	size_t	i;
	char	**ret;

	i = 0;
	while (envp[i])
		i++;
	ret = (char **)malloc(sizeof(char *) * (i + 1 + 2));
	ret[i] = NULL;
	ret[i + 1] = ft_strdup("0");
	ret[i + 2] = NULL;
	i = i - 2;
	while (--i > 0)
		ret[i] = ft_strdup(envp[i]);
	ret[i] = ft_strdup(envp[i]);
	return (ret);
}

int	ft_free_envp(void)
{
	size_t	i;

	i = 0;
	while (g_envp[i])
		free(g_envp[i++]);
	i++;
	free(g_envp[i]);
	free(g_envp);
	return (0);
}

int	ft_set_ret(int value)
{
	size_t i;

	i = 0;
	while (g_envp[i])
		i++;
	free(g_envp[i + 1]);
	g_envp[i + 1] = ft_itoa(value);
	return (0);
}

char	*ft_getenv(char *name)
{
	char	*temp;
	size_t	name_len;
	size_t	i;

	i = 0;
	if (!g_envp)
		return (NULL);
	temp = g_envp[i];
	name_len = ft_strlen(name);
	while (temp)
	{
		if (ft_strlen(temp) > name_len && \
		ft_strncmp(temp, name, name_len) == 0 && \
		temp[name_len] == '=')
			return (temp + name_len + 1);
		temp = g_envp[++i];
	}
	return (NULL);
}

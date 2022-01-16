/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 01:30:04 by hashly            #+#    #+#             */
/*   Updated: 2022/01/15 17:03:20 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_fill_str(char *s1, char *s2)
{
	size_t	len;
	char	*str;

	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	str = (char *)malloc(sizeof(char) * len);
	while (*s1)
		*str++ = *s1++;
	*str++ = '=';
	while (*s2)
		*str++ = *s2++;
	*str = 0;
	return (str);
}

static char	**malloc_for_export(char *key, char *value)
{
	char	**ret;
	size_t	i;
	size_t	j;

	i = 0;
	while (g_envp[i])
		i++;
	ret = (char **)malloc(sizeof(char *) * (i + 2 + 2));
	ret[i] = ft_fill_str(key, value);
	ret[i + 1] = NULL;
	ret[i + 2] = g_envp[i + 1];
	ret[i + 3] = NULL;
	j = -1;
	i = i - 2;
	while (++j < i)
		ret[j] = g_envp[j];
	free(g_envp);
	return (ret);
}

//export
int	ft_export(char *key, char *value)
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
			free(g_envp[i]);
			g_envp[i] = ft_fill_str(key, value);
			return (ft_set_ret(0));
		}
		i++;
	}
	g_envp = malloc_for_export(key, value);
	return (ft_set_ret(0));
}
